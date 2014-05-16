///////////////////////////////////////////////////////////
//  Compressor.h
//  Implementation of the Class Compressor
//  Created on:      24-Apr-2014 11:20:29 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_FA2F6B61_115D_48ec_A9D6_501C9DB5EE6F__INCLUDED_)
#define EA_FA2F6B61_115D_48ec_A9D6_501C9DB5EE6F__INCLUDED_

/**
 * Abstract class which provide in-place compress and decompress functions
 */
class Compressor
{

public:
	Compressor();
	virtual ~Compressor();

	void Compress(Vector<byte_t>& bytes);
	void Decompress(Vector<byte_t>& bytes);

};
#endif // !defined(EA_FA2F6B61_115D_48ec_A9D6_501C9DB5EE6F__INCLUDED_)
