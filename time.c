/*
 * - The Simple Graphics Utility
 * time.c
 */
#include "time.h"
#include <sys/time.h>

SGUfloat seconds_timer() {
	static struct timeval saved_time;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);

	// for now we'll assume the the frame gets 
	// rerendered in less than a second
	suseconds_t diff = current_time.tv_usec - saved_time.tv_usec;
	if (diff < 0) diff += 1000000;
	SGUfloat seconds = diff / 1000000.0;

	saved_time = current_time;

	return seconds;
}
