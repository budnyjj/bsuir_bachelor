///////////////////////////////////////////////////////////
//  Buffered_stream.cpp
//  Implementation of the Class Buffered_stream
//  Created on:      24-Apr-2014 11:20:29 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#include "Buffered_stream.h"


Buffered_stream::Buffered_stream(){

}



Buffered_stream::~Buffered_stream(){

}





void Buffered_stream::Buffered_stream(Stream * stream, size_t buffer_size){

}


/**
 * Read num_bytes from stream.
 */
int Buffered_stream::read(Vector <byte_t>& dest, int num_bytes){

	if (num_bytes <= _buffer.size())
	{
		// return num_bytes from _buffer
	}
	else 
	{
		// repeat:
		// fill destination vector with values
		// from _buffer, clear it,
		// call handle_empty_buffer()
	}
}


/**
 * Write bytes to stream. Return 0 if succeed, error_code othewise.
 */
int Buffered_stream::write(Vector <byte_t>& source, int num_bytes){

	if (_buffer.size + num_bytes <= MAX_BUFFER_SIZE) 
	{
		// extend _buffer with values from source;
	}
	else
	{	
		// repeat:
		// extend _buffer with values from source up 
		// to MAX_BUFFER_SIZE, call handle_full_buffer();
	}
}


/**
 * Handles situation, when buffer is full. 
 */
void Buffered_stream::handle_full_buffer(){

}


/**
 * Handles situation when _buffer is empty.
 */
void Buffered_stream::handle_empty_buffer(){

}