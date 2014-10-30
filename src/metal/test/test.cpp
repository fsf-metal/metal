#include <gtest/gtest.h>

#include <metal/Codec.h>
#include <metal/Message.h>

using namespace std;
using namespace Metal;

TEST( Codec, encodeString) {

	Message msg;
    Codec codec;

	msg.reset();
	std::string str = "This is a 30 characters string";
	codec.encode(str, msg, 0, 10);
	ASSERT_EQ('T', msg.get(0));
	ASSERT_EQ('i', msg.get(5));
	ASSERT_EQ(' ', msg.get(9));
	ASSERT_EQ( 0, msg.get(10));

	// TODO Test integer encoding
}

TEST( Codec, 8bits) {
    Message msg;
    Codec codec;

	int8_t test8 = 0xF1;
    codec.encode( test8, msg, 0);
    ASSERT_EQ( (char)0xF1, msg.get(0));
	codec.encode(test8, msg, 10);
	int8_t decoded;
	codec.decode(msg.getData(), 10, decoded);
	ASSERT_EQ( test8, decoded);
}

TEST( Codec, 16bits) {
    Message msg;
    Codec codec;
	char * data = msg.getData();

	int16_t test16 = 0x0123;
    codec.encodeLE( test16, msg, 10);
    ASSERT_EQ( (char)0x23, msg.get(10));
    ASSERT_EQ( (char)0x01, msg.get(11));
	int16_t decoded;
	codec.decodeLE(data, 10, decoded);
	ASSERT_EQ( test16, decoded);

    codec.encodeBE( test16, msg, 20);
    ASSERT_EQ( (char)0x01, msg.get(20));
    ASSERT_EQ( (char)0x23, msg.get(21));
	codec.decodeBE(data, 20, decoded);
	ASSERT_EQ(test16, decoded);

    uint16_t test16u = 0xFEDC;
    codec.encodeLE( test16u, msg, 0);
    ASSERT_EQ( (char)0xDC, msg.get(0));
    ASSERT_EQ( (char)0xFE, msg.get(1));
	uint16_t decodedu;
	codec.decodeLE(data, 0, decodedu);
	ASSERT_EQ(test16u, decodedu);

    codec.encodeBE( test16u, msg, 2);
    ASSERT_EQ( (char)0xFE, msg.get(2));
    ASSERT_EQ( (char)0xDC, msg.get(3));
	codec.decodeBE(data, 2, decodedu);
	ASSERT_EQ(test16u, decodedu);
}

TEST( Codec, 32bits) {
    Message msg;
    Codec codec;
	char * data = msg.getData();

	int32_t test32 = 0x01234567;
	int32_t decode32;

    codec.encodeLE( test32, msg, 0);
    ASSERT_EQ( (char)0x67, msg.get(0));
    ASSERT_EQ( (char)0x45, msg.get(1));
    ASSERT_EQ( (char)0x23, msg.get(2));
    ASSERT_EQ( (char)0x01, msg.get(3));
	codec.decodeLE(data, 0, decode32);
	ASSERT_EQ( test32, decode32);

    codec.encodeBE( test32, msg, 4);
    ASSERT_EQ( (char)0x01, msg.get(4));
    ASSERT_EQ( (char)0x23, msg.get(5));
    ASSERT_EQ( (char)0x45, msg.get(6));
    ASSERT_EQ( (char)0x67, msg.get(7));
	codec.decodeBE(data, 4, decode32);
	ASSERT_EQ(test32, decode32);

	uint32_t test32u = 0xFEDCBA98;
	uint32_t decode32u;

    codec.encodeLE( test32u, msg, 8);
    ASSERT_EQ( (char)0x98, msg.get(8));
    ASSERT_EQ( (char)0xBA, msg.get(9));
    ASSERT_EQ( (char)0xDC, msg.get(10));
    ASSERT_EQ( (char)0xFE, msg.get(11));
	codec.decodeLE(data, 8, decode32u);
	ASSERT_EQ(test32u, decode32u);

    codec.encodeBE( test32u, msg, 12);
    ASSERT_EQ( (char)0xFE, msg.get(12));
    ASSERT_EQ( (char)0xDC, msg.get(13));
    ASSERT_EQ( (char)0xBA, msg.get(14));
    ASSERT_EQ( (char)0x98, msg.get(15));
	codec.decodeBE(data, 12, decode32u);
	ASSERT_EQ(test32u, decode32u);
}

TEST( Codec, 64bits) {
    Message msg;
    Codec codec;
	char * data = msg.getData();

	int64_t test64 = 0x0123456789ABCDEFL;
	int64_t decode64;
	codec.encodeLE(test64, msg, 0);
    ASSERT_EQ( (char)0xEF, msg.get(0));
    ASSERT_EQ( (char)0xCD, msg.get(1));
    ASSERT_EQ( (char)0xAB, msg.get(2));
    ASSERT_EQ( (char)0x89, msg.get(3));
    ASSERT_EQ( (char)0x67, msg.get(4));
    ASSERT_EQ( (char)0x45, msg.get(5));
    ASSERT_EQ( (char)0x23, msg.get(6));
    ASSERT_EQ( (char)0x01, msg.get(7));
	codec.decodeLE(data, 0, decode64);
	ASSERT_EQ( test64, decode64);

    codec.encodeBE( test64, msg, 10);
    ASSERT_EQ( (char)0x01, msg.get(10));
    ASSERT_EQ( (char)0x23, msg.get(11));
    ASSERT_EQ( (char)0x45, msg.get(12));
    ASSERT_EQ( (char)0x67, msg.get(13));
    ASSERT_EQ( (char)0x89, msg.get(14));
    ASSERT_EQ( (char)0xAB, msg.get(15));
    ASSERT_EQ( (char)0xCD, msg.get(16));
    ASSERT_EQ( (char)0xEF, msg.get(17));
	codec.decodeBE(data, 10, decode64);
	ASSERT_EQ(test64, decode64);

	uint64_t test64u = 0xFEDCBA9876543210L;
	uint64_t decode64u;
    codec.encodeLE( test64u, msg, 20);
    ASSERT_EQ( (char)0x10, msg.get(20));
    ASSERT_EQ( (char)0x32, msg.get(21));
    ASSERT_EQ( (char)0x54, msg.get(22));
    ASSERT_EQ( (char)0x76, msg.get(23));
    ASSERT_EQ( (char)0x98, msg.get(24));
    ASSERT_EQ( (char)0xBA, msg.get(25));
    ASSERT_EQ( (char)0xDC, msg.get(26));
    ASSERT_EQ( (char)0xFE, msg.get(27));
	codec.decodeLE(data, 20, decode64u);
	ASSERT_EQ(test64u, decode64u);

    codec.encodeBE( test64u, msg, 30);
    ASSERT_EQ( (char)0xFE, msg.get(30));
    ASSERT_EQ( (char)0xDC, msg.get(31));
    ASSERT_EQ( (char)0xBA, msg.get(32));
    ASSERT_EQ( (char)0x98, msg.get(33));
    ASSERT_EQ( (char)0x76, msg.get(34));
    ASSERT_EQ( (char)0x54, msg.get(35));
    ASSERT_EQ( (char)0x32, msg.get(36));
    ASSERT_EQ( (char)0x10, msg.get(37));
	codec.decodeBE(data, 30, decode64u);
	ASSERT_EQ(test64u, decode64u);
}

int main( int argc, char **argv) {
    testing::InitGoogleTest( &argc, argv);
    return RUN_ALL_TESTS();
}
