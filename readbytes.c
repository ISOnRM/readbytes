/* readbytes <filenames> */

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static void print_usage(const char *prog) {
    fprintf(stderr, "Usage: %s <filenames>\n"
                    "-h or --help - Show this help\n"
                    "npc in ascii output is non-printable-character\n", prog);

}

static int check_args(int argc, char **argv) {
    if (argc < 2) {
        print_usage(argv[0]);
        return -1;
    }

    for (int i = 1; i < argc; ++i) {
        if (strcmp("-h", argv[i]) == 0 ||
            strcmp("--help", argv[i]) == 0) 
        {
            print_usage(argv[0]);
            return -1;
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    if (check_args(argc, argv) == -1) return 1;

    int fd;
    struct stat st;
    void *a;
    for (int i = 1; i < argc; ++i) {
        /* open and check fd */
        fd = open(argv[i], O_RDONLY);
        if (fd == -1) {
            perror("open");
            return 1;
        }

        /* check stats */
        if (fstat(fd, &st) == -1) {
            perror("fstat");
            close(fd);
            return 1;
        }

        /* check file type */
        // switch (st.st_mode & S_IFMT) {
        //     case S_IFREG: break;
        //     default: 
        //         printf("file \"%s\" is not a regular file.\n", argv[i]);
        //         close(fd);
        //         continue;
        // }
        if (!S_ISREG(st.st_mode)) {
            printf("file \"%s\" is not a regular file.\n", argv[i]);
            close(fd);
            continue;
        }

        /* check whether file size is 0 */
        /* if so then mmap will not do justice */
        if (st.st_size == 0) {
            printf("File \"%s\" is empty.\n", argv[i]);
            close(fd);
            continue;
        }

        
        /* memory map to a bytes from fd */
        a = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (a == MAP_FAILED) {
            perror("mmap");
            close(fd);
            return 1;
        }

        printf("Reading file \"%s\":\n", argv[i]);

        /* write bytes to stdout */
        for (int j = 0; j < (int)st.st_size; ++j) {
            // printf("Byte #%d: %02hhx\n", j, *((unsigned char*)(a) + j));
            unsigned char byte = *((unsigned char *)a + j);
            if (byte >= 32 && byte <= 126) {
                printf("off=0x%08x dec=%u hex=0x%02x ascii='%c'\n",
                       j, byte, byte, byte);
            } else {
                printf("off=0x%08x dec=%u hex=0x%02x ascii=npc\n",
                       j, byte, byte);
            }
        }

        /* unmap mem */
        if (munmap(a, st.st_size) == -1) {
            perror("munmap");
            close(fd);
            exit(1);
        }

        close(fd);
    }

    return 0;    
}
