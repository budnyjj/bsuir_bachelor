///////////////////////////////////////////////////////////
//  Compressing_stream.h
//  Implementation of the Class Compressing_stream
//  Created on:      24-Apr-2014 11:20:29 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_42303363_70E7_42fe_8D8E_6440CEAD2552__INCLUDED_)
#define EA_42303363_70E7_42fe_8D8E_6440CEAD2552__INCLUDED_

#include "Stream_wrapper.h"
#include "Compressor.h"

/**
 * Stream decorator, which provides compress functionality.
 */
class Compressing_stream : public Stream_wrapper
{

public:
	Compressing_stream();
	virtual ~Compressing_stream();
	Compressor *m_Compressor;

	void Compressing_stream(Stream * stream, Compressor * compressor);
	virtual int read(Vector <byte_t>& dest, int num_bytes);
	virtual int write(Vector <byte_t>& source, int num_bytes);

private:
	Compressor * _compressor;

};
#endif // !defined(EA_42303363_70E7_42fe_8D8E_6440CEAD2552__INCLUDED_)
