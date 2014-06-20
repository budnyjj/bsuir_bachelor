///////////////////////////////////////////////////////////
//  Buffered_stream.h
//  Implementation of the Class Buffered_stream
//  Created on:      24-Apr-2014 11:20:28 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_B91544AC_F625_4796_873C_6610D36EB859__INCLUDED_)
#define EA_B91544AC_F625_4796_873C_6610D36EB859__INCLUDED_

#include "Stream_wrapper.h"

/**
 * Stream with buffer.
 */
class Buffered_stream : public Stream_wrapper
{

public:
	Buffered_stream();
	virtual ~Buffered_stream();

	void Buffered_stream(Stream * stream, size_t buffer_size = 1024);
	virtual int read(Vector <byte_t>& dest, int num_bytes);
	virtual int write(Vector <byte_t>& source, int num_bytes);

protected:
	/**
	 * Array of bytes, which contains stream data.
	 */
	Vector <byte_t>& _buffer;

	virtual void handle_full_buffer();
	virtual void handle_empty_buffer();

private:
	const int MAX_BUFFER_SIZE;

};
#endif // !defined(EA_B91544AC_F625_4796_873C_6610D36EB859__INCLUDED_)
