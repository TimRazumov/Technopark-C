#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "str.h"

String* create_str(const size_t byte) {
    String* str = (String*)calloc(1, sizeof(String));
    if (!str) {
        goto exit;
    }
    str->size = byte;
    str->str = (char*)calloc(str->size, sizeof(char));
    if (!str->str) {
        goto exit;
    }
    return str;
    exit:
    free_str(str);
    return NULL;
}

String* create_str_from_c_str(const char* c_str) {
    if (!c_str) {
        return NULL;
    }
    String* str = create_str(strlen(c_str) + 1);  // + нулевой байт
    if (!str) {
        free_str(str);
        return NULL;
    }
    for (size_t i = 0; i < str->size; i++) {
        str->str[i] = c_str[i];
    }
    return str;
}

int swap_str(String** l, String** r) {
    if (!l || !r) {
        return -1;
    }
    String* tmp = *l;
    *l = *r;
    *r = tmp;
    return 0;
}

String* split_str(String* first_part, const char* separator) {
    if (!first_part || !separator) {
        return NULL;
    }
    char* tmp = strstr(first_part->str, separator);  // нашли место которое возвращаем
    if (!tmp) {
        return NULL;
    }
    size_t sep_len = strlen(separator);
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

int free_str(String* str) {
    if (!str) {
        return -1;
    }
    free(str->str);
    free(str);
    return 0;
}

/*

TARGET = main.out

# XXX: Don't forget backslash at the end of any line except the last one
HDRS = \
	   project/include

SRCS = \
       project/src/main.c \
       project/src/str.c  \
       project/src/query_info.c

.PHONY: all clean

all: $(SRCS)
	$(CC) -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS)

clean:
	rm -rf $(TARGET)

*/
