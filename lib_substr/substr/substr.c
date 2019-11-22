#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "substr.h"

chunk_info* get_substr_info(const char* const str) {
    if (!str) {
        return NULL;
    }
    size_t* count = (size_t*)calloc(ALPHABET_SIZE, sizeof(size_t));
    if (!count) {
        return NULL;
    }
    chunk_info* chunk = (chunk_info*)calloc(1, sizeof(chunk_info));
    if (!chunk) {
        free(count);
        return NULL;
    }
    chunk->size = strlen(str);
    for (size_t i = 0, lower_bound = 0; i < chunk->size; i++) {
        if (++count[str[i]] > 1) {
            for (size_t j = lower_bound; j < i; j++) {
                if (str[i] == str[j]) {
                    lower_bound = j + 1;
                    count[str[i]]--;
                    break;
                }  // find the position of the repeating character
            }
        }
        if (i == chunk->size - 1) {
            chunk->max_r = chunk->size - lower_bound;
        }  // counting at the right border
        size_t tmp = i - lower_bound + 1;
        if (tmp > chunk->max) {
            chunk->max = tmp;
            chunk->pos = lower_bound;
            if (!lower_bound) {
                chunk->max_l = tmp;
            }  // counting at the left border
        }
    }
    free(count);
    return chunk;
}

char* get_max_substr_without_repeat_from_file(const char* const file_name) {
    if (!file_name) {
        return NULL;
    }
    FILE* f = fopen(file_name, "r");
    if (!f) {
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    size_t buff_size = ftell(f) + 1;
    rewind(f);
    char* str = (char*)calloc(buff_size, sizeof(char));
    if (!str) {
        fclose(f);
        return NULL;
    }
    fgets(str, buff_size, f);
    fclose(f);
    chunk_info* info = get_substr_info(str);
    if (!info) {
        free(str);
        return NULL;
    }
    char* res = (char*)calloc(info->max + 1, sizeof(char));
    if (!res) {
        free(str);
        free(info);
        return NULL;
    }
    memcpy(res, str + info->pos, info->max);
    free(info);  // find the position of the maximum line and read
    free(str);
    return res;
}
