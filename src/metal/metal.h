#ifndef __METAL_H
#define __METAL_H

// We rely on QuickFIX to represent messages
#include <quickfix/fix50sp2/NewOrderSingle.h>
#include <quickfix/fix50sp2/ExecutionReport.h>
#include <quickfix/fix50sp2/OrderCancelRequest.h>

namespace Metal {
class NewOrderSingle : public FIX50SP2::NewOrderSingle {};
class OrderCancelRequest : public FIX50SP2::OrderCancelRequest {};
typedef FIX50SP2::ExecutionReport ExecutionReport;
}

#endif // __METAL_H

