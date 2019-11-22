#ifndef LIB_SUBSTR_SUBSTR_SUBSTR_H_
#define LIB_SUBSTR_SUBSTR_SUBSTR_H_

#include <stddef.h>

#define ALPHABET_SIZE 256

typedef struct {
    size_t global_pos;  // absolute position of a chunk in a line
    size_t size;  // chunk size
    size_t max_l;  // maximum substring adjacent to the left border
    size_t max_r;  // maximum substring adjacent to the right border
    size_t pos;  // relative position of the beginning of the maximum substring in the string
    size_t max;  // maximum string length in chunk
} chunk_info;

chunk_info* get_substr_info(const char* const str);
char* get_max_substr_without_repeat_from_file(const char* const file_name);

#endif  // LIB_SUBSTR_SUBSTR_SUBSTR_H_
