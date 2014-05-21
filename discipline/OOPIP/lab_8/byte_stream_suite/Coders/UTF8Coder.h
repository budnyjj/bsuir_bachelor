///////////////////////////////////////////////////////////
//  UTF8Coder.h
//  Implementation of the Class UTF8Coder
//  Created on:      24-Apr-2014 11:20:31 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_02EE62B2_3092_48dc_80BA_DF48833810E8__INCLUDED_)
#define EA_02EE62B2_3092_48dc_80BA_DF48833810E8__INCLUDED_

#include "UTFCoder.h"

class UTF8Coder : public UTFCoder
{

public:
	UTF8Coder();
	virtual ~UTF8Coder();

	virtual void Code(Vector<byte_t>& bytes);
	virtual void Decode(Vector <byte_t>& bytes);

};
#endif // !defined(EA_02EE62B2_3092_48dc_80BA_DF48833810E8__INCLUDED_)
