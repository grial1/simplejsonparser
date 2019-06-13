// Author: Gastón Rial
// Date: 2019-06-12

#include "jsonparser_impl.h"
#include <iostream>
#include <memory>

using namespace jsonparser;
using namespace std;

int main(int argc,char** argv)
{

    /*
        Test with two JSON examples
        TODO: Testing with Catch2
    */
    string sJson = "{\"name\":\"Juan\",\"edad\":55,\"literate\":true,\"payment\":17.5,\"another thing\":'hola mundo'}";
    string sJson2 = "{\"City\":\"Colonia\",\"listOne\":[23,18,32],\"listTwo\":[2.3,4.5,7.8],\"double\":417.5}";
    Json oJson;
    Json oJson2;
    encodeSimpleJson(sJson,oJson);
    encodeSimpleJson(sJson2,oJson2);    
    cout << oJson << endl;
    cout << oJson2 << endl;
    cout << oJson.get("name") << endl;
    cout << oJson.get("edad") << endl;
    oJson.addKey("repiola", vector<string>{string("uno"),string("dos")});
    oJson.addKey("repiola_otro", vector<double>{2.3,4.5});
    cout << oJson << endl;
    saveJson(oJson,"./example.json");

    return 0;
}