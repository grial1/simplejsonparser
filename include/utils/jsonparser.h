// Author: Gastón Rial
// Date: 2019-06-12

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

namespace jsonparser 
{
    enum class ValueType{
                            JSON_NULL,          // JSON = null
                            JSON_BOOL,          // JSON = true or false
                            JSON_INTEGER,       // JSON = JSONNumber
                            JSON_DOUBLE,        // JSON = JSONNumber
                            JSON_STRING,        // JSON = JSONString
                            JSON_OBJECT,        // JSON = JSONObject
                            JSON_ARRAY_STRING,  // JSON = JSONArray
                            JSON_ARRAY_DOUBLE,  // JSON = JSONArray
                            JSON_ARRAY_INTEGER  // JSON = JSONArray
                        };
    // forward declaration, necessary to be used in JsonValue
    class Json;

    template <typename V>
    class JsonValue
    {

        public:

            JsonValue(V& oValue, ValueType oType);
            const V& getValue() const;
            void setValue(const V& oValue);
            const ValueType& getType() const;

            ~JsonValue();

        private:
        
            V _value;
            ValueType _oType;

    };

    class Json
    {

        public:
            
            Json();
            Json(const string& oKey,JsonValue<void*>* oValue);
            Json(const string& oKey,const JsonValue<void*>& oValue);
            Json(const string& oKey,const bool& oValue);
            Json(const string& oKey,const int& oValue);
            Json(const string& oKey,const double& oValue);
            Json(const string& oKey,const string& oValue);
            Json(const string& oKey,const Json& oValue);
            Json(const string& oKey,const vector<string>& oValue);
            Json(const string& oKey,const vector<int>& oValue);
            Json(const string& oKey,const vector<double>& oValue);
            JsonValue<void*>& operator[](const char* oKey) const;
            const vector<pair<string,int>>& getKeyList() const;
            const vector<JsonValue<void*>*>& getValueList() const;
            int getJsonSize() const; // Number of Keys
            void addKey(const string& oKey,JsonValue<void*>* oValue);
            void addKey(const string& oKey,const JsonValue<void*>& oValue);
            void addKey(const string& oKey,const bool& oValue);
            void addKey(const string& oKey,const int& oValue);
            void addKey(const string& oKey,const double& oValue);
            void addKey(const string& oKey,const string& oValue);
            void addKey(const string& oKey,const Json& oValue);
            void addKey(const string& oKey,const vector<string>& oValue);
            void addKey(const string& oKey,const vector<int>& oValue);
            void addKey(const string& oKey,const vector<double>& oValue);
            string get(const char* oKey) const;

            ~Json();

        private:
            vector<pair<string,int>> _oKeyList;
            vector<JsonValue<void*>*> _oValueList;
            int _size = 0;

    };

    template <typename V>
    ostream& operator<<(ostream& out,const JsonValue<V>& oJsonValue);

    ostream& operator<<(ostream& out,const Json& oJson);

    template <typename V>
    string to_string(const JsonValue<V>& oJV);

    string to_string(const Json& oJson);

    void encodeSimpleJson(const string& sJson,Json& outJson);

    void saveJson(const Json& oJson,const string& output_file_path);

};

#endif //< SIMPLEJSONPARSER_INCLUDE_UTILS_JSON_PARSER_H_