///////////////////////////////////////////////////////////
//  UTF32Coder.h
//  Implementation of the Class UTF32Coder
//  Created on:      24-Apr-2014 11:20:31 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_E9EBCC8D_E709_4525_A38B_153A537051FC__INCLUDED_)
#define EA_E9EBCC8D_E709_4525_A38B_153A537051FC__INCLUDED_

#include "UTFCoder.h"

class UTF32Coder : public UTFCoder
{

public:
	UTF32Coder();
	virtual ~UTF32Coder();

	virtual void Code(Vector<byte_t>& bytes);
	virtual void Decode(Vector <byte_t>& bytes);

};
#endif // !defined(EA_E9EBCC8D_E709_4525_A38B_153A537051FC__INCLUDED_)
