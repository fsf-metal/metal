/*
 * AquisTypes.h
 *
 *  Created on: Sep 29, 2014
 *      Author: jc
 */

#ifndef METAL_AQUIS_AQUISTYPES_H
#define METAL_AQUIS_AQUISTYPES_H

#include <stdint.h>

namespace Metal {
namespace Aquis {

typedef uint8_t MsgType;
typedef uint32_t SeqNum;
typedef uint16_t ProtocolVersion;
typedef uint16_t InactivityTimeout;
typedef uint32_t ATPSeqNo;

typedef uint16_t SecurityId;
typedef uint8_t OrderType;
typedef uint8_t TimeInForce;
typedef uint8_t Side;
typedef uint32_t Quantity;
typedef uint64_t Price;
typedef uint8_t OrderCapacity;
typedef uint8_t Account;
typedef uint64_t UserTag;

typedef uint32_t OrderRef;

}
}

#endif //METAL_AQUIS_AQUISTYPES_H
