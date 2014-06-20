///////////////////////////////////////////////////////////
//  ASCII7Coder.h
//  Implementation of the Class ASCII7Coder
//  Created on:      24-Apr-2014 11:20:28 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_8647D58F_4B52_4591_A2B9_1CCBFD8F3F56__INCLUDED_)
#define EA_8647D58F_4B52_4591_A2B9_1CCBFD8F3F56__INCLUDED_

#include "Coder.h"

class ASCII7Coder : public Coder
{

public:
	ASCII7Coder();
	virtual ~ASCII7Coder();

	virtual Vector <byte_t> Code(Vector<byte_t>& src);
	virtual Vector <byte_t> Decode(Vector <byte_t>& byte);

};
#endif // !defined(EA_8647D58F_4B52_4591_A2B9_1CCBFD8F3F56__INCLUDED_)
