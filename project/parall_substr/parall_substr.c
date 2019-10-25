#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "parall_substr.h"

#define ALPHABET_SIZE 256

chunk_info* get_substr_info(const char* const str) {
    size_t* count = (size_t*)calloc(ALPHABET_SIZE, sizeof(size_t));
    chunk_info* chunk = (chunk_info*)calloc(1, sizeof(chunk_info));
    if (!str || !count || !chunk) {
        free(count);
        free(chunk);
        return NULL;
    }
    chunk->size = strlen(str);
    for (size_t i = 0, lower_bound = 0,
        len = strlen(str); i < len; i++) {
        if (++count[str[i]] > 1) {
            for (size_t j = lower_bound; j < i; j++) {
                if (str[i] == str[j]) {
                    lower_bound = j + 1;
                    count[str[i]]--;
                    break;
                }
            }
        }
        if (i == len - 1) {
            chunk->max_r = len - lower_bound;
        }  // правая граница
        size_t tmp = i - lower_bound + 1;
        if (tmp > chunk->max) {
            chunk->max = tmp;
            chunk->pos = lower_bound;
            if (!lower_bound) {
                chunk->max_l = tmp;
            }  // левая граница
        }
    }
    free(count);
    return chunk;
}

chunk_info* merge_chunk_info(const chunk_info* const chunks, size_t num_chunks, FILE* const f) {
    if (!f || !chunks || !num_chunks) {
        return NULL;
    }
    rewind(f);
    chunk_info* merged_ch = (chunk_info*)calloc(1, sizeof(chunk_info));
    if (!merged_ch) {
    	return NULL;
    }
    *merged_ch = *chunks;
    for (size_t i = 1; i < num_chunks; i++) {
        size_t tmp_sz = merged_ch->max_r + chunks[i].max_l;
        if (merged_ch->max < chunks[i].max) {
            merged_ch->max = chunks[i].max;
            merged_ch->pos = chunks[i].global_pos + chunks[i].pos;
        }
        if (tmp_sz > merged_ch->max) {
            size_t tmp_glob_pos = chunks[i].global_pos - merged_ch->max_r;
            fseek(f, tmp_glob_pos, SEEK_SET);
            char* str = (char*)calloc(tmp_sz + 1, sizeof(char));
            if (!str) {
            	free(merged_ch);
            	return NULL;
            }
            fgets(str, tmp_sz + 1, f);
            chunk_info* tmp = get_substr_info(str);
            if (!tmp) {
            	free(str);
            	free(merged_ch);
            	return NULL;
            }
            if (merged_ch->max < tmp->max) {
                merged_ch->max = tmp->max;
                merged_ch->pos = tmp_glob_pos + tmp->pos;
            }
            free(str);
            free(tmp);
        }
        merged_ch->max_r = chunks[i].max_r;
        merged_ch->size += chunks[i].size;
    }
    return merged_ch;
}

static
int comp_chunk_info(const chunk_info* l, const chunk_info* r) {
    return l->global_pos > r->global_pos;
}

char* get_max_substr_without_repeat_from_file(const char* const file_name) {
    if (!file_name) {
        return NULL;
    }
    FILE* f = fopen(file_name, "r");
    if (!f) {
        return NULL;
    }
    int num_proc = sysconf(_SC_NPROCESSORS_ONLN);
    fseek(f, 0, SEEK_END);
    size_t file_size = ftell(f);
    size_t buff_size =  file_size / num_proc + file_size % num_proc;
    rewind(f);
    char* str = (char*)calloc(buff_size, sizeof(char));
    int file_pipes[2];
    if (pipe(file_pipes) || !str) {
        free(str);
        fclose(f);
        return NULL;
    }
    size_t glob_pos = 0;
    for (size_t i = 0; i < num_proc; i++) {
        fgets(str, buff_size, f);
        size_t len = strlen(str);
        pid_t pid = fork();
        if (!pid) {
            chunk_info* tmp = get_substr_info(str);
            if (!tmp) {
                exit(EXIT_FAILURE);
            }
            tmp->global_pos = glob_pos;
            write(file_pipes[1], tmp, sizeof(chunk_info));
            free(tmp);
            exit(EXIT_SUCCESS);
        } else if (pid == -1) {
        	exit(EXIT_FAILURE);
        }
        glob_pos += len;
    }
    free(str);
    for (size_t i = 0; i < num_proc; i++) {
        int status = 0;
        wait(&status);
        if (!WIFEXITED(status)) {
        	exit(EXIT_FAILURE);
        }
    }
    chunk_info* chunk = (chunk_info*)calloc(num_proc, sizeof(chunk_info));
    if (!chunk) {
    	fclose(f);
        return NULL;
    }
    for (size_t i = 0; i < num_proc; i++) {
        read(file_pipes[0], chunk + i, sizeof(chunk_info));
    }
    qsort(chunk, num_proc, sizeof(chunk_info), (int(*) (const void *, const void *))comp_chunk_info);
    chunk_info* res_info = merge_chunk_info(chunk, num_proc, f);
    free(chunk);
    char* res = (char*)calloc(res_info->max + 1, sizeof(char));
    fseek(f, res_info->global_pos + res_info->pos, SEEK_SET);
    fgets(res, res_info->max + 1, f);
    free(res_info);
    fclose(f);
    return res;
}
