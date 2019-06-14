/// author Gastón Rial
/// date 2019-06-12

#include "jsonparser_impl.h"
#include <iostream>
#include <memory>

using namespace jsonparser;
using namespace std;

int main(int argc,char** argv)
{

    /*
     *   Example with three  simple JSONs (not nested)
    */
    
    /// Initialize two strings
    string sJson = "{\"name\":\"Juan\",   \"edad\":55,\"literate\":true,\"payment\":    17.5,\"another thing\":'hola mundo'}";
    string sJson2 = "{  \"City\":\"Colonia\",\"listOne\": [23,18,32]  ,\"listTwo\": [2.3,4.5,7.8],\"double\":417.5}";
    
    /// Initialize three JSONs
    Json oJson;
    Json oJson2;
    Json oJson3;

    /// Encode the strings into the first two Json objects
    encodeSimpleJson(sJson,oJson);
    encodeSimpleJson(sJson2,oJson2);

    /// Show values in stdou    
    cout << "[+]First JSON: " << oJson << endl;
    cout << "[+]Second JSON: " << oJson2 << endl;

    /// Show values associated with keys
    cout <<"[+]Key name: "<< oJson.get("name") << endl;
    cout <<"[+]Key edad: "<< oJson.get("edad") << endl;

    /// Add new Keys to the Json and show it again in the stdout
    oJson.addKey("repiola", vector<string>{string("uno"),string("dos")});
    oJson.addKey("repiola_otro", vector<double>{2.3,4.5});
    cout << "[+]First JSON with new keys: " << oJson << endl;

    /// Save Json object into a file
    saveJson(oJson,"./example.json");

    /// Encode JSON string as Json object
    oJson3 = sJson2;
    
    /// Show its values
    cout << "[+]Third JSON: " << oJson3 << endl;
    
    return 0;
}