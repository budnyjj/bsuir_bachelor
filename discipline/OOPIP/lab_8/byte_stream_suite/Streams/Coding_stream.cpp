///////////////////////////////////////////////////////////
//  Coding_stream.cpp
//  Implementation of the Class Coding_stream
//  Created on:      24-Apr-2014 11:20:29 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#include "Coding_stream.h"


Coding_stream::Coding_stream(){

}



Coding_stream::~Coding_stream(){

}





void Coding_stream::Coding_stream(Stream* stream, Coder * coder){

	this->_stream = stream;
	this->_coder = coder;
}


/**
 * Read num_bytes from stream.
 */
int Coding_stream::read(Vector <byte_t>& dest, int num_bytes){

	int err_code = 0;
	if (!(err_code = _stream->read(dest, num_bytes)))
		_coder->decode(dest);
	return err_code;
}


/**
 * Write bytes to stream. Return 0 if succeed, error_code othewise.
 */
int Coding_stream::write(Vector <byte_t>& source, int num_bytes){

	this->_coder->code(source);
	return this->_stream->write(source, num_bytes);
}