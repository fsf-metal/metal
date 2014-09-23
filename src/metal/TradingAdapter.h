#ifndef __METAL_TRADINGADAPTER_H
#define __METAL_TRADINGADAPTER_H

#include <string>
#include <chrono>

#include "Adapter.h"
#include "metal.h"
#include "Mapper.h"

namespace Metal {
class TradingAdapter : public Adapter {
	public:
		/**
		 * @param name Whatever should be used to identify this adapter.
		 * Subclasses will perform mapping, encoding then write to the active session
		 */
		TradingAdapter( const std::string& name) : Adapter( name){};
		/**
		 * This method will be called by users to send new orders<br>
		 * Subclasses will perform mapping, encoding then write to the active session<br>
		 * @param NewOrderSingle Inbound order in unified format @see NewOrderSingle
		 */
		virtual void send( const NewOrderSingle &) = 0;

		/**
		 * This method will invoked upon receiving an execution report<br>
		 * Subclasses will perform mapping, encoding then write to the active session<br>
		 * @param ExecutionReport incomming execution report
		 */
		virtual void recv( const ExecutionReport &er) = 0;

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
};

} // namespace Metal

#endif //__METAL_TRADINGADAPTER_H
