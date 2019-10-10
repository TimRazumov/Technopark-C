#include <stdlib.h>
#include <stdio.h>

#include "str.h"
#include "query_info.h"


int main(int argc, const char** argv) {
    if (argc < 2) {
        return -1;
    }
    const char* url = argv[1];
    QueryInfo* query_info = create_query_info(url);
    print_query_info(query_info);
    free_query_info(query_info);
    return 0;
}
