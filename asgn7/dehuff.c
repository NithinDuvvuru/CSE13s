#include "bitreader.h"
#include "node.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "i:o:h"

void dehuff_decompress_file(FILE *fout, BitReader *inbuf) {
    uint8_t type1 = bit_read_uint8(inbuf);
    uint8_t type2 = bit_read_uint8(inbuf);
    uint32_t filesize = bit_read_uint32(inbuf);
    uint16_t num_leaves = bit_read_uint16(inbuf);

    assert(type1 == 'H');
    assert(type2 == 'C');

    int num_nodes = 2 * num_leaves - 1;
    Node *stack[64]; // Assuming 64 is sufficient
    int top = -1;

    Node *node;
    for (int i = 0; i < num_nodes; i++) {
        int bit = bit_read_bit(inbuf);
        if (bit == 1) {
            uint8_t symbol = bit_read_uint8(inbuf);
            node = node_create(symbol, 0);
        } else {
            node = node_create(0, 0);
            node->right = stack[top--];
            node->left = stack[top--];
        }
        stack[++top] = node;
    }

    Node *code_tree = stack[top];
    int bit;
    for (uint32_t i = 0; i < filesize; i++) {
        node = code_tree;
        while (true) {
            bit = bit_read_bit(inbuf);
            if (bit == 0) {
                node = node->left;
            } else {
                node = node->right;
            }
            if (node->left == NULL && node->right == NULL) {
                fprintf(fout, "%c", node->symbol);
                break;
            }
        }
    }
    node_free(&code_tree);
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
        default: fprintf(stderr, "Usage: %s -i <input_file> -o <output_file>\n", argv[0]); return 0;
        }
    }

    if (input_file == NULL || output_file == NULL) {
        fprintf(stderr, "Input and output files are required.\n");
        return 1;
    }

    BitReader *fin = bit_read_open(input_file);
    if (fin == NULL) {
        fprintf(stderr, "Error opening input file");
        bit_read_close(&fin);
        return 1;
    }

    FILE *fout = fopen(output_file, "wb");
    if (fout == NULL) {
        fprintf(stderr, "Can't open output file %s\n", output_file);
        bit_read_close(&fin);
        return 1;
    }

    dehuff_decompress_file(fout, fin);

    bit_read_close(&fin);
    fclose(fout);

    return 0;
}
