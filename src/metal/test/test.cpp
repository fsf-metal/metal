#include <gtest/gtest.h>

#include <metal/Codec.h>
#include <metal/Message.h>

using namespace std;
using namespace Metal;

TEST( Codec, encodeString) {

	Message msg;
    Codec codec;

	std::string str = "This is a 30 characters string";
	codec.encode(str, msg, 0, 10);
	ASSERT_EQ( 'T', msg.get(0));
	ASSERT_EQ( ' ', msg.get(9));
	ASSERT_EQ( 0, msg.get(10));

	// TODO Test integer encoding
}

TEST( Codec, int8) {
    Message msg;
    Codec codec;

	int8_t test8 = 0xF1;
    codec.encode( test8, msg, 0);
    ASSERT_EQ( (char)0xF1, msg.get(0));
}

TEST( Codec, int16) {
    Message msg;
    Codec codec;

	int16_t test16 = 0x0123;
    codec.encodeLittleEndian( test16, msg, 0);
    ASSERT_EQ( (char)0x23, msg.get(0));
    ASSERT_EQ( (char)0x01, msg.get(1));
    codec.encodeBigEndian( test16, msg, 2);
    ASSERT_EQ( (char)0x01, msg.get(2));
    ASSERT_EQ( (char)0x23, msg.get(3));

    uint16_t test16u = 0xFEDC;
    codec.encodeLittleEndian( test16u, msg, 0);
    ASSERT_EQ( (char)0xDC, msg.get(0));
    ASSERT_EQ( (char)0xFE, msg.get(1));
    codec.encodeBigEndian( test16u, msg, 2);
    ASSERT_EQ( (char)0xFE, msg.get(2));
    ASSERT_EQ( (char)0xDC, msg.get(3));
}

TEST( Codec, int32) {
    Message msg;
    Codec codec;

	int32_t test32 = 0x01234567;

    codec.encodeLittleEndian( test32, msg, 0);
    ASSERT_EQ( (char)0x67, msg.get(0));
    ASSERT_EQ( (char)0x45, msg.get(1));
    ASSERT_EQ( (char)0x23, msg.get(2));
    ASSERT_EQ( (char)0x01, msg.get(3));

    codec.encodeBigEndian( test32, msg, 4);
    ASSERT_EQ( (char)0x01, msg.get(4));
    ASSERT_EQ( (char)0x23, msg.get(5));
    ASSERT_EQ( (char)0x45, msg.get(6));
    ASSERT_EQ( (char)0x67, msg.get(7));

	uint32_t test32u = 0xFEDCBA98;

    codec.encodeLittleEndian( test32u, msg, 8);
    ASSERT_EQ( (char)0x98, msg.get(8));
    ASSERT_EQ( (char)0xBA, msg.get(9));
    ASSERT_EQ( (char)0xDC, msg.get(10));
    ASSERT_EQ( (char)0xFE, msg.get(11));

    codec.encodeBigEndian( test32u, msg, 12);
    ASSERT_EQ( (char)0xFE, msg.get(12));
    ASSERT_EQ( (char)0xDC, msg.get(13));
    ASSERT_EQ( (char)0xBA, msg.get(14));
    ASSERT_EQ( (char)0x98, msg.get(15));
}

TEST( Codec, int64) {
    Message msg;
    Codec codec;

	int64_t test64 = 0x0123456789ABCDEFL;
    codec.encodeLittleEndian( test64, msg, 0);
    ASSERT_EQ( (char)0xEF, msg.get(0));
    ASSERT_EQ( (char)0xCD, msg.get(1));
    ASSERT_EQ( (char)0xAB, msg.get(2));
    ASSERT_EQ( (char)0x89, msg.get(3));
    ASSERT_EQ( (char)0x67, msg.get(4));
    ASSERT_EQ( (char)0x45, msg.get(5));
    ASSERT_EQ( (char)0x23, msg.get(6));
    ASSERT_EQ( (char)0x01, msg.get(7));

    codec.encodeBigEndian( test64, msg, 10);
    ASSERT_EQ( (char)0x01, msg.get(10));
    ASSERT_EQ( (char)0x23, msg.get(11));
    ASSERT_EQ( (char)0x45, msg.get(12));
    ASSERT_EQ( (char)0x67, msg.get(13));
    ASSERT_EQ( (char)0x89, msg.get(14));
    ASSERT_EQ( (char)0xAB, msg.get(15));
    ASSERT_EQ( (char)0xCD, msg.get(16));
    ASSERT_EQ( (char)0xEF, msg.get(17));

	uint64_t test64u = 0xFEDCBA9876543210L;
    codec.encodeLittleEndian( test64u, msg, 20);
    ASSERT_EQ( (char)0x10, msg.get(20));
    ASSERT_EQ( (char)0x32, msg.get(21));
    ASSERT_EQ( (char)0x54, msg.get(22));
    ASSERT_EQ( (char)0x76, msg.get(23));
    ASSERT_EQ( (char)0x98, msg.get(24));
    ASSERT_EQ( (char)0xBA, msg.get(25));
    ASSERT_EQ( (char)0xDC, msg.get(26));
    ASSERT_EQ( (char)0xFE, msg.get(27));

    codec.encodeBigEndian( test64u, msg, 30);
    ASSERT_EQ( (char)0xFE, msg.get(30));
    ASSERT_EQ( (char)0xDC, msg.get(31));
    ASSERT_EQ( (char)0xBA, msg.get(32));
    ASSERT_EQ( (char)0x98, msg.get(33));
    ASSERT_EQ( (char)0x76, msg.get(34));
    ASSERT_EQ( (char)0x54, msg.get(35));
    ASSERT_EQ( (char)0x32, msg.get(36));
    ASSERT_EQ( (char)0x10, msg.get(37));
}

int main( int argc, char **argv) {
    testing::InitGoogleTest( &argc, argv);
    return RUN_ALL_TESTS();
}
