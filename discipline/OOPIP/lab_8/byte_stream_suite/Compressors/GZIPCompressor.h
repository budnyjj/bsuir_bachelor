///////////////////////////////////////////////////////////
//  GZIPCompressor.h
//  Implementation of the Class GZIPCompressor
//  Created on:      24-Apr-2014 11:20:30 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_CF87543E_57AD_4d52_BB47_F0C8E579AD97__INCLUDED_)
#define EA_CF87543E_57AD_4d52_BB47_F0C8E579AD97__INCLUDED_

#include "Compressor.h"

class GZIPCompressor : public Compressor
{

public:
	GZIPCompressor();
	virtual ~GZIPCompressor();

	void Compress(Vector<byte_t>& bytes);
	void Decompress(Vector<byte_t>& bytes);

};
#endif // !defined(EA_CF87543E_57AD_4d52_BB47_F0C8E579AD97__INCLUDED_)
