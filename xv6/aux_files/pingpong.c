#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUFSIZE 512

void ping_pong(int fd) 
{
   // ------------------------- Write your code here -------------------------
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf(1, "Usage: %s <input_file>\n", argv[0]);
        exit();
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf(1, "Error opening file %s\n", argv[1]);
        exit();
    }

    ping_pong(fd);
    close(fd);

    exit();
}
