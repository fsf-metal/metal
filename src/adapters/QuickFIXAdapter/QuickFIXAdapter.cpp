#include <iostream>

#include "QuickFIXAdapter.h"
#include "QuickFIXMessageMapper.h"

#include "quickfix/FileStore.h"
#include "quickfix/FileLog.h"
#include "quickfix/SocketInitiator.h"
#include "quickfix/Session.h"
#include "quickfix/SessionID.h"
#include "quickfix/SessionSettings.h"
#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"


using namespace FIX;

class MyApplication: public Application,public MessageCracker {
	public:
		MyApplication( QuickFIXAdapter *pqfa) {
			this->adapter = pqfa;
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
				std::cout << "Message received type " << message.getField( 35) << std::endl;
				crack( message, sessionID);
			};

		void onMessage( const FIX42::ExecutionReport& message, const SessionID& ) {
				if( this->adapter != NULL && false) {
					SingleGeneralOrderHandling::ExecutionReport er;
					QuickFIXMessageMapper::map( message, er);
					this->adapter->recv( er);
				}
        };
	private:
		QuickFIXAdapter *adapter;

};

QuickFIXAdapter::QuickFIXAdapter() {
}

QuickFIXAdapter::~QuickFIXAdapter() {
}

/**
 * Tranform incomming NewOrderSingle into QuickFIX message and sendi it
 */
void QuickFIXAdapter::send( SingleGeneralOrderHandling::NewOrderSingle &nos) {
	std::cout << "QuickFIXAdapter: send NewOrderSingle" << std::endl;

	FIX42::NewOrderSingle message;
	QuickFIXMessageMapper::map( nos, message);
	this->session->sendToTarget( message);
}

void QuickFIXAdapter::recv( SingleGeneralOrderHandling::ExecutionReport &er) {
	std::cout << "QuickFIXAdapter: Execution Report received but not processed" << std::endl;
}

void QuickFIXAdapter::start() {
	//std::cout << "QuickFIXAdapter: start()" << std::endl;
	TradingAdapter::start();

	// Perform all QuickFIX initialisation
	std::string settingsFileName = "QuickFIXAdapter.cfg";
	SessionSettings *settings = new SessionSettings( settingsFileName);
	std::cout << "QuickFIXAdapter: settings loaded from " << settingsFileName << std::endl;

	MyApplication *application = new MyApplication( this);

	FileStoreFactory *storeFactory = new FileStoreFactory(*settings);
	FileLogFactory *logFactory = new FileLogFactory(*settings);
	this->initiator = new SocketInitiator( *application, *storeFactory, *settings, *logFactory /*optional*/);

	std::cout << "QuickFIXAdapter: starting initiator" << std::endl;
	this->initiator->start();

	// memorize session
}

void QuickFIXAdapter::stop() {
	if( this->initiator != NULL) {
		std::cout << "QuickFIXAdapter: stopping initiator" << std::endl;
		this->initiator->stop();
		delete this->initiator;
		this->initiator = NULL;
	}
}
