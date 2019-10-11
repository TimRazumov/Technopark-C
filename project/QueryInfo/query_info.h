#ifndef PROJECT_QUERYINFO_QUERY_INFO_H_
#define PROJECT_QUERYINFO_QUERY_INFO_H_

#include <stddef.h>
#include "str.h"

#define PROTOCOL_SEP "://"
#define DOMAINS_SEP "."
#define PORT_SEP ":"
#define DOC_PATH_SEP "/"
#define QUERY_STRING_SEP "?"
#define PART_SEP "#"

typedef struct {
    String* protocol;  // протокол подключения
    size_t num_domains;  // кол-во доменов
    String** domains;  // доменные имена
    size_t port;  // порт
    String* doc_path;  // путь к документу
    String* query_string;  // опции запроса
    String* part;  // якорь
} QueryInfo;

QueryInfo* create_query_info(const char* url);
size_t num_domains(const String* url);
size_t free_query_info(QueryInfo* query_info);
size_t print_query_info(const QueryInfo* query_info, FILE* output);

#endif  // PROJECT_QUERYINFO_QUERY_INFO_H_
