#include "user.h"
#define BUFSIZE 512

void printBuf(char *buf, int n) {
    printf(1, "buffer content: ");
    for (int i = 0; i < n; i++) {
        printf(1, "%d ", buf[i], buf[i]);
    }

    printf(1, "\n");
}

int main(int argc, char *argv[]) {
    // open
    // read
    // write
    // close
    int fd;
    // char buf[BUFSIZE];

    // Open the file with the appropriate flag
    // O_RDONLY O_WRONLY O_CREATE
    fd = open("new.txt", O_RDWR | O_CREATE);
    printf(1, "fd is: %d\n", fd);

    // Create a buffer
    int result;
    int bufSize = 512;
    int bytesRead = 0;
    char *buf = malloc(bufSize);

    // Read into the buffer
    // Buffer struct 01:15:00
    while ((result = read(fd, buf, bufSize - bytesRead)) > 0) {
        bytesRead += result;
        if (bytesRead == bufSize) {
            bufSize *= 2;
            buf = realloc(buf, bufSize);
        }
    }

    // Error handling (optional for assignments)
    if (result < 0) {
        printf(2, "open: read error");
        exit();
    }

    // Do whatever you want with the buffer
    printBuf(buf, bytesRead);

    // fd = open("output.txt", O_RDONLY);
    // result = write(fd, buf, bytesRead);

    // Since printf accepts a file descriptor as the
    // first argument, we can use it to write to the
    // file as well.
    printf(fd, "bytes read: %d\n", bytesRead);
    // Be careful with C-strings! Don't confuse a buffer with a C-string

    // We can also "write" to the standard output
    // printf(fd, "buf: %s\n", buf);
    result = write(1, buf, bytesRead);
    printf(fd, "bytes written: %d\n", result);

    // Good practice
    close(fd);

    // exit closes all the files anyway
    exit();
}
