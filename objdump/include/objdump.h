/*
** EPITECH PROJECT, 2021
** objdump
** File description:
** my.h
*/

#ifndef MY_OBJDUMP
#define MY_OBJDUMP

#include "flag.h"
#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int header_flags_64(Elf64_Ehdr *ehdr);
int header_flags_32(Elf32_Ehdr *ehdr);
void print_list_element(const char *str, bool *need_comma);
void hex_dump(size_t address, const unsigned char *data, size_t size);
void file_64(Elf64_Ehdr *ehdr, char *file_name);
void file_32(Elf32_Ehdr *ehdr, char *file_name);

#endif