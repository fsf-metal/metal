#include <iostream>
#include "InboundFIXSession.h"
#include "QuickFIXAdapter/QuickFIXMessageMapper.h"

#include "quickfix/FileStore.h"
#include "quickfix/FileLog.h"
#include "quickfix/SocketAcceptor.h"
#include "quickfix/Session.h"
#include "quickfix/SessionID.h"
#include "quickfix/SessionSettings.h"
#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"

#include "singlegeneralorderhandling.pb.h"

using namespace FIX;

// This is our custom QuickFIX implementation
class MyApplication:public Application,public MessageCracker {
	public:
		MyApplication() {
			this->tradingAdapter = NULL;
		};
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
		void fromApp( const Message& message, const SessionID& sessionID) 
			throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType ) {
				crack( message, sessionID);
			};

		void onMessage( const FIX44::NewOrderSingle& message, const SessionID& ) {
			// Transform and send the message
			if( this->tradingAdapter != NULL) {
				SingleGeneralOrderHandling::NewOrderSingle nos;
				QuickFIXMessageMapper::map( message, nos);
				this->tradingAdapter->send( nos);
			}
		};

		// memorize TradingAdapter to forward incomming orders
		void setTradingAdapter( TradingAdapter *pta) {
			this->tradingAdapter = pta;
		}

	private:
		TradingAdapter *tradingAdapter;
};

InboundFIXSession::InboundFIXSession() {
	this->acceptor = NULL;
	this->tradingAdapter = NULL;
}

void InboundFIXSession::setTradingAdapter( TradingAdapter *pta) {
	this->tradingAdapter = pta;
}

void InboundFIXSession::start() {
	std::cout << "Starting inbound FIX session" << std::endl;

	// Perform all QuickFIX initialisation
	SessionSettings *settings = new SessionSettings("silverFIXClient.cfg");

	MyApplication *application = new MyApplication();
	//application->adapter = this->adapter;
	application->setTradingAdapter( this->tradingAdapter);

	FileStoreFactory *storeFactory = new FileStoreFactory(*settings);
	FileLogFactory *logFactory = new FileLogFactory(*settings);
	this->acceptor = new SocketAcceptor( *application, *storeFactory, *settings, *logFactory /*optional*/);
	// std::cout << "Acceptor Initiated" << std::endl;
	this->acceptor->start();
	std::cout << "QuickFIX Acceptor started" << std::endl;
}

void InboundFIXSession::stop() {
	// std::cout << "Stopping inbound FIX session" << std::endl;
	// Stop QuickFIX acceptor 
	if( this->acceptor != NULL) {
		this->acceptor->stop();
		// std::cout << "QuickFIX Acceptor stopped" << std::endl;
		this->acceptor = NULL;
	}
}

