#ifndef __COROUTINE_H__
#define __COROUTINE_H__

/* The credit belongs to Tom Duff and Simon Tatham */

#include <stdlib.h>
#include <string.h>

typedef struct coroutine {
	int   init;
	int   line;
	void *vars;
} coroutine_t;

#define coroutine_define(c,a)					\
	do {							\
		(c)->init = 1;					\
		if ((c)->vars == NULL) {			\
			(c)->line = 0;				\
			(c)->vars = malloc(sizeof(*(a)));	\
		}						\
		(a) = (c)->vars;				\
	} while (0)

#define coroutine_began(c)					\
	if ((c)->vars != NULL)					\
		switch ((c)->line) {				\
		case 0:
			
#define coroutine_yield(c,r)					\
	do {							\
		(c)->line = __LINE__;				\
		return (r);					\
		case __LINE__:;					\
	} while (0)

#define coroutine_return(c,r)					\
	do {							\
		free((c)->vars);				\
		(c)->vars = NULL;				\
		return (r);					\
	} while (0)

#define coroutine_ended(c,r)					\
	}							\
	free((c)->vars);					\
	(c)->vars = NULL;					\
	return (r)

#define coroutine_init(c)					\
	do {							\
		(c)->init = 0;					\
		(c)->line = 0;					\
		(c)->vars = NULL;				\
	} while (0)

#define coroutine_next(c)					\
	(!(c)->init || ((c)->init && (c)->vars != NULL))

#define coroutine_deinit(c)					\
	do {							\
		free((c)->vars);				\
		(c)->vars = NULL;				\
	} while (0)

#endif /* __COROUTINE_H__ */
