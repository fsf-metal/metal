#include <gtest/gtest.h>
#include <json/json.h>

#include "../Field.h"

using namespace Bootstrapper;
using namespace std;

TEST(SmartExample, BooleanSanity) {
    ASSERT_TRUE( true) << "True is not True?";
    ASSERT_FALSE( false) << "False is not False?";
}

TEST( Fields, getType) {
    Json::Reader reader;
    FieldType expectedFieldType[4] = {FieldType::INT8,FieldType::INT16,FieldType::INT32,FieldType::INT64};
    int inputSize[4] = {1,2,4,8};
    std::string strJson;
    Json::Value val;
    FieldType type;
    for( int index = 0; index < 4; ++index) {
        strJson = "{\"name\":\"fieldName\",\"pos\":4,\"type\":\"int\",\"size\":" + to_string( inputSize[index]) + ",\"value\":0}";
        ASSERT_TRUE( reader.parse( strJson, val)) << "Could not parse input string:" << reader.getFormattedErrorMessages() << endl << "Input=" << strJson;
        type = Field::getType( val);
        ASSERT_EQ( expectedFieldType[index], type) << "Unexpected type for int/4";
    }

    // Try some invalid size
    strJson = "{\"name\":\"fieldName\",\"pos\":4,\"type\":\"int\",\"size\":3,\"value\":0}";
    ASSERT_TRUE( reader.parse( strJson, val)) << "Could not parse input string:" << reader.getFormattedErrorMessages() << endl << "Input=" << strJson;
    try {
        type = Field::getType( val);
        ASSERT_TRUE( false) << "Size 3 should be invalid";
    } catch( exception e) {

    }
}

int main( int argc, char **argv) {
    testing::InitGoogleTest( &argc, argv);
    return RUN_ALL_TESTS();
}
