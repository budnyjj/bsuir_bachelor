///////////////////////////////////////////////////////////
//  File_stream.cpp
//  Implementation of the Class File_stream
//  Created on:      24-Apr-2014 11:20:29 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#include "File_stream.h"


File_stream::File_stream(){

}



File_stream::~File_stream(){

}





void File_stream::File_stream(FILE* file){

	this->_file = file;
}


/**
 * Read num_bytes from file.
 */
int File_stream::read(Vector <byte_t>& dest, int num_bytes){

	//Read num_bytes from file to destination.


	return 0;
}


/**
 * Write bytes to stream. Return 0 if succeed, error_code othewise.
 */
int File_stream::write(Vector <byte_t>& source, int num_bytes){

	//Write num_bytes to file.


	return 0;
}



File_stream::File_stream(){

}



File_stream::~File_stream(){

}





/**
 * Read num_char from stream.
 */
String File_stream::read(int num_char){

	return  NULL;
}


/**
 * Write string to stream. Return 0 if succeed, error_code othewise.
 */
int File_stream::write(String string){

	return 0;
}