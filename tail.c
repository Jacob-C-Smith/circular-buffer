/** !
 * tail - output the last part of a file
 * 
 * @file tail.c
 * 
 * @author Jacob Smith
 */

// Standard library
#include <stdio.h>

// log module
#include <log/log.h>

// circular buffer 
#include <circular_buffer/circular_buffer.h>

// Entry point
int main ( int argc, const char *argv[] )
{

	// Supress compiler warnings
	(void) argc;
	(void) argv;

	// Initialized data
	circular_buffer *p_circular_buffer = 0;

	// Construct a circular buffer
	circular_buffer_construct(&p_circular_buffer, 10);

    
	while ( !feof(stdin) )
	{
		

		// Pop the value
		// /circular_buffer_push(p_circular_buffer, &p_data);
	}

	// Dump the contents of the circular buffer
	while ( circular_buffer_empty(p_circular_buffer) == false )
	{
		
		// Initialized data
		void *p_data = (void *) 0;

		// Pop the value
		circular_buffer_pop(p_circular_buffer, &p_data);

		// Print the value to standard out
		printf("\"%s\"\n", (const char *)p_data);
	}

	// Success
	return EXIT_SUCCESS;
}
