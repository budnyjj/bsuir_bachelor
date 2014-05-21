///////////////////////////////////////////////////////////
//  UTFCoder.h
//  Implementation of the Class UTFCoder
//  Created on:      24-Apr-2014 11:20:31 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_BE084A01_F936_4ee8_8580_B33C1A70CE42__INCLUDED_)
#define EA_BE084A01_F936_4ee8_8580_B33C1A70CE42__INCLUDED_

#include "Coder.h"

class UTFCoder : public Coder
{

public:
	UTFCoder();
	virtual ~UTFCoder();

	virtual void Code(Vector<byte_t>& bytes);
	virtual void Decode(Vector <byte_t>& bytes);

};
#endif // !defined(EA_BE084A01_F936_4ee8_8580_B33C1A70CE42__INCLUDED_)
