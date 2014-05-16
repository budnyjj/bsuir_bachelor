///////////////////////////////////////////////////////////
//  Stream_wrapper.h
//  Implementation of the Class Stream_wrapper
//  Created on:      24-Apr-2014 11:20:30 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_7C85D4B0_216F_476e_81AE_036B2089415D__INCLUDED_)
#define EA_7C85D4B0_216F_476e_81AE_036B2089415D__INCLUDED_

#include "Stream.h"

/**
 * Abstract class, which provides decoration functions for stream class.
 */
class Stream_wrapper : public Stream
{

public:
	Stream_wrapper();
	virtual ~Stream_wrapper();
	Stream *m_Stream;

	void Stream_wrapper(Stream * stream);
	virtual int read(Vector <byte_t>& dest, int num_bytes);
	virtual int write(Vector <byte_t>& source, int num_bytes);

protected:
	/**
	 * Pointer to connected Stream object.
	 */
	Stream * _stream;

};
#endif // !defined(EA_7C85D4B0_216F_476e_81AE_036B2089415D__INCLUDED_)
