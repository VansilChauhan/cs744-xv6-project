#include "types.h"
#include "user.h"

#define BUFFER_SIZE 1024

int main()
{
    char data_buffer[BUFFER_SIZE];
    while (1)
    {
        int cid = fork();
        if (cid == 0)
        {
            write(1, ">>> ", 4);
            int read_bytes = read(0, data_buffer, BUFFER_SIZE);
            data_buffer[read_bytes] = '\0';
            write(1, data_buffer, read_bytes + 1);
        }
        else
        {
            wait();
        }
    }
    exit();
}