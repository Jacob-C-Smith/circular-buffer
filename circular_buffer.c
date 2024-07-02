/** !
 * Circular buffer implementation
 * 
 * @file circular_buffer.c
 * 
 * @author Jacob Smith
 */

// Header
#include <circular_buffer/circular_buffer.h>

// Structure definitions
struct circular_buffer_s
{
	bool full;
	size_t read, write, length;
	mutex _lock;
	void *_p_data[];
};

// Function definitions
int circular_buffer_create ( circular_buffer **const pp_circular_buffer )
{

	// Argument check
	if ( pp_circular_buffer == (void *) 0 ) goto no_circular_buffer;

	// Initialized data
	circular_buffer *ret = CIRCULAR_BUFFER_REALLOC(0, sizeof(circular_buffer));

	// Error check
	if ( ret == (void *)0 ) goto no_mem;

	// Zero set
	memset(ret, 0, sizeof(circular_buffer));

	// Return a pointer to the caller
	*pp_circular_buffer = ret;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_circular_buffer:
				#ifndef NDEBUG
					log_error("[circular buffer] Null pointer provided for \"pp_circular_buffer\" in call to function \"%s\"\n",__FUNCTION__);
				#endif

				// Error
				return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					log_error("[Standard Library] Failed to allocate memory in call to function \"%s\"\n",__FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}
 
int circular_buffer_construct ( circular_buffer **const pp_circular_buffer, size_t size )
{

	// Argument check
	if ( pp_circular_buffer == (void *) 0 ) goto no_circular_buffer;
	if ( size               ==          0 ) goto no_size;

	// Initialized data
	circular_buffer *p_circular_buffer = 0;

	// Allocate memory for a circular buffer
	if ( circular_buffer_create(&p_circular_buffer) == 0 ) goto failed_to_create_circular_buffer;

	// Grow the circular buffer
	p_circular_buffer = CIRCULAR_BUFFER_REALLOC(p_circular_buffer, sizeof(circular_buffer) * ( size * sizeof(void *) ));

	// Error check
	if ( p_circular_buffer == (void *) 0 ) goto no_mem;

	// Store the size of the circular buffer
	p_circular_buffer->length = size;

	// Create a mutex
    if ( mutex_create(&p_circular_buffer->_lock) == 0 ) goto failed_to_create_mutex;

	// Return a pointer to the caller
	*pp_circular_buffer = p_circular_buffer;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_circular_buffer:
				#ifndef NDEBUG
					log_error("[circular buffer] Null pointer provided for parameter \"pp_circular_buffer\" in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
				// Error
				return 0;

			no_size:
				#ifndef NDEBUG
					log_error("[circular buffer] Parameter \"size\" must be greater than zero in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
				// Error
				return 0;
		}

		// Circular buffer errors
		{
			failed_to_create_circular_buffer:
				#ifndef NDEBUG
					log_error("[circular buffer] Failed to allocate circular buffer in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
			
			failed_to_create_mutex:
                #ifndef NDEBUG
                    log_error("[circular buffer] Failed to create mutex in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					log_error("[Standard Library] Failed to allocate memory in call to function \"%s\"\n",__FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int circular_buffer_from_contents ( circular_buffer **const pp_circular_buffer, void* const* const pp_contents, size_t size )
{

	// Argument check
	if ( pp_circular_buffer == (void *) 0 ) goto no_circular_buffer;
	if ( pp_contents        == (void *) 0 ) goto no_circular_buffer_contents;
	if ( size               ==          0 ) goto no_circular_buffer_contents;

	// Initialized data
	circular_buffer *p_circular_buffer = (void *) 0;

	// Construct a circular buffer
	if ( circular_buffer_construct(&p_circular_buffer, size) == 0 ) goto failed_to_construct_circular_buffer;
	
	// Iterate over each item
	for (size_t i = 0; i < size; i++)

		// Add the item to the circular buffer
		; // circular_buffer_enqueue(p_circular_buffer, pp_contents[i]);
	
	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_circular_buffer:
				#ifndef NDEBUG
					log_error("[circular buffer] Null pointer provided for parameter \"pp_circular_buffer\" in call to function \"%s\"\n",__FUNCTION__);
				#endif
			
				// Error
				return 0;

			no_circular_buffer_contents:
				#ifndef NDEBUG
					log_error("[circular buffer] Circular buffer has no contents in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
				// Error
				return 0;
		}

		// Circular buffer errors
		{
			failed_to_construct_circular_buffer:
				#ifndef NDEBUG
					log_error("[circular buffer] Failed to construct circular buffer in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
				// Error
				return 0;
		}
	}
}

bool circular_buffer_empty ( circular_buffer *const p_circular_buffer )
{
	
	// Argument check
	if ( p_circular_buffer == (void *)0 ) goto no_circular_buffer;

	// Lock
	mutex_lock(&p_circular_buffer->_lock);

	// Initialized data
	bool ret = ( p_circular_buffer->full == false && p_circular_buffer->read == p_circular_buffer->write );

	// Unlock
	mutex_unlock(&p_circular_buffer->_lock);
	
	// Success
	return ret;
	
	// Error handling
	{

		// Argument errors
		{
			no_circular_buffer:
				#ifndef NDEBUG
					log_error("[circular buffer] Null pointer provided for parameter \"p_circular_buffer\" in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
				// Error
				return 0;
		}
	}
}

bool circular_buffer_full ( circular_buffer *const p_circular_buffer )
{
	
	// Argument check
	if ( p_circular_buffer == (void *)0 ) goto no_circular_buffer;

	// Lock
	mutex_lock(&p_circular_buffer->_lock);

	// Initialized data
	bool ret = p_circular_buffer->full;

	// Unlock
	mutex_unlock(&p_circular_buffer->_lock);
	
	// Success
	return ret;
	
	// Error handling
	{

		// Argument errors
		{
			no_circular_buffer:
				#ifndef NDEBUG
					log_error("[circular buffer] Null pointer provided for parameter \"p_circular_buffer\" in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
				// Error
				return 0;
		}
	}
}

int circular_buffer_push ( circular_buffer *const p_circular_buffer, void *p_data )
{

	// Argument check
	if ( p_circular_buffer == (void *) 0 ) goto no_circular_buffer;
	if ( p_data            == (void *) 0 ) goto no_data;
		
	// Lock
	mutex_lock(&p_circular_buffer->_lock);

	// Store the element
	p_circular_buffer->_p_data[p_circular_buffer->write] = p_data;

	// Update the write index
	p_circular_buffer->write = ( p_circular_buffer->write + 1 ) % p_circular_buffer->length;

	// Handle overflows
	if ( p_circular_buffer->full ) goto overflow;

	// Update the full flag
	p_circular_buffer->full = ( p_circular_buffer->read == p_circular_buffer->write );

	// Unlock
	mutex_unlock(&p_circular_buffer->_lock);

	// Success
	return 1;

	overflow:
	{

		// Update the read index
		p_circular_buffer->read = ( p_circular_buffer->read + 1 ) % p_circular_buffer->length;

		// Unlock
		mutex_unlock(&p_circular_buffer->_lock);

		// Success
		return 1;
	}

	// Error handling
	{

		// Argument errors
		{
			no_circular_buffer:
				#ifndef NDEBUG
					log_error("[circular buffer] Null pointer provided for parameter \"p_circular_buffer\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;

			no_data:
				#ifndef NDEBUG
					log_error("[circular buffer] Null pointer provided for parameter \"p_data\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int circular_buffer_peek ( circular_buffer *const p_circular_buffer, void **pp_data )
{

	// Argument check
	if ( p_circular_buffer == (void *) 0 ) goto no_circular_buffer;
	if ( pp_data           == (void *) 0 ) goto no_data;

	// Lock
	mutex_lock(&p_circular_buffer->_lock);

	// State check
	if ( p_circular_buffer->read == p_circular_buffer->write ) goto circular_buffer_empty;

	// Return data to the caller
	*pp_data = p_circular_buffer->_p_data[p_circular_buffer->read];

	// Unlock
	mutex_unlock(&p_circular_buffer->_lock);

	// Success
	return 1;

	// Empty
	circular_buffer_empty:
	{

		// Unlock
		mutex_unlock(&p_circular_buffer->_lock);

		// Error
		return 0;
	}

	// Error handling
	{

		// Argument errors
		{
			no_circular_buffer:
				#ifndef NDEBUG
					log_error("[circular buffer] Null pointer provided for parameter \"p_circular_buffer\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;

			no_data:
				#ifndef NDEBUG
					log_error("[circular buffer] Null pointer provided for parameter \"pp_data\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int circular_buffer_pop ( circular_buffer *const p_circular_buffer, void **pp_data )
{

	// Argument check
	if ( p_circular_buffer == (void *) 0 ) goto no_circular_buffer;
	if ( pp_data           == (void *) 0 ) goto no_data;

	// Lock
	mutex_lock(&p_circular_buffer->_lock);
	
	// Initialized data
	void *p_data = p_circular_buffer->_p_data[p_circular_buffer->read];

	// Update the read index
	p_circular_buffer->read = ( p_circular_buffer->read + 1 ) % p_circular_buffer->length;

	// Clear the full flag
	p_circular_buffer->full = false;

	// Return a pointer to the caller
	*pp_data = p_data;

	// Unlock
	mutex_unlock(&p_circular_buffer->_lock);

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_circular_buffer:
				#ifndef NDEBUG
					log_error("[circular buffer] Null pointer provided for parameter \"p_circular_buffer\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;

			no_data:
				#ifndef NDEBUG
					log_error("[circular buffer] Null pointer provided for parameter \"pp_data\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int circular_buffer_destroy ( circular_buffer **const pp_circular_buffer )
{

	// Argument check
	if ( pp_circular_buffer == (void *) 0 ) goto no_circular_buffer;

	// Initialized data
	circular_buffer *p_circular_buffer = *pp_circular_buffer;
	
	// Lock
	mutex_lock(&p_circular_buffer->_lock);

	// No more circular buffer for end user
	*pp_circular_buffer = 0;

	// Unlock
	mutex_unlock(&p_circular_buffer->_lock);

	// Empty the circular buffer
	//

	// Free the memory
	p_circular_buffer = CIRCULAR_BUFFER_REALLOC(p_circular_buffer, 0);
		
	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_circular_buffer:
				#ifndef NDEBUG
					log_error("[circular buffer] Null pointer provided for \"pp_circular_buffer\" in call to function \"%s\"\n",__FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}
