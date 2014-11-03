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
		void toAdmin( FIX::Message&, const SessionID& ) {
		};
		void toApp( FIX::Message&, const SessionID& )
			throw( DoNotSend ) {
			};
		void fromAdmin( const FIX::Message&, const SessionID& )
			throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon ) {
			};

		void fromApp( const FIX::Message& message, const SessionID& sessionID)
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
					this->adapter->onMessage( er);
				}
        };

		void onMessage( const FIX44::ExecutionReport& message, const SessionID& ) {
				if( this->adapter != NULL) {
//					std::cout << "QuickFIXAdapter: FIX44 ExecutionReport Received" << std::endl;
					Metal::ExecutionReport er;
					Metal::QuickFIXMessageMapper::map( message, er);

					this->adapter->onMessage( er);
				}
        };

	private:
		QuickFIXAdapter *adapter;

};

/**
 * Default Constructor
 */
QuickFIXAdapter::QuickFIXAdapter() :TradingAdapter("QuickFIX", "e32cd5d0-4564-11e4-916c-0800200c9a66") {
	this->initiator = NULL;
	this->session = NULL;
}

/**
 * This (dumb) loop maps and encodes all incoming NewOrderSingle.<br>
 * In the case of QuickFIX, encoding simply means calling toString()
 */
void QuickFIXAdapter::benchmark( const std::vector<NewOrderSingle> &allOrders,
		std::chrono::milliseconds &mappingDuration,
		std::chrono::milliseconds &encodingDuration) {
	std::string messageString;
	std::vector<FIX44::NewOrderSingle*> mappedNewOrders;

	int size = allOrders.size();
	// Save room and allocate resulting objects
	mappedNewOrders.reserve( size);
	for( int index = 0; index < size; ++index) {
        mappedNewOrders.push_back( new FIX44::NewOrderSingle());
    }

	auto t0 = std::chrono::system_clock::now();
	for( int index = 0; index < size; ++index) {
		QuickFIXMessageMapper::map( allOrders.at( index), *mappedNewOrders.at( index));
	}

	auto t1 = std::chrono::system_clock::now();
	for( int index = 0; index < size; ++index) {
		mappedNewOrders.at( index)->toString( messageString);
	}

	auto t2 = std::chrono::system_clock::now();

	// free allocated memory
	while (!mappedNewOrders.empty()) {
		delete mappedNewOrders.back();
		mappedNewOrders.pop_back();
	}

	mappingDuration = std::chrono::duration_cast<std::chrono::milliseconds>( t1 - t0);
	encodingDuration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1);
}

void QuickFIXAdapter::benchmark( const std::vector<OrderCancelRequest> &allCancels,
		std::chrono::milliseconds &mappingDuration,
		std::chrono::milliseconds &encodingDuration) {
	std::string messageString;
	std::vector<FIX::Message *> mappedCancels;

	int size = allCancels.size();
	mappedCancels.reserve( size);

	for( int index = 0; index < size; ++index) {
        mappedCancels.push_back( new (FIX::Message));
    }
	auto t0 = std::chrono::system_clock::now();
	for( int index = 0; index < size; ++index) {
		QuickFIXMessageMapper::map( allCancels.at( index), *mappedCancels.at( index));
	}
	auto t1 = std::chrono::system_clock::now();
	for( int index = 0; index < size; ++index) {
		mappedCancels.at( index)->toString( messageString);
	}
	auto t2 = std::chrono::system_clock::now();

	// free allocated memory
	while (!mappedCancels.empty()) {
		delete mappedCancels.back();
		mappedCancels.pop_back();
	}

	mappingDuration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
	encodingDuration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1);
}

/**
 * Send normalized New Order
 */
void QuickFIXAdapter::sendNewOrder( const NewOrderSingle &nos) {
//	std::cout << "QuickFIXAdapter: send NewOrderSingle" << std::endl;

	// TODO : Read protocol version from session properties
	// For the moment, we assume the output is FIX44
	FIX44::NewOrderSingle nosFIX44;
	QuickFIXMessageMapper::map( nos, (FIX::Message &)nosFIX44);

	this->session->send( nosFIX44);
}

void QuickFIXAdapter::onMessage( const ExecutionReport &er) {
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

