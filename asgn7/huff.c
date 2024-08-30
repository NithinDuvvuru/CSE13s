#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:h"

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

uint32_t fill_histogram(FILE *fin, uint32_t *histogram) {
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }

    histogram[0x00]++;
    histogram[0xff]++;

    uint32_t filesize = 0;
    int byte;
    while ((byte = fgetc(fin)) != EOF) {
        histogram[byte]++;
        filesize++;
    }

    return filesize;
}

Node *create_tree(uint32_t *histogram, uint16_t *num_leaves) {
    PriorityQueue *pq = pq_create();

    for (int i = 0; i < 256; i++) {
        if (histogram[i] > 0) {
            Node *node = node_create((uint8_t) i, histogram[i]);
            enqueue(pq, node);
            (*num_leaves)++;
        }
    }
    while (pq_size_is_1(pq) == false && pq_is_empty(pq) == false) {
        Node *left = dequeue(pq);
        Node *right = dequeue(pq);

        Node *parent = node_create(0, left->weight + right->weight);
        parent->left = left;
        parent->right = right;
        enqueue(pq, parent);
    }

    Node *tree = dequeue(pq);
    pq_free(&pq);
    return tree;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {
    if (node->left == NULL) {
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    } else {
        fill_code_table(code_table, node->left, code, code_length + 1);
        code |= (uint64_t) 1 << code_length;
        fill_code_table(code_table, node->right, code, code_length + 1);
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left == NULL) {
        /* node is a leaf */
        bit_write_bit(outbuf, 1); // Write bit 1 to outbuf
        bit_write_uint8(outbuf, node->symbol); // Write uint8 node->symbol to outbuf
    } else {
        /* node is internal */
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0); // Write bit 0 to outbuf
    }
}

void huff_compress_file(BitWriter *outbuf, FILE *fin, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    // Write file header
    bit_write_uint8(outbuf, 'H'); // Write 'H' to outbuf
    bit_write_uint8(outbuf, 'C'); // Write 'C' to outbuf
    bit_write_uint32(outbuf, filesize); // Write filesize to outbuf
    bit_write_uint16(outbuf, num_leaves); // Write num_leaves to outbuf
    huff_write_tree(outbuf, code_tree);
    // Compress the file content using Huffman codes
    while (true) {
        int b = fgetc(fin);
        if (b == EOF) {
            break;
        }
        uint64_t code = code_table[b].code;
        uint8_t code_length = code_table[b].code_length;
        for (int i = 0; i < code_length; i++) {
            bit_write_bit(outbuf, (code & 1)); // Write bit (code & 1) to outbuf
            code >>= 1;
        }
    }
}

int main(int argc, char *argv[]) {
    int opt;
    char *input_file = NULL;
    char *output_file = NULL;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': input_file = optarg; break;
        case 'o': output_file = optarg; break;
        case 'h': printf("Usage: %s -i <input_file> -o <output_file>\n", argv[0]); return 0;
        default: fprintf(stderr, "Usage: %s -i <input_file> -o <output_file>\n", argv[0]); return 1;
        }
    }

    if (input_file == NULL || output_file == NULL) {
        fprintf(stderr, "Input and output file error.\n");
        return 1;
    }

    FILE *fin = fopen(input_file, "rb");
    if (fin == NULL) {
        fprintf(stderr, "Can't open input file %s\n", output_file);
        return 1;
    }

    uint32_t histogram[256];
    uint32_t filesize = fill_histogram(fin, histogram);
    fclose(fin);

    uint16_t num_leaves = 0;
    Node *code_tree = create_tree(histogram, &num_leaves);

    Code code_table[256];
    fill_code_table(code_table, code_tree, 0, 0);

    fin = fopen(input_file, "rb");
    if (fin == NULL) {
        perror("Error rewinding input file");
        return 1;
    }

    BitWriter *fout = bit_write_open(output_file);
    if (fout == NULL) {
        perror("Error opening output file");
        fclose(fin);
        return 1;
    }

    huff_compress_file(fout, fin, filesize, num_leaves, code_tree, code_table);
    fclose(fin);
    bit_write_close(&fout);

    node_free(&code_tree);

    return 0;
}
