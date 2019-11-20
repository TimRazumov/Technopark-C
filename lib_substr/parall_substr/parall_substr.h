#ifndef PROJECT_PARALL_SUBSTR_PARALL_SUBSTR_H_
#define PROJECT_PARALL_SUBSTR_PARALL_SUBSTR_H_

#include <stddef.h>
#include "substr.h"

chunk_info* merge_chunk_info(const chunk_info* const chunks, size_t num_chunks, FILE* const f);
char* get_max_substr_without_repeat_from_file_parall(const char* const file_name);

#endif  // PROJECT_PARALL_SUBSTR_PARALL_SUBSTR_H_
