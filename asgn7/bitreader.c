#include "bitreader.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitReader {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitReader *bit_read_open(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        perror("Error opening file");
        return NULL;
    }

    BitReader *buf = (BitReader *) malloc(sizeof(BitReader));
    if (buf == NULL) {
        perror("Memory allocation failed");
        fclose(f);
        return NULL;
    }

    buf->underlying_stream = f;
    buf->byte = 0;
    buf->bit_position = 8;

    return buf;
}

void bit_read_close(BitReader **pbuf) {
    if (pbuf == NULL || *pbuf == NULL) {
        return;
    }

    if (fclose((*pbuf)->underlying_stream) == EOF) {
        perror("Error closing file");
    }

    free(*pbuf);
    *pbuf = NULL;
}

uint8_t bit_read_bit(BitReader *buf) {
    if (buf->bit_position > 7) {
        int c = fgetc(buf->underlying_stream);
        if (c == EOF) {
            exit(1);
        }
        buf->byte = (uint8_t) c;
        buf->bit_position = 0;
    }

    uint8_t bit = (buf->byte >> buf->bit_position) & 1;
    buf->bit_position++;

    return bit;
}

uint8_t bit_read_uint8(BitReader *buf) {
    uint8_t byte = 0;
    for (int i = 0; i < 8; i++) {
        byte |= (bit_read_bit(buf) << i);
    }
    return byte;
}

uint16_t bit_read_uint16(BitReader *buf) {
    uint16_t word = 0;
    for (int i = 0; i < 16; i++) {
        word |= ((uint16_t) bit_read_bit(buf) << i);
    }
    return word;
}

uint32_t bit_read_uint32(BitReader *buf) {
    uint32_t word = 0;
    for (int i = 0; i < 32; i++) {
        word |= ((uint32_t) bit_read_bit(buf) << i);
    }
    return word;
}
