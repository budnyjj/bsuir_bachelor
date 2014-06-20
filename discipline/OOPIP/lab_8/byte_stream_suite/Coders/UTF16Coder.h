///////////////////////////////////////////////////////////
//  UTF16Coder.h
//  Implementation of the Class UTF16Coder
//  Created on:      24-Apr-2014 11:20:30 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_E47AF6EC_A742_47a6_BA8F_65882DBCE82D__INCLUDED_)
#define EA_E47AF6EC_A742_47a6_BA8F_65882DBCE82D__INCLUDED_

#include "UTFCoder.h"

class UTF16Coder : public UTFCoder
{

public:
	UTF16Coder();
	virtual ~UTF16Coder();

	virtual void Code(Vector<byte_t>& bytes);
	virtual void Decode(Vector <byte_t>& bytes);

};
#endif // !defined(EA_E47AF6EC_A742_47a6_BA8F_65882DBCE82D__INCLUDED_)
