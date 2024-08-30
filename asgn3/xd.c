#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SIZE 16

void hexToAscii(const unsigned char buffer[16], ssize_t size) {
    int format = 27;
    for (ssize_t i = 0; i < size; i++) {
        printf("%02x", buffer[i]);
        format += 2;
        if (((i + 1) % 2 == 0 || i == 1) && i != 0) {
            printf(" ");
            format += 1;
        }
    }
    for (int i = format; i <= 67; i++) {
        printf(" ");
    }
    for (ssize_t i = 0; i < size; i++) {
        if (buffer[i] >= 32 && buffer[i] <= 126) {
            printf("%c", buffer[i]);
        } else {
            printf(".");
        }
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    unsigned char buffer[SIZE];
    int fd;
    unsigned char totalBuffer[SIZE * 2];
    ssize_t total = 0;
    ssize_t bytes = 0;
    if (argc > 2) {
        return 1;
    }
    if (argc == 2) {
        fd = open((argv[1]), O_RDONLY);
        if (fd == -1) {
            return -1;
        }
    } else
        fd = STDIN_FILENO;

    off_t offset = 0;
    int overflow = 0;
    int start = 0;
    while ((bytes = read(fd, buffer, SIZE)) > 0) {
        for (int i = 0; i < bytes; i++) {
            if (total + i < 16) {
                totalBuffer[total + i + start] = buffer[i];
            } else {
                overflow += 1;
            }
        }
        total += bytes;
        if (bytes == -1) {
            break;
        }
        if (total >= 16) {
            printf("%08lx: ", (long unsigned int) offset);
            hexToAscii(totalBuffer, SIZE);
            offset += SIZE;
            total = 0;
            memset(totalBuffer, 0, sizeof(totalBuffer));
        }
        if (overflow > 0) {
            for (int i = 0; i < overflow; i++) {
                totalBuffer[i] = buffer[bytes + i - overflow];
            }
            start = overflow;
            overflow = 0;
        }
    }
    if (total != 0) {
        printf("%08lx: ", (long unsigned int) offset);
        hexToAscii(totalBuffer, total + start);
    }
    if (argc == 2)
        close(fd);

    return 0;
}
