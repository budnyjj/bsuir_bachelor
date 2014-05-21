///////////////////////////////////////////////////////////
//  Network_stream.h
//  Implementation of the Class Network_stream
//  Created on:      24-Apr-2014 11:20:30 PM
//  Original author: budnyjj
///////////////////////////////////////////////////////////

#if !defined(EA_CB529AE4_1E29_480f_A1A9_D573F36081B1__INCLUDED_)
#define EA_CB529AE4_1E29_480f_A1A9_D573F36081B1__INCLUDED_

#include "Stream.h"

/**
 * Send passed values by network.
 */
class Network_stream : public Stream
{

public:
	Network_stream();
	virtual ~Network_stream();

	void Network_stream(SOCKET* socket);
	virtual int read(Vector <byte_t>& dest, int num_bytes);
	virtual int write(Vector <byte_t>& source, int num_bytes);

private:
	SOCKET* _socket;

};
#endif // !defined(EA_CB529AE4_1E29_480f_A1A9_D573F36081B1__INCLUDED_)
