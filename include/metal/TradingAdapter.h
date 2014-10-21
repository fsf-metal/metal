#ifndef __METAL_TRADINGADAPTER_H
#define __METAL_TRADINGADAPTER_H

#include <string>
#include <chrono>
#include <thread>

#include <netlink/socket.h>

#include "Adapter.h"
#include "metal.h"
#include "Mapper.h"
#include "Message.h"
#include "KeepAlive.h"

namespace Metal {

/**
 * This class is responsible for maintaining the session
 */
class TradingAdapter : public Adapter, public KeepAlive {
	public:
		/**
		 * @param name Whatever should be used to identify this adapter.
		 * @param uuid a unique identifier. Check out http://www.famkruithof.net/uuid/uuidgen to create your own
		 * @param heartBeatInterval number of seconds between heartbeats. Defaults to 30 seconds.
		 * @param retryInterval number of seconds between retries when connection is lost. Defaults to 5 seconds.
		 * Subclasses will perform mapping, encoding then write to the active session
		 */
		TradingAdapter( const std::string& name, const std::string& uuid, int heartBeatInterval = 30, int retryInterval = 5);

		/**
		 * This method should be invoked before starting the adapter to set remote host properties
		 * @param hostName name of the remote host
		 * @param portNumber remote port number
		 */
		void setRemoteHost(const std::string &hostName, unsigned int portNumber);

		/**
		 * This function should be invoked to initiate physical connection<br>
		 * It will create a new Thread for incoming messages
		 */
		void start();

		/**
		* This method will close logical and physical connection<br>
		* All created threads will be terminated
		*/
		void stop();

		/**
		 * This methods sends an message in native format.
		 */
		void send( Message& msg);

		/**
		 * This method will be called by users to send new orders<br>
		 * It will map and encode the message using @see encode(NewOrderSingle) then send it using send(Message&)<br>
		 * You should override send() to leverage your own sending mechanism
		 * @param NewOrderSingle Inbound order in unified format @see NewOrderSingle
		 */
		virtual void send( const NewOrderSingle &);
		/**
		 * Performs full conversion (mapping + encoding) on NewOrderSingle
		 * @param nos order message to be encoding
		 * @param msg resulting binary message
		 */
		virtual void encode( const NewOrderSingle &nos, Message &msg);

		/**
		 * Should be implemented by subclasses to send heart beats
		 */
		virtual void encodeHeartBeat(Message &msg);

		/**
		* This method should be overriden by subclasses<br>
		* We do not make it pure virtual to reduce constraints
		* @param msg Where encoded Logon Message will be stored
		*/
		virtual void encodeLogon( Message &msg);

		/**
		 * This method will invoked upon receiving an execution report<br>
		 * Subclasses will perform mapping, encoding then write to the active session<br>
		 * @param ExecutionReport incomming execution report
		 */
		virtual void onMessage( const ExecutionReport &er) = 0;

		/**
		 * invokwed with the time is right to retry a connection 
		 */
		void retryConnection();

		/**
		 * This method is invoked once the socket is connected<br>
		 * The default behavior is to send a Logon message. Which you may want to override.
		 */
		virtual void onPhysicalConnection();

		/**
		 * The purpose is to measure Mapping and Encoding speed for NewOrderSingle<br>
		 * Subclasses should make sure to execute both as opposed to just mapping
		 * @param list A list of NewOrderSingle better if randomly generated
		 * @param mappingDuration Time used to map messages
		 * @param encodingDuration Time used to encode messages
		 */
		virtual void benchmark( const std::vector<NewOrderSingle> &list,
				std::chrono::milliseconds &mappingDuration,
				std::chrono::milliseconds &encodingDuration) = 0;

		/**
		* The purpose is to measure Mapping and Encoding speed for OrderCancelRequest<br>
		* Subclasses should make sure to execute both as opposed to just mapping
		 * @param list A list of NewOrderSingle better if randomly generated
		 * @param mappingDuration Time used to map messages
		 * @param encodingDuration Time used to encode messages
		*/
		virtual void benchmark( const std::vector<OrderCancelRequest> &list,
				std::chrono::milliseconds &mappingDuration,
				std::chrono::milliseconds &encodingDuration) = 0;

	protected:
		~TradingAdapter();

		std::string remoteHost;
		unsigned int remotePort;
		NL::Socket *socket;

		/**
		 * This will terminate the physical connection if need be
		 * @param delay in milliseconds if we should wait before closing
		 */
		void closeSocket( int delay = 0);

		/**
		 * Send a heartbeat to the remote party
		 */
		void heartBeat();

};

} // namespace Metal

#endif //__METAL_TRADINGADAPTER_H
