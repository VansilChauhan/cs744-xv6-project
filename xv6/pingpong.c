#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUFSIZE 512

void ping_pong(int fd)
{
    // ------------------------- Write your code here -------------------------
    char target[] = "ping";
    char output[] = "pong\n";
    char read_buffer[BUFSIZE];

    int n;
    while ((n = read(fd, read_buffer, BUFSIZE)) > 0)
    {
        for (int i = 0; i < n; i++)
        {
            int flag = 1;
            for (int j = 0; j < 4; j++)
            {
                if (i + j >= n)
                {
                    flag = 0;
                    break;
                }
                if (read_buffer[i + j] != target[j])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
            {
                write(1, output, 5);
                i += 3;
            }
        }
    }
    if (n < 0)
    {
        printf(1, "wc: read error\n");
        exit();
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf(1, "Usage: %s <input_file>\n", argv[0]);
        exit();
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        printf(1, "Error opening file %s\n", argv[1]);
        exit();
    }

    ping_pong(fd);
    close(fd);

    exit();
}
