///////////////////////////////////////////////////////////
//  Compressing_stream.cpp
//  Implementation of the Class Compressing_stream
//  Created on:      24-Apr-2014 11:20:29 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#include "Compressing_stream.h"


Compressing_stream::Compressing_stream(){

}



Compressing_stream::~Compressing_stream(){

}





void Compressing_stream::Compressing_stream(Stream * stream, Compressor * compressor){

	this->_stream = stream;
	this->_compressor = compressor;
}


/**
 * Read num_bytes from stream.
 */
int Compressing_stream::read(Vector <byte_t>& dest, int num_bytes){

	int err_no = 0;
	if (!(err_no = _stream->read(dest, num_bytes)))
	{
		this->decompress(dest);
	}
	return err_no;
}


/**
 * Write bytes to stream. Return 0 if succeed, error_code othewise.
 */
int Compressing_stream::write(Vector <byte_t>& source, int num_bytes){

	this->_compressor->compress(source);
	return this->_stream->write(source, num_bytes);
}