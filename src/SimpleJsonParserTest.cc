/// author Gastón Rial
/// date 2019-06-13

#define CATCH_CONFIG_MAIN   ///< catch2 main function
#include "catch.hpp"        ///< Testing library. See: https://github.com/catchorg/Catch2
#include "jsonparser_impl.h"

SCENARIO( "A Json object can be created from a string", "[jsonparser]" ) {

    GIVEN("A JSON string")
    {

        string sJson = "{\"Key\":\"Value\"}";
        jsonparser::Json oJson;

        WHEN("calling encodeSimpleJson")
        {
            jsonparser::encodeSimpleJson(sJson,oJson);

            THEN("The properties are maintained")
            {
                
                REQUIRE( oJson.get("Key").compare("\"Value\"") == 0 );
                REQUIRE( sJson.compare(jsonparser::to_string(oJson)) == 0 );

            }

        }

        WHEN("calling addKey")
        {
            oJson.addKey("Key2", 1);

            THEN("The value 1 is added")
            {
                
                REQUIRE( oJson.get("Key2").compare("1") == 0 );
                REQUIRE( *(static_cast<int*>(oJson["Key2"].getValue())) == 1 );

            }

        }

    }


}