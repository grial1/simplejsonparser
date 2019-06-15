/// author Gastón Rial
/// date 2019-06-12

#ifndef SIMPLEJSONPARSER_INCLUDE_UTILS_JSON_PARSER_H_
#define SIMPLEJSONPARSER_INCLUDE_UTILS_JSON_PARSER_H_

#include <utility>
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include <exception>
#include <sstream>
#include <typeinfo>
#include <cstring>
#include <cmath>

using namespace std;

/// namespace jsonparser
/// brief this namespace establishes the API
namespace jsonparser 
{
    /// brief enum ValueType
    /// description This enum has all the posible types a JsonValue object can have
    enum class ValueType{
                            JSON_NULL,          ///< JSON = null
                            JSON_BOOL,          ///< JSON = true or false
                            JSON_INTEGER,       ///< JSON = JSONNumber
                            JSON_DOUBLE,        ///< JSON = JSONNumber
                            JSON_STRING,        ///< JSON = JSONString
                            JSON_OBJECT,        ///< JSON = JSONObject
                            JSON_ARRAY_STRING,  ///< JSON = JSONArray
                            JSON_ARRAY_DOUBLE,  ///< JSON = JSONArray
                            JSON_ARRAY_INTEGER  ///< JSON = JSONArray
                        };
    
    
    class Json;
    /// class JsonValue
    /// brief used as a wrapper to be managed inside of a Json object
    template <typename V>
    class JsonValue
    {

        public:

            JsonValue(V& oValue, ValueType oType);  ///< constructor
            const V& getValue() const;              ///< accessor or getter method
            void setValue(const V& oValue);         ///< mutator or setter method
            const ValueType& getType() const;       ///< method that returns type
            operator string() const;                ///< transform operator

            ~JsonValue();                           ///< destructor

        private:
        
            V _value;                               ///< encapsulated value
            ValueType _oType;                       ///< type of value stored in JsonValue

    };

    /// class Json
    /// brief This is the actual Json, which can be accessed and modified easily
    class Json
    {

        public:
            
            Json();                                                         ///< constructor
            Json(const string& oKey,JsonValue<void*>* oValue);              ///< constructor
            Json(const string& oKey,const JsonValue<void*>& oValue);        ///< constructor
            Json(const string& oKey,const bool& oValue);                    ///< constructor
            Json(const string& oKey,const int& oValue);                     ///< constructor
            Json(const string& oKey,const double& oValue);                  ///< constructor
            Json(const string& oKey,const string& oValue);                  ///< constructor
            Json(const string& oKey,const Json& oValue);                    ///< constructor
            Json(const string& oKey,const vector<string>& oValue);          ///< constructor
            Json(const string& oKey,const vector<int>& oValue);             ///< constructor
            Json(const string& oKey,const vector<double>& oValue);          ///< constructor
            void operator=(const string& sJson);                            ///< assigment operator
            JsonValue<void*>& operator[](const char* oKey) const;           ///< subscripting operator
            const vector<pair<string,int>>& getKeyList() const;             ///< accessor or getter method
            const vector<JsonValue<void*>*>& getValueList() const;          ///< accessor or getter method
            int getJsonSize() const;                                        ///< accessor or getter method
            void addKey(const string& oKey,JsonValue<void*>* oValue);       ///< method for adding a new key
            void addKey(const string& oKey,const JsonValue<void*>& oValue); ///< method for adding a new key
            void addKey(const string& oKey,const bool& oValue);             ///< method for adding a new key
            void addKey(const string& oKey,const int& oValue);              ///< method for adding a new key
            void addKey(const string& oKey,const double& oValue);           ///< method for adding a new key
            void addKey(const string& oKey,const string& oValue);           ///< method for adding a new key
            void addKey(const string& oKey,const Json& oValue);             ///< method for adding a new key
            void addKey(const string& oKey,const vector<string>& oValue);   ///< method for adding a new key
            void addKey(const string& oKey,const vector<int>& oValue);      ///< method for adding a new key
            void addKey(const string& oKey,const vector<double>& oValue);   ///< method for adding a new key
            string get(const char* oKey) const;                             ///< method for returning string rep. of JsonValue
            operator string() const;                                        ///< transform operator

            ~Json();                                                        ///< destructor

        private:

            vector<pair<string,int>> _oKeyList;                             ///< List of Key:Index pairs
            vector<JsonValue<void*>*> _oValueList;                          ///< List of JsonValues
            int _size = 0;                                                  ///< Size of Json or number of keys

    };

    /// operator <<
    /// brief Let the simple (not of ValueType::JSON_OBJECT type) JsonValue objects to be printed to the stdout
    /// returns ostream
    template <typename V>
    ostream& operator<<(ostream& out,const JsonValue<V>& oJsonValue);

    /// operator <<
    /// brief Let the simple JSON object to be printed to the stdout
    /// returns ostream
    ostream& operator<<(ostream& out,const Json& oJson);

    /// function to_string
    /// brief Get the string out of a JsonValue
    /// returns string
    template <typename V>
    string to_string(const JsonValue<V>& oJV);

    /// function to_string
    /// brief Get the string out of a Json
    /// returns string
    string to_string(const Json& oJson);

    /// function parseSimpleJson
    /// brief Transform string to a Json object
    /// returns Json - outJson
    void encodeSimpleJson(const string& sJson,Json& outJson);

    /// function saveJson
    /// brief write simple (not nested) Json object to a file in output_file_path
    void saveJson(const Json& oJson,const string& output_file_path);

};

#endif //< SIMPLEJSONPARSER_INCLUDE_UTILS_JSON_PARSER_H_