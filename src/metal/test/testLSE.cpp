#include <gtest/gtest.h>

#include <adapters/LSETradingAdapter/MilleniumCodec.h>
#include <metal/Message.h>

using namespace std;
using namespace Metal;

TEST( LSE, heartBeat) {
	Metal::LSE::MilleniumCodec mc;

	Metal::Message msg;
	mc.encodeHeartBeat(msg);

	ASSERT_EQ( 4, msg.getLength());
	EXPECT_EQ( 2, msg.get(0));
	EXPECT_EQ( 4, msg.get(1));
	EXPECT_EQ( 0, msg.get(2));
	EXPECT_EQ('0', msg.get(3));
}

