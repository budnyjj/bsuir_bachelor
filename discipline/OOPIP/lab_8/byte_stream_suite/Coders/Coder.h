///////////////////////////////////////////////////////////
//  Coder.h
//  Implementation of the Class Coder
//  Created on:      24-Apr-2014 11:20:29 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_D0BF04B0_E40A_48dd_B45C_9DE999009748__INCLUDED_)
#define EA_D0BF04B0_E40A_48dd_B45C_9DE999009748__INCLUDED_

/**
 * Abcstract class which provides coding and deconding interface.
 */
class Coder
{

public:
	Coder();
	virtual ~Coder();

	virtual void Code(Vector<byte_t>& src);
	virtual void Decode(Vector <byte_t>& byte);

};
#endif // !defined(EA_D0BF04B0_E40A_48dd_B45C_9DE999009748__INCLUDED_)
