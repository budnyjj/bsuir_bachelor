///////////////////////////////////////////////////////////
//  Memory_stream.cpp
//  Implementation of the Class Memory_stream
//  Created on:      24-Apr-2014 11:20:30 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#include "Memory_stream.h"


Memory_stream::Memory_stream(){

}



Memory_stream::~Memory_stream(){

}





void Memory_stream::Memory_stream(byte_t * memory, size_t size){

	this->_max_size = max_size;
	this->_memory = memory;
	
}


/**
 * Read num_bytes from stream.
 */
int Memory_stream::read(Vector <byte_t>& dest, int num_bytes){

	return 0;
}


/**
 * Write bytes to stream. Return 0 if succeed, error_code othewise.
 */
int Memory_stream::write(Vector <byte_t>& source, int num_bytes){

	return 0;
}