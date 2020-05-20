/*
 * Copyright 2010-2015, Tarantool AUTHORS, please see AUTHORS file.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * 1. Redistributions of source code must retain the above
 *    copyright notice, this list of conditions and the
 *    following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * <COPYRIGHT HOLDER> OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include "third_party/queue.h"
#include "unit.h"
#include <stdio.h>

struct elem
{
	STAILQ_ENTRY(elem) entry;
	int val;
};

STAILQ_HEAD(elem_queue, elem);

const char *
queue2str(struct elem_queue *queue)
{
	static char buf[1024];
	buf[0] = '\0';
	struct elem *elem;
	int n = 0;
	STAILQ_FOREACH(elem, queue, entry) {
		n += snprintf(buf + n, sizeof(buf) - n - 1, "%d ", elem->val);
	}
	return buf;
}

/** Test a queue with 0 elements. */
void test0()
{
	header();
	plan(1);
	struct elem_queue queue = STAILQ_HEAD_INITIALIZER(queue);
	note("Initialized: %s", queue2str(&queue));
	STAILQ_INIT(&queue);
	note("STAILQ_INIT: %s", queue2str(&queue));
	STAILQ_REVERSE(&queue, elem, entry);
	note("STAILQ_REVERSE: %s", queue2str(&queue));
	ok(1, "test 0");
	check_plan();
	footer();
}

/** Test a queue with 1 element. */
void test1()
{
	header();
	plan(1);
	struct elem el1;
	struct elem_queue queue = STAILQ_HEAD_INITIALIZER(queue);
	el1.val = 1;
	STAILQ_INSERT_TAIL(&queue, &el1, entry);
	note("STAILQ_INIT: %s", queue2str(&queue));
	STAILQ_REVERSE(&queue, elem, entry);
	note("STAILQ_REVERSE: %s", queue2str(&queue));
	ok(1, "test 1");
	check_plan();
	footer();
}


void test2()
{
	header();
	plan(1);
	struct elem el1, el2;
	struct elem_queue queue = STAILQ_HEAD_INITIALIZER(queue);
	el1.val = 1;
	el2.val = 2;
	STAILQ_INSERT_TAIL(&queue, &el1, entry);
	STAILQ_INSERT_TAIL(&queue, &el2, entry);
	note("STAILQ_INIT: %s", queue2str(&queue));
	STAILQ_REVERSE(&queue, elem, entry);
	note("STAILQ_REVERSE: %s", queue2str(&queue));
	ok(1, "test 2");
	check_plan();
	footer();
}

void test3()
{
	header();
	plan(1);
	struct elem el1, el2, el3;
	struct elem_queue queue = STAILQ_HEAD_INITIALIZER(queue);
	el1.val = 1;
	el2.val = 2;
	el3.val = 3;
	STAILQ_INSERT_TAIL(&queue, &el1, entry);
	STAILQ_INSERT_TAIL(&queue, &el2, entry);
	STAILQ_INSERT_TAIL(&queue, &el3, entry);
	note("STAILQ_INIT: %s", queue2str(&queue));
	STAILQ_REVERSE(&queue, elem, entry);
	note("STAILQ_REVERSE: %s", queue2str(&queue));
	ok(1, "test 3");
	check_plan();
	footer();
}


void test_splice()
{
	header();
	plan(1);
	struct elem el1, el2, el3;
	struct elem_queue queue1 = STAILQ_HEAD_INITIALIZER(queue1);
	struct elem_queue queue2 = STAILQ_HEAD_INITIALIZER(queue2);
	STAILQ_SPLICE(&queue1, STAILQ_FIRST(&queue1), entry, &queue2);
	note("q1: %s", queue2str(&queue1));
	note("q2: %s", queue2str(&queue2));
	STAILQ_SPLICE(&queue2, STAILQ_FIRST(&queue2), entry, &queue1);
	note("q1: %s", queue2str(&queue1));
	note("q2: %s", queue2str(&queue2));
	el1.val = 1;
	el2.val = 2;
	el3.val = 3;
	STAILQ_INSERT_TAIL(&queue1, &el1, entry);
	STAILQ_INSERT_TAIL(&queue1, &el2, entry);
	STAILQ_INSERT_TAIL(&queue1, &el3, entry);
	note("STAILQ_INIT: %s", queue2str(&queue1));
	STAILQ_SPLICE(&queue1, STAILQ_FIRST(&queue1), entry, &queue2);
	note("q1: %s", queue2str(&queue1));
	note("q2: %s", queue2str(&queue2));
	STAILQ_SPLICE(&queue2, STAILQ_FIRST(&queue2), entry, &queue1);
	note("q1: %s", queue2str(&queue1));
	note("q2: %s", queue2str(&queue2));
	STAILQ_SPLICE(&queue1, STAILQ_NEXT(STAILQ_FIRST(&queue1), entry),
					   entry, &queue2);
	note("q1: %s", queue2str(&queue1));
	note("q2: %s", queue2str(&queue2));
	STAILQ_SPLICE(&queue2, STAILQ_NEXT(STAILQ_FIRST(&queue2), entry),
		      entry, &queue1);
	note("q1: %s", queue2str(&queue1));
	note("q2: %s", queue2str(&queue2));
	STAILQ_SPLICE(&queue2, STAILQ_FIRST(&queue2), entry, &queue1);
	note("q1: %s", queue2str(&queue1));
	note("q2: %s", queue2str(&queue2));
	ok(1, "test splice");
	footer();
}

int main()
{
	plan(5);
	test0();
	test1();
	test2();
	test3();
	test_splice();
	check_plan();
	return 0;
}
