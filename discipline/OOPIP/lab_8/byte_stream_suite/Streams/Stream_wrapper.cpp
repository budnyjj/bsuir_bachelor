///////////////////////////////////////////////////////////
//  Stream_wrapper.cpp
//  Implementation of the Class Stream_wrapper
//  Created on:      24-Apr-2014 11:20:30 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#include "Stream_wrapper.h"


Stream_wrapper::Stream_wrapper(){

}



Stream_wrapper::~Stream_wrapper(){

}





/**
 * Wrap stream with decorator instance.
 */
void Stream_wrapper::Stream_wrapper(Stream * stream){

}


/**
 * Read num_bytes from stream.
 */
int Stream_wrapper::read(Vector <byte_t>& dest, int num_bytes){

	return _stream->read(dest, num_bytes);
}


/**
 * Write bytes to stream. Return 0 if succeed, error_code othewise.
 */
int Stream_wrapper::write(Vector <byte_t>& source, int num_bytes){

	return this->_stream->write(source, num_bytes);
}