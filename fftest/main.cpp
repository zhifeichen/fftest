#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

DECLFUN(muxer_mp4)
DECLFUN(muxer_ts)
DECLFUN(demuxer_ts)
DECLFUN(std_function_test)
DECLFUN(rest_test)

TEST_LIST_START
	REGFUN(muxer_mp4, 0)
	REGFUN(muxer_ts, 0)
	REGFUN(demuxer_ts, 0)
	REGFUN(std_function_test, 0)
	REGFUN(rest_test, 1)
TEST_LIST_END

void print_task(void)
{
    int index = 0;
    printf("all test are: \n");
    while (TASKS[index].name) {
        printf("\t%s\n", TASKS[index].name);
        index++;
    }
}

int test_all(void)
{
    int index = 0;
    printf("do all test if need: \n");
    while (TASKS[index].name) {
        if (TASKS[index].do_test) {
            printf("\ttest %s: \n", TASKS[index].name);
            TASKS[index].fun(NULL);
        }
        else {
            printf("\tskip test %s\n", TASKS[index].name);
        }
        index++;
    }
    return 0;
}

int find_task(const char* name)
{
    int result = -1;
    int i = 0;
    while (TASKS[i].name) {
        if (strcmp(name, TASKS[i].name) == 0) {
            result = i;
            break;
        }
        i++;
    }
    return result;
}

int test_task(const char* name)
{
    int finded;
    finded = find_task(name);
    if (finded < 0) {
        printf("can not find test %s!\n", name);
        return -1;
    }
    else {
        printf("testting %s...\n", name);
        return TASKS[finded].fun(NULL);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        print_task();
        test_all();
    }
    else {
        test_task(argv[1]);
    }
    return 0;
}