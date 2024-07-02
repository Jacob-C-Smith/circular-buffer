/** !
 * Circular buffer example program
 * 
 * @file main.c
 * 
 * @author Jacob Smith
 */

// Standard library
#include <stdio.h>

// circular buffer module
#include <circular_buffer/circular_buffer.h>

// Entry point
int main ( int argc, const char *argv[] )
{

	// Supress compiler warnings
	(void) argc;
	(void) argv;

	// Initialized data
	circular_buffer *p_circular_buffer = 0;
	char            *pp_contents[]     = { "First!", "Second!", "Third!", "Fourth!", "Fifth!", "Sixth!", 0x0 };

	// Construct a circular buffer
	circular_buffer_construct(&p_circular_buffer, 4);
		
	// Populate the circular buffer
	for (size_t i = 0; i < 6; i++)

		// Add a value to the circular buffer
		circular_buffer_push(p_circular_buffer, pp_contents[i]);

	// Dump the contents of the circular buffer
	while ( circular_buffer_empty(p_circular_buffer) == false )
	{
		
		// Initialized data
		void *p_data = (void *) 0;

		// Pop the value
		circular_buffer_pop(p_circular_buffer, &p_data);

		// Print the value to standard out
		printf("%s\n", (const char *)p_data);
	}

	// Success
	return EXIT_SUCCESS;
}