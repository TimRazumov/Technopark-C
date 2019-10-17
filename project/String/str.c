#include <stdio.h>
#include <stdlib.h>
#include "str.h"
#include <string.h>

String* create_str(const size_t num_byte) {
    if (!num_byte) {
        return NULL;
    }
    String* str = (String*)calloc(1, sizeof(String));
    if (!str) {
        return NULL;
    }
    str->size = num_byte;
    str->str = (char*)calloc(str->size, sizeof(char));
    if (!str->str) {
        free_str(str);
        return NULL;
    }
    return str;
}

String* create_str_from_c_str(const char* c_str) {
    if (!c_str) {
        return NULL;
    }
    String* str = create_str(strlen(c_str) + 1);  // + нулевой байт
    if (!str) {
        return NULL;
    }
    memcpy(str->str, c_str, str->size);
    return str;
}

size_t swap_str(String** l, String** r) {
    if (!l || !r) {
        return EXIT_FAILURE;
    }
    String* tmp = *l;
    *l = *r;
    *r = tmp;
    return EXIT_SUCCESS;
}

String* split_str(String* first_part, const char* separator) {
    size_t sep_len = 0;
    if (!first_part || !separator || !(sep_len = strlen(separator))) {
        return NULL;
    }
    char* tmp = strstr(first_part->str, separator);
    if (!tmp) {
        return NULL;
    }
    tmp += sep_len;
    size_t len = strlen(tmp) + 1;  // + нулевой байт
    String* second_part = create_str(len);
    if (!second_part) {
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        second_part->str[i] = tmp[i];
        tmp[i] = '\0';
    }
    for (size_t j = strlen(separator); j > 0; j--) {
        tmp--;
        *tmp = '\0';
    }
    return second_part;
}

size_t free_str(String* str) {
    if (!str) {
        return EXIT_FAILURE;
    }
    free(str->str);
    free(str);
    return EXIT_SUCCESS;
}
