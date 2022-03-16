/*
** EPITECH PROJECT, 2021
** objdump
** File description:
** main
*/

#include "../include/objdump.h"

bool error_size_32(struct stat s, int fd, char *file_name)
{
    Elf32_Ehdr ehdr;
    unsigned int size;
    if (read(fd, &ehdr, sizeof(ehdr)) == -1)
        return false;
    size = ehdr.e_shoff + (ehdr.e_shentsize * ehdr.e_shnum);
    if (size != s.st_size) {
        fprintf(stderr, "my_objdump: %s: file format not recognized\n", \
        file_name);
        return false;
    }
    return true;
}

bool error_size(struct stat s, int fd, char *file_name)
{
    Elf64_Ehdr ehdr;
    unsigned int size;
    if (read(fd, &ehdr, sizeof(ehdr)) == -1)
        return false;
    size = ehdr.e_shoff + (ehdr.e_shentsize * ehdr.e_shnum);
    if (size != s.st_size) {
        fprintf(stderr, "my_objdump: %s: file format not recognized\n", \
        file_name);
        return false;
    }
    return true;
}

bool check_file(void * buf, struct stat s, char *file_name, int fd)
{
    unsigned char *e_ident;
    e_ident = (unsigned char *)buf;
    if ((long unsigned int)s.st_size < sizeof(Elf64_Ehdr) || \
    e_ident[EI_MAG0] != 0x7F || e_ident[EI_MAG1] != 0x45 || \
    e_ident[EI_MAG2] != 0x4c || e_ident[EI_MAG3] != 0x46) {
        fprintf(stderr, "my_objdump: %s: file format not recognized\n", \
        file_name);
        return false;
    }
    if (e_ident[EI_CLASS] != ELFCLASS64) {
        if (!error_size_32(s, fd, file_name))
            return false;
        file_32((Elf32_Ehdr *)buf, file_name);
    } else {
        if (!error_size(s, fd, file_name))
            return false;
        file_64((Elf64_Ehdr *)buf, file_name);
    }
    munmap(buf, s.st_size);
    close(fd);
    return true;
}

bool open_file(char *file_name)
{
    int fd;
    void *buf;
    struct stat s;
    fd = open(file_name, O_RDONLY);
    if (fd != -1) {
        fstat(fd, &s);
        buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (buf != (void *)(-1))
            return (check_file(buf, s, file_name, fd));
    }
    fprintf(stderr, "my_objdump: '%s': No such file\n", file_name);
    return false;
}

int main(int ac, char **av)
{
    if (ac == 1) {
        if (!open_file("a.out")) {
            return 84;
        }
        return 0;
    }
    for (int i = 1; i < ac; i++) {
        if (!open_file(av[i])) {
            return 84;
        }
    }
    return 0;
}
