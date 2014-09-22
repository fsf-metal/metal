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
#include "quickfix/fix50sp2/NewOrderSingle.h"


using namespace FIX;

namespace Metal {
namespace QuickFIX {


class MyApplication: public Application,public MessageCracker {
	public:
		MyApplication( QuickFIXAdapter *pqfa) {
			this->adapter = pqfa;
		};
		~MyApplication() {};
		void onCreate( const SessionID& ) {};
		void onLogon( const SessionID& ){};
		void onLogout( const SessionID& ) {};
		void toAdmin( Message&, const SessionID& ) {
		};
		void toApp( Message&, const SessionID& )
			throw( DoNotSend ) {
			};
		void fromAdmin( const Message&, const SessionID& )
			throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon ) {
			};

		void fromApp( const Message& message, const SessionID& sessionID)
			throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType ) {
				// Header header = message.getHeader();
//				std::cout << "Generic Message received" << std::endl;
				crack( message, sessionID);
			};

		void onMessage( const FIX42::ExecutionReport& message, const SessionID& ) {
				if( this->adapter != NULL) {
//					std::cout << "QuickFIXAdapter: FIX42 ExecutionReport Received" << std::endl;
					Metal::ExecutionReport er;
//					QuickFIXMessageMapper::map( message, er);
					this->adapter->recv( er);
				}
        };

		void onMessage( const FIX44::ExecutionReport& message, const SessionID& ) {
				if( this->adapter != NULL) {
//					std::cout << "QuickFIXAdapter: FIX44 ExecutionReport Received" << std::endl;
					Metal::ExecutionReport er;
					Metal::QuickFIXMessageMapper::map( message, er);

					this->adapter->recv( er);
				}
        };
	private:
		QuickFIXAdapter *adapter;

};

/**
 * Default Constructor
 */
QuickFIXAdapter::QuickFIXAdapter():TradingAdapter("QuickFIX") {
	this->initiator = NULL;
	this->session = NULL;
}

/**
 * This (dumb) loop maps and encodes all incoming NewOrderSingle.<br>
 * In the case of QuickFIX, encoding simply means calling toString()
 */
void QuickFIXAdapter::benchmark( const std::vector<NewOrderSingle> &allOrders, bool mappingOnly) {
	FIX44::NewOrderSingle nos44;
	std::string messageString;

	if( mappingOnly) {
		for( std::vector<NewOrderSingle>::const_iterator iter = allOrders.begin(); iter != allOrders.end(); ++iter) {
			QuickFIXMessageMapper::map( *iter, nos44);
		}
	} else {
		for( std::vector<NewOrderSingle>::const_iterator iter = allOrders.begin(); iter != allOrders.end(); ++iter) {
			QuickFIXMessageMapper::map( *iter, nos44);
			nos44.toString( messageString);
		}
	}
}

void QuickFIXAdapter::benchmark( const std::vector<OrderCancelRequest> &allCancels, bool mappingOnly) {
	FIX44::OrderCancelRequest ocr44;
	std::string messageString;

	if( mappingOnly) {
		for (std::vector<OrderCancelRequest>::const_iterator iter = allCancels.begin(); iter != allCancels.end(); ++iter) {
			QuickFIXMessageMapper::map(*iter, ocr44);
		}
	} else {
		for (std::vector<OrderCancelRequest>::const_iterator iter = allCancels.begin(); iter != allCancels.end(); ++iter) {
			QuickFIXMessageMapper::map(*iter, ocr44);
			ocr44.toString(messageString);
		}
	}
}

/**
 * Tranform incomming NewOrderSingle into QuickFIX message and send it
 */
void QuickFIXAdapter::send( const NewOrderSingle &nos) {
//	std::cout << "QuickFIXAdapter: send NewOrderSingle" << std::endl;

	// TODO : Read protocol version from session properties
	// For the moment, we assume the output is FIX44
	FIX44::NewOrderSingle nosFIX44;
	QuickFIXMessageMapper::map( nos, (FIX::Message &)nosFIX44);

	this->session->send( nosFIX44);
}

void QuickFIXAdapter::recv( const ExecutionReport &er) {
	std::cout << "QuickFIXAdapter: Execution Report received but not processed" << std::endl;
}

void QuickFIXAdapter::start() {
	//std::cout << "QuickFIXAdapter: start()" << std::endl;

	// Perform all QuickFIX initialisation
	std::string settingsFileName = "QuickFIXAdapter.cfg";
	SessionSettings *settings = new SessionSettings( settingsFileName);
	std::cout << "QuickFIXAdapter: settings loaded from " << settingsFileName << std::endl;

	MyApplication *application = new MyApplication( this);

	FileStoreFactory *storeFactory = new FileStoreFactory(*settings);
	FileLogFactory *logFactory = new FileLogFactory(*settings);
	this->initiator = new SocketInitiator( *application, *storeFactory, *settings, *logFactory /*optional*/);

	//std::cout << "QuickFIXAdapter: starting initiator" << std::endl;
	this->initiator->start();

	// memorize session
    std::set<SessionID> sessions = settings->getSessions();
	std::cout << "QuickFIXAdapter: adapter started with " << sessions.size() << " session(s)" << std::endl;
    if( sessions.size() > 0) {
        this->session  = FIX::Session::lookupSession( *sessions.begin());
    }
}

void QuickFIXAdapter::stop() {
	if( this->initiator != NULL) {
		std::cout << "QuickFIXAdapter: stopping initiator" << std::endl;
		this->initiator->stop();
		delete this->initiator;
		this->initiator = NULL;
	}
}

} // namespace QuickFIX
} // namespace Metal

