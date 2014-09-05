#ifndef __INBOUNDFIXSESSION_H
#define __INBOUNDFIXSESSION_H

#include "quickfix/SocketAcceptor.h"

class InboundFIXSession {
	public:
		InboundFIXSession(){};
		void start();
		void stop();

	private:
		FIX::SocketAcceptor *acceptor;
};

#endif // __INBOUNDFIXSESSION_H
