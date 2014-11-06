#ifndef __LSEMESSAGEMAPPER_H
#define __LSEMESSAGEMAPPER_H

#include <metal/metal.h>
#include <metal/Mapper.h>
#include "NewOrder.h"
#include "OrderCancelRequest.h"
#include "ExecutionReport.h"

namespace Metal {
namespace LSE {

class MilleniumMapper : public Mapper {
	public:
		//-------------
        // LSE to MeTAL
		//-------------
		static void map(const NewOrder&, NewOrderSingle&);
		/** Execution report */
		static void map(const Metal::LSE::ExecutionReport & nativeER, Metal::ExecutionReport &metalER);

        /**
         * MeTAL to LSE for NewOrderSingle
         */
		static void map( const NewOrderSingle&, NewOrder&);
        /**
         * MeTAL to LSE for OrderCancelRequest
         */
		static void map( const Metal::OrderCancelRequest&, Metal::LSE::OrderCancelRequest&);

		/**
		 * Metal to LSE for Side
		 */
		static void map( const FIX::Side &, Metal::LSE::Side &);

		/**
		 * Translate Native Order Status to FIX
		 */
		static FIX::OrdStatus map( OrderStatus nativeStatus);
			
		/**
		 * Translate Native Side to FIX
		 */
		static FIX::Side map( Side nativeStatus);

		// only used by benchmarker
		void benchmark( std::vector<NewOrderSingle> &);

		// Encoding functions
		// inline static void encodeInt32( const int value, char *message, int position);

};

} // namespace LSE
} // namespace Metal


#endif // __LSEMESSAGEMAPPER_H
