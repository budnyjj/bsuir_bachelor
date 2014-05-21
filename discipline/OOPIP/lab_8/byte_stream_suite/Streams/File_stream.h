///////////////////////////////////////////////////////////
//  File_stream.h
//  Implementation of the Class File_stream
//  Created on:      24-Apr-2014 11:20:29 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_08517A3B_75E2_42d6_BE29_8867FC455E13__INCLUDED_)
#define EA_08517A3B_75E2_42d6_BE29_8867FC455E13__INCLUDED_

#include "Stream.h"
#include "Buffered_stream.h"

/**
 * Store passed values in file
 */
class File_stream : public Stream
{

public:
	File_stream();
	virtual ~File_stream();

	void File_stream(FILE* file);
	virtual int read(Vector <byte_t>& dest, int num_bytes);
	virtual int write(Vector <byte_t>& source, int num_bytes);

private:
	FILE* _file;

};

/**
 * Stream, which store its contents in file.
 */
class File_stream : public Buffered_stream
{

public:
	File_stream();
	virtual ~File_stream();

	virtual String read(int num_char);
	virtual int write(String string);

};
#endif // !defined(EA_08517A3B_75E2_42d6_BE29_8867FC455E13__INCLUDED_)
