#include "bitwriter.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitWriter {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitWriter *bit_write_open(const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        perror("Error opening file");
        return NULL;
    }

    BitWriter *buf = (BitWriter *) malloc(sizeof(BitWriter));
    if (buf == NULL) {
        perror("Memory allocation failed");
        fclose(f);
        return NULL;
    }

    buf->underlying_stream = f;
    buf->byte = 0;
    buf->bit_position = 0;

    return buf;
}

void bit_write_close(BitWriter **pbuf) {
    if (pbuf == NULL || *pbuf == NULL) {
        return;
    }

    if ((*pbuf)->bit_position > 0) {
        if (fputc((*pbuf)->byte, (*pbuf)->underlying_stream) == EOF) {
            perror("Error writing byte to file");
        }
    }

    if (fclose((*pbuf)->underlying_stream) == EOF) {
        perror("Error closing file");
    }

    free(*pbuf);
    *pbuf = NULL;
}

void bit_write_bit(BitWriter *buf, uint8_t bit) {
    if (buf->bit_position > 7) {
        if (fputc(buf->byte, buf->underlying_stream) == EOF) {
            perror("Error writing byte to file");
        }
        buf->byte = 0;
        buf->bit_position = 0;
    }

    buf->byte |= (bit << buf->bit_position);
    buf->bit_position++;
}

void bit_write_uint8(BitWriter *buf, uint8_t x) {
    for (int i = 0; i < 8; i++) {
        uint8_t bit = (x >> i) & 1;
        bit_write_bit(buf, bit);
    }
}

void bit_write_uint16(BitWriter *buf, uint16_t x) {
    for (int i = 0; i < 16; i++) {
        uint8_t bit = (x >> i) & 1;
        bit_write_bit(buf, bit);
    }
}

void bit_write_uint32(BitWriter *buf, uint32_t x) {
    for (int i = 0; i < 32; i++) {
        uint8_t bit = (x >> i) & 1;
        bit_write_bit(buf, bit);
    }
}
