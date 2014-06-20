///////////////////////////////////////////////////////////
//  Coding_stream.h
//  Implementation of the Class Coding_stream
//  Created on:      24-Apr-2014 11:20:29 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_D0CB31D8_0225_4269_A916_5A9076261D1E__INCLUDED_)
#define EA_D0CB31D8_0225_4269_A916_5A9076261D1E__INCLUDED_

#include "Coder.h"
#include "Stream_wrapper.h"

/**
 * Stream decorator, which provides de/code functionality.
 */
class Coding_stream : public Stream_wrapper
{

public:
	Coding_stream();
	virtual ~Coding_stream();
	Coder *m_Coder;

	void Coding_stream(Stream* stream, Coder * coder);
	virtual int read(Vector <byte_t>& dest, int num_bytes);
	virtual int write(Vector <byte_t>& source, int num_bytes);

protected:
	Coder * _coder;

};
#endif // !defined(EA_D0CB31D8_0225_4269_A916_5A9076261D1E__INCLUDED_)
