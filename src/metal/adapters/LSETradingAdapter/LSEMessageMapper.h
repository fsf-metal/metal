#ifndef __LSEMESSAGEMAPPER_H
#define __LSEMESSAGEMAPPER_H

#include <metal/metal.h>
#include <metal/MessageMapper.h>
#include "NewOrder.h"

namespace Metal {
namespace LSE {

class LSEMessageMapper : public MessageMapper {
	public:
        // LSE to MeTAL
		static void map( const NewOrder&, NewOrderSingle&);
        // MeTAL to LSE
		static void map( const NewOrderSingle&, NewOrder&);

        // only used by benchmarker
		void benchmark( std::vector<NewOrderSingle> &);

		// Encoding functions
		// inline static void encodeInt32( const int value, char *message, int position);

};

} // namespace LSE
} // namespace Metal


#endif // __LSEMESSAGEMAPPER_H
