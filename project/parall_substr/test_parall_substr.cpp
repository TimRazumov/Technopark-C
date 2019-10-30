#include <gtest/gtest.h>

extern "C" {
    #include "parall_substr.h"
}

TEST(substr, get_substr_info) {
	FILE* f = fopen("tests/test1.txt", "r");
	if (!f) {
		return;
	}
	fseek(f, 0, SEEK_END);
    size_t file_size = ftell(f);
    rewind(f);
    char* str = (char*)calloc(file_size + 1, sizeof(char));
    if (!str) {
    	fclose(f);
    	return;
    }
    fgets(str, file_size + 1, f);
	chunk_info* info = get_substr_info(str);
    free(str);
    fclose(f);
	if (!info || info->size != 691 || info->pos != 671 || info->max != 5) {
		GTEST_FAIL() << " Wrong answer";
        free(info);
		return;
	}
	free(info);

    f = fopen("tests/test2.txt", "r");
	if (!f) {
		return;
	}
	fseek(f, 0, SEEK_END);
    file_size = ftell(f);
    rewind(f);
    str = (char*)calloc(file_size + 1, sizeof(char));
    if (!str) {
    	fclose(f);
    	return;
    }
    fgets(str, file_size + 1, f);
	info = get_substr_info(str);
    free(str);
    fclose(f);
	if (!info || info->size != 1048576 || info->pos != 47913 || info->max != 20) {
		GTEST_FAIL() << " Wrong answer";
        free(info);
		return;
	}
	free(info);

	f = fopen("tests/test3.txt", "r");
	if (!f) {
		return;
	}
	fseek(f, 0, SEEK_END);
    file_size = ftell(f);
    rewind(f);
    str = (char*)calloc(file_size + 1, sizeof(char));
    if (!str) {
    	fclose(f);
    	return;
    }
    fgets(str, file_size + 1, f);
	info = get_substr_info(str);
    free(str);
    fclose(f);
	if (!info || info->size != 104857600 || info->pos != 51843502 || info->max != 24) {
		GTEST_FAIL() << " Wrong answer";
        free(info);
		return;
	}
	free(info);
	return;
}

TEST(parall_substr, get_max_substr_without_repeat_from_file) {
	char* str = get_max_substr_without_repeat_from_file("tests/test1.txt");  // 700 b
	if (!str) {
        GTEST_FAIL() << " Error";
	    return;
	}
    if (strcmp(str, "kwjhl")) {
		GTEST_FAIL() << " Wrong answer";
		return;
	}
	free(str);

	str = get_max_substr_without_repeat_from_file("tests/test2.txt");  // 1 mb
	if (!str) {
		GTEST_FAIL() << " Error";
		return;
	}
	if (strcmp(str, "vyrkhudsoqintcgafjeb")) {
		GTEST_FAIL() << " Wrong answer";
		return;
	}
	free(str);

	str = get_max_substr_without_repeat_from_file("tests/test3.txt");  // 100 mb
	if (!str) {
		GTEST_FAIL() << " Error";
		return;
	}
	if (strcmp(str, "wtklaehqozdcrvxnpibfjymu")) {
		GTEST_FAIL() << " Wrong answer";
		return;
	}
	free(str);
	return;
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
