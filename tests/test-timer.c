/*
 *  (C) Copyright 2014 Kontron Europe GmbH, Saarbruecken
 */
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <stdint.h>
#include <string.h>

#include <glib.h>
#include <glib/gstdio.h>

#include "../timer.c"


/*
 * TESTS
 */
static void test_get_timeval_to_next_slice(void)
{
	struct timespec now;
	struct timespec next;
	int interval_ms;

	now.tv_sec = 0;
	now.tv_nsec = 0;
	interval_ms = 1;
	get_timeval_to_next_slice(&now, &next, interval_ms);
	g_assert_cmpint(next.tv_sec, ==, 0);
	g_assert_cmpint(next.tv_nsec, ==, 1000000);

	now.tv_sec = 0;
	now.tv_nsec = 990000;
	interval_ms = 1;
	get_timeval_to_next_slice(&now, &next, interval_ms);
	g_assert_cmpint(next.tv_sec, ==, 0);
	g_assert_cmpint(next.tv_nsec, ==, 1000000);

	now.tv_sec = 0;
	now.tv_nsec = 999000000;
	interval_ms = 1;
	get_timeval_to_next_slice(&now, &next, interval_ms);
	g_assert_cmpint(next.tv_sec, ==, 1);
	g_assert_cmpint(next.tv_nsec, ==, 0);

	now.tv_sec = 0;
	now.tv_nsec = 0;
	interval_ms = 1000;
	get_timeval_to_next_slice(&now, &next, interval_ms);
	g_assert_cmpint(next.tv_sec, ==, 1);
	g_assert_cmpint(next.tv_nsec, ==, 0);

	now.tv_sec = 0;
	now.tv_nsec = 500000000;
	interval_ms = 1000;
	get_timeval_to_next_slice(&now, &next, interval_ms);
	g_assert_cmpint(next.tv_sec, ==, 1);
	g_assert_cmpint(next.tv_nsec, ==, 0);

	now.tv_sec = 0;
	now.tv_nsec = 999030000;
	interval_ms = 1;
	get_timeval_to_next_slice(&now, &next, interval_ms);
	g_assert_cmpint(next.tv_sec, ==, 1);
	g_assert_cmpint(next.tv_nsec, ==, 0);
}

void test_a_less_b(void)
{
	struct timespec a;
	struct timespec b;

	a.tv_sec = 0;
	a.tv_nsec = 0;
	b.tv_sec = 0;
	b.tv_nsec = 0;
	g_assert_false(a_less_b(&a, &b));

	a.tv_sec = 1;
	a.tv_nsec = 0;
	b.tv_sec = 0;
	b.tv_nsec = 0;
	g_assert_false(a_less_b(&a, &b));

	a.tv_sec = 0;
	a.tv_nsec = 124;
	b.tv_sec = 0;
	b.tv_nsec = 0;
	g_assert_false(a_less_b(&a, &b));

	a.tv_sec = 100;
	a.tv_nsec = 124;
	b.tv_sec = 100;
	b.tv_nsec = 0;
	g_assert_false(a_less_b(&a, &b));

	a.tv_sec = 0;
	a.tv_nsec = 0;
	b.tv_sec = 1;
	b.tv_nsec = 0;
	g_assert_true(a_less_b(&a, &b));

	a.tv_sec = 1;
	a.tv_nsec = 0;
	b.tv_sec = 1;
	b.tv_nsec = 12211321;
	g_assert_true(a_less_b(&a, &b));

	a.tv_sec = 1;
	a.tv_nsec = 124;
	b.tv_sec = 3;
	b.tv_nsec = 0;
	g_assert_true(a_less_b(&a, &b));
}

void test_get_timer_before_target(void)
{
	struct timespec now;
	struct timespec ts_target;
	struct itimerspec timer;

	now.tv_sec = 0;
	now.tv_nsec = 0;
	ts_target.tv_sec = 0;
	ts_target.tv_nsec = 200000;
	get_timer_before_target(200000, &now, &ts_target, &timer);
	g_assert_cmpint(timer.it_value.tv_sec, ==, 0);
	g_assert_cmpint(timer.it_value.tv_nsec, ==, 0);

	now.tv_sec = 0;
	now.tv_nsec = 0;
	ts_target.tv_sec = 1;
	ts_target.tv_nsec = 100000;
	get_timer_before_target(200000, &now, &ts_target, &timer);
	g_assert_cmpint(timer.it_value.tv_sec, ==, 1);
	g_assert_cmpint(timer.it_value.tv_nsec, ==, 999900000);

	now.tv_sec = 0;
	now.tv_nsec = 0;
	ts_target.tv_sec = 1;
	ts_target.tv_nsec = 0;
	get_timer_before_target(200000, &now, &ts_target, &timer);
	g_assert_cmpint(timer.it_value.tv_sec, ==, 1);
	g_assert_cmpint(timer.it_value.tv_nsec, ==, 999800000);

	now.tv_sec = 0;
	now.tv_nsec = 0;
	ts_target.tv_sec = 0;
	ts_target.tv_nsec = 900000000;
	get_timer_before_target(200000, &now, &ts_target, &timer);
	g_assert_cmpint(timer.it_value.tv_sec, ==, 0);
	g_assert_cmpint(timer.it_value.tv_nsec, ==, 899800000);

	now.tv_sec = 1519037653;
	now.tv_nsec = 999993435;
	ts_target.tv_sec = 1519037654;
	ts_target.tv_nsec = 0;
	get_timer_before_target(300000, &now, &ts_target, &timer);
	g_assert_cmpint(timer.it_value.tv_sec, ==, -1);
	g_assert_cmpint(timer.it_value.tv_nsec, ==, -1);

}

int main(int argc, char** argv)
{
	g_test_init(&argc, &argv, NULL);

	g_test_add_func("/timer/a/valid",
			test_get_timeval_to_next_slice);

	g_test_add_func("/timer/a_less_b/false",
			test_a_less_b);

	g_test_add_func("/timer/get_time_before_target",
			test_get_timer_before_target);


	return g_test_run();
}