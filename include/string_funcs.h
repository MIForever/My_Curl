#ifndef STRING_FUNCS_H
#define STRING_FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void fill_null(char* str, int size);

int my_strlen(char string[]);

int get_len(char* s1);

void m_perror(char* str);

int index_of_get(char* ip);

char* get_url(char* s1);

void my_strcat(char* dest, char* piece);

char* get_request(char* path, char* url);

#endif
