#ifndef __METAL_TRADINGADAPTER_H
#define __METAL_TRADINGADAPTER_H

#include <string>
#include <chrono>
#include <netlink/socket.h>

#include "Adapter.h"
#include "metal.h"
#include "Mapper.h"
#include "Message.h"

namespace Metal {
class TradingAdapter : public Adapter {
	public:
		/**
		 * @param name Whatever should be used to identify this adapter.
		 * Subclasses will perform mapping, encoding then write to the active session
		 */
		TradingAdapter( const std::string& name, const std::string& uuid);

		/**
		 * This method should be invoked before starting the adapter to set remote host properties
		 * @param hostName name of the remote host
		 * @param portNumber remote port number
		 */
		void setRemoteHost(const std::string &hostName, unsigned int portNumber);

		/**
		 * This function should be invoked to initiate physical connection<br>
		 * It will create a new Thread for incomming messages
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
		 * Subclasses will perform mapping, encoding then write to the active session<br>
		 * @param NewOrderSingle Inbound order in unified format @see NewOrderSingle
		 */
		virtual void send( const NewOrderSingle &) = 0;

		/**
		* This pure virtual method should be implemented in each adapter.
		*/
		virtual void sendLogon() = 0;

		/**
		 * This method will invoked upon receiving an execution report<br>
		 * Subclasses will perform mapping, encoding then write to the active session<br>
		 * @param ExecutionReport incomming execution report
		 */
		virtual void recv( const ExecutionReport &er) = 0;

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
};

} // namespace Metal

#endif //__METAL_TRADINGADAPTER_H
