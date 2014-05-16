///////////////////////////////////////////////////////////
//  HuffmanCompressor.h
//  Implementation of the Class HuffmanCompressor
//  Created on:      24-Apr-2014 11:20:30 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_DACB6F88_C9D0_4160_B0C3_A4C43544BBAD__INCLUDED_)
#define EA_DACB6F88_C9D0_4160_B0C3_A4C43544BBAD__INCLUDED_

#include "Compressor.h"

class HuffmanCompressor : public Compressor
{

public:
	HuffmanCompressor();
	virtual ~HuffmanCompressor();

	void Compress(Vector<byte_t>& bytes);
	void Decompress(Vector<byte_t>& bytes);

};
#endif // !defined(EA_DACB6F88_C9D0_4160_B0C3_A4C43544BBAD__INCLUDED_)
