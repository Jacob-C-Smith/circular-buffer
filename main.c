/** !
 * Circular buffer example program
 * 
 * @file main.c
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
	circular_buffer   *p_circular_buffer = 0;
	const void *const  _p_contents[]     = { "First!", "Second!", "Third!", "Fourth!", "Fifth!", "Sixth!" };

	// Log
	log_info("Creating a circular buffer\n");

	// Construct a circular buffer
	circular_buffer_from_contents(&p_circular_buffer, _p_contents, (sizeof(_p_contents) / sizeof(char *)));
	
	// Log
	log_info("\nDumping contents of circular buffer\n\n");

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
