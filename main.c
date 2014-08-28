#include <stdio.h>

#include "coroutine.h"

int
producer(char *r)
{
	memcpy(r, "hello", strlen("hello"));
	return 0;
}

int
consumer(coroutine_t *c)
{
	struct {
		char foo[1000];
	} *v;

	/* code in here will execute every time */

	coroutine_define(c, v);	/* init and allocate sizeof(*v) memory */

	/* code in here will execute every time */

	coroutine_began(c);	/* setup coroutine execute switch-case */

	/* code in here only execute in first time */

	coroutine_yield(c, producer(v->foo));			/* case 1 */
	printf("%s\n", v->foo);

	coroutine_yield(c, producer(v->foo + strlen(v->foo)));	/* case 2 */
	printf("%s\n", v->foo);

	coroutine_ended(c, 0);	/* finish up switch-case and release *v */
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
