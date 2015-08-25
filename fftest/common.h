#ifndef __COMMON_H__
#define __COMMON_H__

typedef struct test_entry
{
	char* name;
	int (*fun)(void*);
	int do_test;
}test_entry;

#define DECLFUN(name) int name(void*);
#define REGFUN(name, test) {#name, name, test},

#define TEST_LIST_START		\
	extern test_entry TASKS[] = {

#define TEST_LIST_END		\
	{ NULL, NULL}			\
};
#endif