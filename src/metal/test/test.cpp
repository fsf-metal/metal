#include <gtest/gtest.h>

#include <metal/Codec.h>

using namespace std;

TEST( Codec, encode) {
	int testValue = 0x01234567;

	Message msg;

	std::string str = "This is a 30 characters string";
	encode(str, msg, 0, 10);
	ASSERT_EQ( 'T', msg[0]);

	// TODO Test integer encoding
}

int main( int argc, char **argv) {
    testing::InitGoogleTest( &argc, argv);
    return RUN_ALL_TESTS();
}
