///////////////////////////////////////////////////////////
//  Network_stream.cpp
//  Implementation of the Class Network_stream
//  Created on:      24-Apr-2014 11:20:30 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#include "Network_stream.h"


Network_stream::Network_stream(){

}



Network_stream::~Network_stream(){

}





void Network_stream::Network_stream(SOCKET* socket){

	this->_socket = socket;
}


/**
 * Read num_bytes from stream.
 */
int Network_stream::read(Vector <byte_t>& dest, int num_bytes){

	return 0;
}


/**
 * Write bytes to stream. Return 0 if succeed, error_code othewise.
 */
int Network_stream::write(Vector <byte_t>& source, int num_bytes){

	return 0;
}