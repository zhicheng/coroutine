#include <stdio.h>

#include "coroutine.h"

int
producer(char *r)
{
	memcpy(r, "hello", sizeof("hello"));
	return 0;
}

int
consumer(coroutine_t *c)
{
	struct foo {
		char foo[1000];
	} *foo;

	coroutine_define(c, foo);

	coroutine_began(c);

	coroutine_yield(c, producer(foo->foo));
	printf("%s\n", foo->foo);

	coroutine_yield(c, producer(foo->foo + strlen(foo->foo)));
	printf("%s\n", foo->foo);

	coroutine_ended(c, 0);
}

int
main(void)
{
	coroutine_t c;
	coroutine_init(&c);
	
	while (coroutine_next(&c)) {
		consumer(&c);
	}
	coroutine_deinit(&c);
}
