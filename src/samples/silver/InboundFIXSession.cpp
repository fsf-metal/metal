#include <iostream>
#include "InboundFIXSession.h"

#include "quickfix/FileStore.h"
#include "quickfix/FileLog.h"
#include "quickfix/SocketAcceptor.h"
#include "quickfix/Session.h"
#include "quickfix/SessionID.h"
#include "quickfix/SessionSettings.h"
#include "quickfix/Application.h"

using namespace FIX;

class MyApplication:public Application {
	public:
		~MyApplication() {};
		void onCreate( const SessionID& ) {};
		void onLogon( const SessionID& ){
			std::cout << "Logon received" << std::endl;
		};
		void onLogout( const SessionID& ) {};
		void toAdmin( Message&, const SessionID& ) {
			std::cout << "Admin sent" << std::endl;
		};
		void toApp( Message&, const SessionID& )
			throw( DoNotSend ) {
			std::cout << "App sent" << std::endl;
		};
		void fromAdmin( const Message&, const SessionID& )
			throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon ) {
			std::cout << "Admin received" << std::endl;
		};
		void fromApp( const Message&, const SessionID& ) 
			throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType ) {
			std::cout << "App received" << std::endl;
		};
};

void InboundFIXSession::start() {
	std::cout << "Starting inbound FIX session" << std::endl;

	SessionSettings *settings = new SessionSettings("silverFIXConfig.txt");

	MyApplication *application = new MyApplication();
	FileStoreFactory *storeFactory = new FileStoreFactory(*settings);
	FileLogFactory *logFactory = new FileLogFactory(*settings);
	this->acceptor = new SocketAcceptor( *application, *storeFactory, *settings, *logFactory /*optional*/);
	// std::cout << "Acceptor Initiated" << std::endl;
	this->acceptor->start();
	std::cout << "QuickFIX Acceptor started" << std::endl;
}

void InboundFIXSession::stop() {
	// std::cout << "Stopping inbound FIX session" << std::endl;
	if( this->acceptor != NULL) {
		this->acceptor->stop();
		std::cout << "QuickFIX Acceptor stopped" << std::endl;
	}
}
