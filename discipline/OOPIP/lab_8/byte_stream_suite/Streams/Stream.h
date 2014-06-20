///////////////////////////////////////////////////////////
//  Stream.h
//  Implementation of the Class Stream
//  Created on:      24-Apr-2014 11:20:30 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_6216E5B0_434D_44a5_89B8_6E6FCF23C4BA__INCLUDED_)
#define EA_6216E5B0_434D_44a5_89B8_6E6FCF23C4BA__INCLUDED_

class Stream
{

public:
	Stream();
	virtual ~Stream();

	virtual int read(Vector <byte_t>& dest, int num_bytes);
	virtual int write(Vector <byte_t>& source, int num_bytes);

};
#endif // !defined(EA_6216E5B0_434D_44a5_89B8_6E6FCF23C4BA__INCLUDED_)
