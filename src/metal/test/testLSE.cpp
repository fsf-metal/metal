#include <gtest/gtest.h>

#include <adapters/LSETradingAdapter/MilleniumCodec.h>
#include <metal/Message.h>

using namespace std;
using namespace Metal;
using namespace Metal::LSE;

void checkMessageStructure(int length, char type, Metal::Message &msg) {
	ASSERT_EQ(length, msg.getLength()) << "Message length is invalid";
	EXPECT_EQ(2, msg.get(0)) << "Message should start with 2";
	EXPECT_EQ(length & 0xFF, msg.get(1)) << "First byte of message size is invalid";
	EXPECT_EQ((length & 0xFF00) >> 8, msg.get(2)) << "Second byte of message size is invalid";
	EXPECT_EQ(type, msg.get(3)) << "Message type is invalid";
}

TEST(LSE, heartBeat) {
	MilleniumCodec mc;

	Message msg;
	mc.encodeHeartBeat(msg);

	checkMessageStructure(4, '0', msg);
}

TEST(LSE, logon) {
	MilleniumCodec mc;
	Message msg;
	LSE::Logon logon( "myself", "mypass");

	mc.encode(logon, msg);

	checkMessageStructure( 80, 'A', msg);
}

TEST(LSE, newOrder) {
	MilleniumCodec mc;
	Message msg;

	LSE::NewOrder no;

	mc.encode(no, msg);
	checkMessageStructure( 97, 'D', msg);

}

TEST(LSE, cancelRequest) {
	MilleniumCodec mc;
	Message msg;

	LSE::OrderCancelRequest ocr;
	mc.encode(ocr, msg);
	checkMessageStructure( 73, 'F', msg);

}