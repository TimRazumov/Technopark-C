#ifndef PROJECT_SUBSTR_SUBSTR_H_
#define PROJECT_SUBSTR_SUBSTR_H_

#include <stddef.h>

typedef struct {
    size_t size;  // размер чанка
    size_t pos;  // относительная позиция начала макс подстроки в строке
    size_t max;  // длина максимальной подстроки в чанке
} chunk_info;

chunk_info* get_substr_info(const char* const str);
char* get_max_substr_without_repeat_from_file(const char* const file_name);

#endif  // PROJECT_SUBSTR_SUBSTR_H_
