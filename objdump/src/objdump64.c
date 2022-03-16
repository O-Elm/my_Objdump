/*
** EPITECH PROJECT, 2021
** objdump
** File description:
** main
*/

#include "../include/objdump.h"

void file_64_two(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr)
{
    uint16_t section_name_section = ehdr->e_shstrndx;
    uint32_t section_name_offset = shdr[section_name_section].sh_offset;
    const char *section_names = (const char *) ehdr + section_name_offset;
    for (int i = 0; i < ehdr->e_shnum; i++) {
        Elf64_Shdr *sec = shdr + i;
        size_t sec_size = sec->sh_size;
        if (sec->sh_type == SHT_NOBITS || sec->sh_offset == 0 || \
        sec_size == 0 || i == section_name_section)
            continue;
        uint32_t section_name_section_offset = sec->sh_name;
        const char *section_name = section_names + section_name_section_offset;
        if (strcmp(section_name, ".strtab") == 0 || \
        strcmp(section_name, ".symtab") == 0)
            continue;
        printf("Contents of section %s:\n", section_name);
        hex_dump(sec->sh_addr, \
        (const unsigned char *) ehdr + sec->sh_offset, sec_size);
    }
}

void file_64(Elf64_Ehdr *ehdr, char *file_name)
{
    Elf64_Shdr *shdr = (Elf64_Shdr *) ((char *)ehdr + ehdr->e_shoff);
    int flags = header_flags_64(ehdr);
    printf("\n%s:     file format elf64-x86-64\n", file_name);
    printf("architecture: i386:x86-64, flags 0x%08x:\n", flags);
    bool need_comma = false;
    if (flags & HAS_RELOC)
        print_list_element("HAS_RELOC", &need_comma);
    if (flags & EXEC_P)
        print_list_element("EXEC_P", &need_comma);
    if (flags & HAS_SYMS)
        print_list_element("HAS_SYMS", &need_comma);
    if (flags & DYNAMIC)
        print_list_element("DYNAMIC", &need_comma);
    if (flags & D_PAGED)
        print_list_element("D_PAGED", &need_comma);
    printf("\nstart address 0x%016lx\n\n", ehdr->e_entry);
    file_64_two(ehdr, shdr);
}