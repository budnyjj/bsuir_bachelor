///////////////////////////////////////////////////////////
//  Memory_stream.h
//  Implementation of the Class Memory_stream
//  Created on:      24-Apr-2014 11:20:30 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_7762515E_17B5_4b20_B272_C064FC7D665B__INCLUDED_)
#define EA_7762515E_17B5_4b20_B272_C064FC7D665B__INCLUDED_

#include "Stream.h"

/**
 * Store passed values in preallocated memory.
 */
class Memory_stream : public Stream
{

public:
	Memory_stream();
	virtual ~Memory_stream();

	void Memory_stream(byte_t * memory, size_t size);
	virtual int read(Vector <byte_t>& dest, int num_bytes);
	virtual int write(Vector <byte_t>& source, int num_bytes);

private:
	byte_t * _memory;
	int _max_size;

};
#endif // !defined(EA_7762515E_17B5_4b20_B272_C064FC7D665B__INCLUDED_)
