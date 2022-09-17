#include "user.h"

int main(int argc, char *argv[]) {
    printf(1, "argc: %d\n", argc);
    printf(1, "argv: [");
    for (int i = 0; i < argc; i++) {
        printf(1, "\"%s\"", argv[i]);
        if (i < argc - 1) {
            printf(1, ", ");
        }
    }
    printf(1, "]\n");

    int bytesRead = 0;
    int result = read(0, 0, 1);
    while (result > 0) {
        bytesRead += result;
        result = read(0, 0, 1);
    }

    if (result < 0) {
        printf(2, "shell: read error\n");
        exit();
    }
    printf(1, "bytesRead: %d\n", bytesRead);

    exit();
}
