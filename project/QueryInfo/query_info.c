#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query_info.h"

QueryInfo* create_query_info(const char* url) {
    QueryInfo* query_info = (QueryInfo*)calloc(1, sizeof(QueryInfo));
    String* str_url = create_str_from_c_str(url);
    if (!query_info || !url || !str_url) {
        goto exit;
    }
    query_info->protocol = split_str(str_url, PROTOCOL_SEP);
    if (query_info->protocol) {
        swap_str(&query_info->protocol, &str_url);
    }
    query_info->part = split_str(str_url, PART_SEP);
    query_info->query_string = split_str(str_url, QUERY_STRING_SEP);
    query_info->doc_path = split_str(str_url, DOC_PATH_SEP);
    String* str_port = split_str(str_url, PORT_SEP);
    if (str_port) {
        query_info->port = atoi(str_port->str);
        free_str(str_port);
    } else {
        query_info->port = 4443;
    }
    query_info->num_domains = num_domains(str_url);
    query_info->domains = (String**)calloc(query_info->num_domains, sizeof(String*));
    if (!query_info->domains) {
        goto exit;
    }
    query_info->domains[0] = str_url;
    for (size_t i = 1; i < query_info->num_domains; i++) {
        query_info->domains[i] = split_str(query_info->domains[i - 1], DOMAINS_SEP);
    }
    return query_info;
    exit:
    free_query_info(query_info);
    free_str(str_url);
    return NULL;
}

size_t num_domains(const String* url) {
    size_t len_url = 0;
    if (!url || !(len_url = strlen(url->str))) {
        return 0;
    }
    size_t num = 1;
    for (size_t i = 0; i < len_url - 1; i++) {
        if (url->str[i] == *DOMAINS_SEP) {
            num++;
        }
    }
    return num;
}

int free_query_info(QueryInfo* query_info) {
    if (!query_info) {
        return -1;
    }
    free_str(query_info->protocol);
    for (size_t i = 0; i < query_info->num_domains; i++) {
        free_str(query_info->domains[i]);
    }
    free(query_info->domains);
    free_str(query_info->doc_path);
    free_str(query_info->query_string);
    free_str(query_info->part);
    free(query_info);
    return 0;
}

/*void print_query_info(const QueryInfo* query_info, FILE* output) {
    if (!query_info || !output) {
        return;
    }
    if (!output) {
        output = stdout;
    }
    if (query_info->protocol) {
        fprintf(output, "%s%s", query_info->protocol->str, PROTOCOL_SEP);
    }
    for (int i = 0; i < query_info->num_domains; i++) {
        fprintf(output, "%s", query_info->domains[i]->str);
        if (i < query_info->num_domains - 1) {
            fprintf(output, "%s", DOMAINS_SEP);
        }
    }
    fprintf(output, "%s%zu", PORT_SEP, query_info->port);
    if (query_info->doc_path) {
        fprintf(output, "%s%s", DOC_PATH_SEP, query_info->doc_path->str);
    }
    if (query_info->query_string) {
        fprintf(output, "%s%s", QUERY_STRING_SEP, query_info->query_string->str);
    }
    if (query_info->part) {
        fprintf(output, "%s%s", PART_SEP, query_info->part->str);
    }
}*/
