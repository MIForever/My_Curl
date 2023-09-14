#include "../include/string_funcs.h"

void fill_null(char* str, int size){
    int i = 0; 
    while(i < size){
        str[i] = 0;
        i++;
    }
}

int my_strlen(char string[]){
    int len=0;
    while(string[len]){
        len++;
    }
    return len;
}


int get_len(char* s1){
    int i = 0;
    for(; s1[i] ; i++){
        if(s1[i] == '/'){
            break;
        }
    }
    return i;
}


void m_perror(char* str){
    write(2, str, my_strlen(str));
}


int index_of_get(char* ip){
    for(int i = 0; ip[i]; i++){
        if(i > 8 && ip[i] == '/'){
            return i;
        }
    }
    return 0;
}


char* get_url(char* s1){
    int end = get_len(s1);
    char* res = malloc(sizeof(char)*end + 1);
    int i;
    for(i = 0; i < end; i++){
        res[i] = s1[i];
    }
    res[i] = '\0';
    return res;
}


void my_strcat(char* dest, char* piece){
    int len1= my_strlen(dest);
    int len2= my_strlen(piece);
    int index=0;
    for(int i=len1; index<len2; i++){
        dest[i]=piece[index];
        index++;
    }
}


char* get_request(char* path, char* url){
    char part1[] = "GET ";
    char part2[] = " HTTP/1.1\r\nHost: ";
    char part3[] = "\r\n\r\n";
    char* res = calloc(my_strlen(path)+my_strlen(url)+27,sizeof(char));

    my_strcat(res, part1);
    my_strcat(res, path);
    my_strcat(res, part2);
    my_strcat(res, url);
    my_strcat(res, part3);
    
    return res;
}