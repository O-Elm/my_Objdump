/*
** EPITECH PROJECT, 2021
** objdump
** File description:
** main
*/

#include "../include/objdump.h"

int header_flags_64(Elf64_Ehdr *ehdr)
{
    int flags = BFD_NO_FLAGS;
    if (ehdr->e_type == ET_EXEC)
        flags += EXEC_P + D_PAGED + HAS_SYMS;
    if (ehdr->e_type == ET_DYN)
        flags += DYNAMIC + D_PAGED + HAS_SYMS;
    if (ehdr->e_type == ET_REL)
        flags += HAS_RELOC + HAS_SYMS;
    return flags;
}

int header_flags_32(Elf32_Ehdr *ehdr)
{
    int flags = BFD_NO_FLAGS;
    if (ehdr->e_type == ET_EXEC)
        flags += EXEC_P + D_PAGED + HAS_SYMS;
    if (ehdr->e_type == ET_DYN)
        flags += DYNAMIC + D_PAGED + HAS_SYMS;
    if (ehdr->e_type == ET_REL)
        flags += HAS_RELOC + HAS_SYMS;
    return flags;
}

void print_list_element(const char *str, bool *need_comma)
{
    if (*need_comma)
        printf(", ");
    printf("%s", str);
    *need_comma = true;
}

void hex_dump_two(size_t i, const unsigned char *data, size_t size)
{
    for (size_t byte = 0; byte < 16; byte++) {
        if (i + byte < size) {
            unsigned char c = data[i + byte];
            if (c >= 32 && c <= 126)
                printf("%c", c);
            else
                printf(".");
        } else {
            printf(" ");
        }
    }
}

void hex_dump(size_t address, const unsigned char *data, size_t size)
{
    char dummy[20];
    int padding = snprintf(dummy, sizeof(dummy), "%04lx", address + size - 1);
    char string[] = " %04lx";
    string[3] = '0' + padding;
    for (size_t i = 0; i < size; i += 16) {
        printf(string, address + i);
        for (size_t byte = 0; byte < 16 ; byte++) {
            if (byte % 4 == 0)
                printf(" ");
            if (i + byte < size) {
                printf("%02x", data[i + byte]);
            }
            else {
                printf("  ");
            }
        }
        printf("  ");
        hex_dump_two(i, data, size);
        printf("\n");}
}