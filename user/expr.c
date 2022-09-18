/*
expr.c
A modified version of GNU expr
*/
#include "kernel/fcntl.h"
#include "user.h"

enum evalState {
    NUM,
    PLUS,
    MINUS 
};

typedef struct {
    char *base;
    unsigned int length;
    unsigned int capacity;
} Buffer;

Buffer allocBuffer(int);
int readIntoBuffer(int, Buffer *);
int evaluate(Buffer);

// Read from stdin or a file and evaluates the input
// as an arithemtic expression containing +, -, and integers.

int main(int argc, char *argv[]) {
    // Argument parsing
    int fd = 0;
    if (argc == 2) {
        fd = open(argv[1], O_RDONLY);
    }
    if (fd < 0) {
        printf(1, "expr: open error\n");
        exit();
    }

    Buffer buffer = allocBuffer(512);
    if (readIntoBuffer(fd, &buffer) < 0) {
        printf(1, "expr: read error\n");
        exit();
    }
    // write(1, buffer.base, buffer.length);

    printf(1, "Evaluating:\n");
    int result = evaluate(buffer);
    printf(1, "%d\n", result);

    exit();
}

Buffer allocBuffer(int initialSize) {
    return (Buffer) {
        .base = malloc(initialSize),
        .length = 0,
        .capacity = initialSize,
    };
}

int readIntoBuffer(int fd, Buffer *buffer) {
    int result;
    while ((result = read(fd, buffer->base + buffer->length, buffer->capacity - buffer->length))) {
        buffer->length += result;
        if (buffer->length == buffer->capacity) {
            buffer->capacity *= 2;
            buffer->base = realloc(buffer->base, buffer->capacity);
        }
    }
    return result;
}

// int readIntoIntBuffer(int fd, Buffer *buffer) {
//     int result;
//     while ((result = getInt(fd))) {
//         buffer->lengthInNumberOfInts++;
//         if (buffer->lengthInNumberOfInts == buffer->capacityInNumberOfInts) {
//             buffer->capacityInNumberOfInts *= 2;
//             buffer->base = realloc(buffer->base, buffer->capacityInNumberOfInts * sizeof(int));
//         }
//     }
//     return result;
// }

int evaluate(Buffer buffer) {
    // For example: "1 + 3 - 12 + 35 - 23"
    // how many bytes are in the buffer
    // buffer->length
    enum evalState curState = NUM;

    int result = atoi(buffer.base);
    // Given that buffer.base is char *, what is the result of the following expression?
    // buffer.base + buffer.length
    // cur is char *, what is cur + 1?
    for (char *cur = buffer.base; cur != buffer.base + buffer.length; ++cur) {// Pointer arithmetic here
        if (*cur == ' ') {
            if (curState == NUM) {
                if (*(cur + 1) == '+') {
                    curState = PLUS;
                }
                else if (*(cur + 1) == '-') {
                    curState = MINUS;
                } else {
                    printf(2, "expr: invalid operator %c\n", *cur);
                    exit();
                }
            }
            else if (curState == PLUS) {
                result += atoi(cur + 1);
                curState = NUM;
            }
            else if (curState == MINUS) {
                // 3 + 2 - 1
                result -= atoi(cur + 1);
                curState = NUM;
            }
        }
    }
    // for (int cur = 0; cur < buffer.length; cur++) {
    // }

    // intBufSize is not size in bytes!
    // int intBufSize = 128;
    // int *intBuf = malloc(intBufSize * sizeof(int));
    // for (int *cur = intBuf; cur != intBuf + intBufSize; ++cur) {
    //     // do something
    // }

    return result;
}
