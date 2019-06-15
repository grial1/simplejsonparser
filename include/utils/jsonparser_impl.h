/// author Gastón Rial
/// date 2019-06-12

#ifndef SIMPLEJSONPARSER_INCLUDE_UTILS_JSON_PARSER_IMPL_H_
#define SIMPLEJSONPARSER_INCLUDE_UTILS_JSON_PARSER_IMPL_H_

#include "jsonparser.h"

using namespace jsonparser;

static const size_t npos = -1;

static inline void getKey(const string& sIn, string& sKey)
{

    int start = sIn.find_first_of('\"');
    int end = sIn.find_last_of('\"');
    sKey = sIn.substr(start+1,end-start-1);

}

static inline void getValue(const string& sIn, string& sValue)
{

    int start = sIn.find_first_not_of(' ');
    int end = sIn.find_last_not_of(' ');
    sValue = sIn.substr(start,end-start+1);

}

static inline void splitString(const string& str, vector<string>& output, char delim = ' ')
{
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim)) {
        output.push_back(token);
    }
}

template <typename V>
JsonValue<V>::JsonValue(V& oValue, ValueType oType)
{

    this->_value = oValue;
    this->_oType = oType;

}

template <typename V>
const V& JsonValue<V>::getValue() const
{

    return (this->_value);

}

template <typename V>
void JsonValue<V>::setValue(const V& oValue)
{

    this->_value = oValue;

}

template <typename V>
const ValueType& JsonValue<V>::getType() const
{

    return (this->_oType);

}

template <typename V>
JsonValue<V>::~JsonValue()
{

    if(typeid(V) == typeid(void*) && this->_value != nullptr)
    {
        switch(this->_oType)
        {
            case ValueType::JSON_BOOL:
                delete (static_cast<bool*>(this->_value));
                break;
            case ValueType::JSON_INTEGER:
                delete (static_cast<int*>(this->_value));
                break;
            case ValueType::JSON_DOUBLE:
                delete (static_cast<double*>(this->_value));
                break;
            case ValueType::JSON_STRING:
                delete (static_cast<string*>(this->_value));
                break;
            case ValueType::JSON_OBJECT:
                delete (static_cast<Json*>(this->_value));
                break;
            case ValueType::JSON_ARRAY_STRING:
                delete (static_cast<vector<string>*>(this->_value));
                break;
            case ValueType::JSON_ARRAY_DOUBLE:
                delete (static_cast<vector<double>*>(this->_value));
                break;
            case ValueType::JSON_ARRAY_INTEGER:
                delete (static_cast<vector<int>*>(this->_value));
                break;
            default:
                delete this->_value;
                break;
        }
    }

}

Json::Json(){}

Json::Json(const string& oKey, JsonValue<void*>* oValue)
{

    this->_oKeyList.push_back(pair<string,int>(oKey,this->_size));
    this->_oValueList.push_back(oValue);
    ++(this->_size);

}

Json::Json(const string& oKey, const JsonValue<void*>& oValue):
Json(oKey, new JsonValue<void*>(oValue))
{}

Json::Json(const string& oKey,const bool& oValue):
Json()
{
    
    void* pValue = static_cast<void*>(new bool(oValue));
    Json(oKey, new JsonValue<void*>(pValue,ValueType::JSON_BOOL));

}

Json::Json(const string& oKey,const int& oValue):
Json()
{
    void* pValue = static_cast<void*>(new int(oValue));
    Json(oKey, new JsonValue<void*>(pValue,ValueType::JSON_INTEGER));
}

Json::Json(const string& oKey,const double& oValue):
Json()
{

    void* pValue = static_cast<void*>(new double(oValue));
    Json(oKey, new JsonValue<void*>(pValue,ValueType::JSON_DOUBLE));

}

Json::Json(const string& oKey,const string& oValue):
Json()
{

    void* pValue = static_cast<void*>(new string(oValue));
    Json(oKey, new JsonValue<void*>(pValue,ValueType::JSON_STRING));

}

Json::Json(const string& oKey,const Json& oValue):
Json()
{

    void* pValue = static_cast<void*>(new Json(oValue));
    Json(oKey, new JsonValue<void*>(pValue,ValueType::JSON_OBJECT));

}

Json::Json(const string& oKey,const vector<string>& oValue):
Json()
{

    void* pValue = static_cast<void*>(new vector<string>(oValue));
    Json(oKey, new JsonValue<void*>(pValue,ValueType::JSON_ARRAY_STRING));

}

Json::Json(const string& oKey,const vector<int>& oValue):
Json()
{

    void* pValue = static_cast<void*>(new vector<int>(oValue));
    Json(oKey, new JsonValue<void*>(pValue,ValueType::JSON_ARRAY_INTEGER));

}

Json::Json(const string& oKey,const vector<double>& oValue):
Json()
{

    void* pValue = static_cast<void*>(new vector<double>(oValue));
    Json(oKey, new JsonValue<void*>(pValue,ValueType::JSON_ARRAY_DOUBLE));

}

JsonValue<void*>& Json::operator[](const char* oKey) const
{
    string sKey(oKey);
    for(auto jsonPair: this->_oKeyList)
        if( sKey.compare(std::get<0>(jsonPair)) == 0 )
        {
            int valueIndex = std::get<1>(jsonPair);
            return *(this->_oValueList[valueIndex]);
        }    
    
    throw runtime_error("Run-Time Error: Key does not belong to json"); // < Run-Time Error: Key does not belong to json

}           

const vector<pair<string,int>>& Json::getKeyList() const
{

    return (this->_oKeyList);

}

const vector<JsonValue<void*>*>& Json::getValueList() const
{

    return (this->_oValueList);

}

int Json::getJsonSize() const
{

    return (this->_size);

}

void Json::addKey(const string& oKey,JsonValue<void*>* oValue)
{

    this->_oKeyList.push_back(pair<string,int>(oKey,this->_size));
    this->_oValueList.push_back(oValue);
    ++(this->_size);

}

void Json::addKey(const string& oKey,const JsonValue<void*>& oValue)
{

    addKey(oKey, new JsonValue<void*>(oValue));

}

void Json::addKey(const string& oKey,const bool& oValue)
{

    void* pValue = static_cast<void*>(new bool(oValue));
    addKey(oKey, new JsonValue<void*>(pValue,ValueType::JSON_BOOL));

}

void Json::addKey(const string& oKey,const int& oValue)
{

    void* pValue = static_cast<void*>(new int(oValue));
    addKey(oKey, new JsonValue<void*>(pValue,ValueType::JSON_INTEGER));

}

void Json::addKey(const string& oKey,const double& oValue)
{

    void* pValue = static_cast<void*>(new double(oValue));
    addKey(oKey, new JsonValue<void*>(pValue,ValueType::JSON_DOUBLE));

}

void Json::addKey(const string& oKey,const string& oValue)
{

    void* pValue = static_cast<void*>(new string(oValue));
    addKey(oKey, new JsonValue<void*>(pValue,ValueType::JSON_STRING));

}

void Json::addKey(const string& oKey,const Json& oValue)
{

    void* pValue = static_cast<void*>(new Json(oValue));
    addKey(oKey, new JsonValue<void*>(pValue,ValueType::JSON_STRING));

}

void Json::addKey(const string& oKey,const vector<string>& oValue)
{

    void* pValue = static_cast<void*>(new vector<string>(oValue));
    addKey(oKey, new JsonValue<void*>(pValue,ValueType::JSON_ARRAY_STRING));

}

void Json::addKey(const string& oKey,const vector<int>& oValue)
{

    void* pValue = static_cast<void*>(new vector<int>(oValue));
    addKey(oKey, new JsonValue<void*>(pValue,ValueType::JSON_ARRAY_INTEGER));

}

void Json::addKey(const string& oKey,const vector<double>& oValue)
{

    void* pValue = static_cast<void*>(new vector<double>(oValue));
    addKey(oKey, new JsonValue<void*>(pValue,ValueType::JSON_ARRAY_DOUBLE));

}

string Json::get(const char* oKey) const
{

    JsonValue<void*>* oJV = &((*this)[oKey]);
    if( oJV != nullptr )
        return to_string(*oJV);
    else
        throw runtime_error("Error: El valor es un <Json Object>");

}


Json::~Json()
{

    this->_oKeyList.clear();
    this->_oValueList.clear();    

}

template <typename V>
ostream& jsonparser::operator<<(ostream& out,const JsonValue<V>& oJsonValue)
{

    if(typeid(V) == typeid(void*) && oJsonValue.getValue() != nullptr)
    {
        switch(oJsonValue.getType())
        {
            case ValueType::JSON_BOOL:
                out << *(static_cast<bool*>(oJsonValue.getValue()));
                break;
            case ValueType::JSON_INTEGER:
                out << *(static_cast<int*>(oJsonValue.getValue()));
                break;
            case ValueType::JSON_DOUBLE:
                out << *(static_cast<double*>(oJsonValue.getValue()));
                break;
            case ValueType::JSON_STRING:
                out << "\"" << *(static_cast<string*>(oJsonValue.getValue())) << "\"";
                break;
            case ValueType::JSON_OBJECT:
                out << " { ";
                out << *(static_cast<Json*>(oJsonValue.getValue())); /*TODO: Resolve recursion error */
                out << " } ";
                break;
            case ValueType::JSON_ARRAY_STRING:
                {
                    out << "[" ;
                    vector<string>* oVector = (static_cast<vector<string>*>(oJsonValue.getValue()));
                    for (auto oIter = oVector->begin(); oIter != oVector->end(); ++oIter)
                    {
                        out << "\"" << *oIter << "\"";
                        if(next(oIter) != oVector->end())
                            out << ",";
                    }
                    out << "]" ;
                    break;
                }
            case ValueType::JSON_ARRAY_DOUBLE:
                {
                    out << "[" ;
                    vector<double>* oVector = (static_cast<vector<double>*>(oJsonValue.getValue()));
                    for (auto oIter = oVector->begin(); oIter != oVector->end(); ++oIter)
                    {
                        out << *oIter;
                        if(next(oIter) != oVector->end())
                            out << ",";
                    }
                    out << "]" ;
                    break;
                }
            case ValueType::JSON_ARRAY_INTEGER:
                {
                    out << "[" ;
                    vector<int>* oVector = (static_cast<vector<int>*>(oJsonValue.getValue()));
                    for (auto oIter = oVector->begin(); oIter != oVector->end(); ++oIter)
                    {
                        out << *oIter;
                        if(next(oIter) != oVector->end())
                            out << ",";
                    }
                    out << "]" ;
                    break;
                }
            default:
                out << oJsonValue.getValue();
                break;
        }
    }

    return out;
}


ostream& jsonparser::operator<<(ostream& out,const Json& oJson)
{

    out << "{";
    for(auto oIter = oJson.getKeyList().begin(); oIter != oJson.getKeyList().end(); ++oIter)
    {
        string sKey = std::get<0>(*oIter);
        out << "\"" << sKey << "\":";
        
        int valueIndex = std::get<1>(*oIter);
        out << *(oJson.getValueList()[valueIndex]); /*TODO: Resolve recursion error */

        if(next(oIter) != oJson.getKeyList().end())
            out << ",";

    }
    out << "}";

    return out;

}

template <typename V>
string jsonparser::to_string(const JsonValue<V>& oJV)
{

    if( typeid(V) == typeid(void*) )
    {

        switch ( oJV.getType() )
        {
            case ValueType::JSON_STRING:
                return "\""+*(static_cast<string*>(oJV.getValue()))+"\"";
                break;
            case ValueType::JSON_BOOL:
                return std::to_string(*(static_cast<bool*>(oJV.getValue())));
                break;
            case ValueType::JSON_INTEGER:
                return std::to_string(*(static_cast<int*>(oJV.getValue())));
                break;
            case ValueType::JSON_DOUBLE:
                return std::to_string(*(static_cast<double*>(oJV.getValue())));
                break;
            case ValueType::JSON_ARRAY_STRING:
            {
                string oRet = "[";
                vector<string>* oVector = (static_cast<vector<string>*>(oJV.getValue()));
                for (auto oIter = oVector->begin(); oIter != oVector->end(); ++oIter)
                {
                    oRet += "\"" + *oIter + "\"";
                    if(next(oIter) != oVector->end())
                        oRet += ",";
                }
                oRet += "]" ;
                return oRet;
                break;
            }
            case ValueType::JSON_ARRAY_INTEGER:
            {
                string oRet = "[";
                vector<int>* oVector = (static_cast<vector<int>*>(oJV.getValue()));
                for (auto oIter = oVector->begin(); oIter != oVector->end(); ++oIter)
                {
                    oRet += std::to_string(*oIter);
                    if(next(oIter) != oVector->end())
                        oRet += ",";
                }
                oRet += "]" ;
                return oRet;
                break;
            }
            case ValueType::JSON_ARRAY_DOUBLE:
            {
                string oRet = "[";
                vector<double>* oVector = (static_cast<vector<double>*>(oJV.getValue()));
                for (auto oIter = oVector->begin(); oIter != oVector->end(); ++oIter)
                {
                    oRet += std::to_string(*oIter);
                    if(next(oIter) != oVector->end())
                        oRet += ",";
                }
                oRet += "]" ;
                return oRet;
                break;
            }
            default:
                return string("null");
                break;
        }

    } 
    else if ( oJV.getType() == ValueType::JSON_OBJECT ) {

        return string("<JSON OBJECT>");

    } 
    else
    {

        throw runtime_error("Error: El valor es indefinido");

    }

}

string jsonparser::to_string(const Json& oJson)
{

    string oRet = "{";
    for(auto oIter = oJson.getKeyList().begin(); oIter != oJson.getKeyList().end(); ++oIter)
    {
        string sKey = std::get<0>(*oIter);
        oRet += "\"" + sKey + "\":";
        
        int valueIndex = std::get<1>(*oIter);
        oRet += to_string(*(oJson.getValueList()[valueIndex])); /*TODO: Resolve recursion error */

        if(next(oIter) != oJson.getKeyList().end())
            oRet += ",";

    }
    oRet += "}";

    return oRet;

}

static inline void getStringValue(const string& element, vector<string>& oVecValue )
{
  
  oVecValue.push_back(element.substr(1,element.length()-2));

}

static inline void getDoubleValue(const string& element, vector<double>& oVecValue )
{

    vector<string> oVecDouble;
    splitString(element,oVecDouble,'.');
    double value = static_cast<double>(atoi(oVecDouble[0].c_str()));
    double raw_decimal = static_cast<double>(atoi(oVecDouble[1].c_str()));
    double power =  ceil(raw_decimal/10);
    double decimal = raw_decimal/pow(10,power);
    value += decimal;
    oVecValue.push_back(value);

}

static inline void getIntValue(const string& element, vector<int>& oVecValue)
{

    oVecValue.push_back(atoi(element.c_str()));

}

template <typename V>
static inline void addArrayValue (const string& sKey, const string& sValues, Json& oRet)
{

    vector<string> sVecValue;
    splitString(sValues,sVecValue,',');
    
    vector<string> sArrayValue;
    vector<double> dArrayValue;
    vector<int> iArrayValue;

    for(auto sIter = sVecValue.begin(); sIter != sVecValue.end(); ++sIter)
    {
        string element;
        if (sIter == sVecValue.begin())
            element = (*sIter).substr(1,(*sIter).length()-1);
        else
            element = *sIter;

        if( typeid(V) == typeid(string))
        {
            
            getStringValue(element, sArrayValue);
            if( next(sIter) == sVecValue.end() )
                oRet.addKey(sKey, sArrayValue);
    
        } 
        else if( typeid(V) == typeid(double) )
        {

            getDoubleValue(element, dArrayValue );
            if( next(sIter) == sVecValue.end() )
                oRet.addKey(sKey, dArrayValue);

        }
        else if( typeid(V) == typeid(int) )
        {

            getIntValue(element, iArrayValue);
            if( next(sIter) == sVecValue.end() )
                oRet.addKey(sKey, iArrayValue);

        }
        else
        {
        
            throw runtime_error("ERROR: type is not recognized");

        }
    }
    
}

static inline void addSimpleValue(const string& sKey, const string& sValue, Json& oRet)
{

    if(strncmp(sValue.c_str(),"false\0",strlen("false\0")) == 0)
    {
        
        oRet.addKey(sKey,false);
    
    }
    else if(strncmp(sValue.c_str(),"true\0",strlen("true\0")) == 0)
    {
        oRet.addKey(sKey,true);
    }
    else if( sValue.find('\"') != npos )
    {
        vector<string> oVecValue;
        splitString(sValue,oVecValue,'\"');
        oRet.addKey(sKey,oVecValue[1]); 
    }
    else if( sValue.find('\'') != npos )
    {
        vector<string> oVecValue;
        splitString(sValue,oVecValue,'\'');
        oRet.addKey(sKey,oVecValue[1]); 
    }
    else if(sValue.find('.') != npos)
    {
        vector<string> oVecValue;
        splitString(sValue,oVecValue,'.');
        double value = static_cast<double>(atoi(oVecValue[0].c_str()));
        double raw_decimal = static_cast<double>(atoi(oVecValue[1].c_str()));
        double power =  ceil(raw_decimal/10);
        double decimal = raw_decimal/pow(10,power);
        value += decimal;
        oRet.addKey(sKey,value);
    }
    else
    {
        
        int value = atoi(sValue.c_str());
        oRet.addKey(sKey,value);
    }

}

void jsonparser::encodeSimpleJson(const string& sJson, Json& oRet)
{

    vector<string> oVec;
    splitString(sJson,oVec,':');
    string sKey;

    for(auto sIter = oVec.begin(); sIter != oVec.end(); ++sIter)
    {


        if(sIter == oVec.begin())
        {   
            
            getKey((*sIter), sKey);
            continue;

        }        
        vector<string> oVecValueKey;

        if( (*sIter).find('[') != npos )
        {

            // get sValue
            splitString(*sIter,oVecValueKey,']');
            string sValue;
            getValue(oVecValueKey[0], sValue);

            // para cada tipo
            if( sValue.find('\"') != npos )
            {

                addArrayValue<string>(sKey, sValue, oRet);

            }
            else if( sValue.find('.') != npos )
            {

                addArrayValue<double>(sKey, sValue, oRet);

            }
            else
            {

                addArrayValue<int>(sKey, sValue, oRet);
            
            }

            if( next(sIter) != oVec.end() )
                getKey(oVecValueKey[1], sKey);
            
        } else {

            splitString(*sIter,oVecValueKey,',');
            string sValue;
            getValue(oVecValueKey[0], sValue);

            addSimpleValue(sKey, sValue, oRet);

            if( next(sIter) != oVec.end() )
                getKey(oVecValueKey[1], sKey);

        }

    }

}

void jsonparser::saveJson(const Json& oJson,const string& output_file_path)
{

    ofstream oFile(output_file_path);
    if (oFile.is_open())
    {
        oFile << to_string(oJson);
        oFile.close();
    }
    else
        throw runtime_error("Error: Could not open file");

}

void Json::operator=(const string& sJson)
{

    encodeSimpleJson(sJson, *this);

}

Json::operator string() const
{

    return to_string(*this);

}

template <typename V>
JsonValue<V>::operator string() const
{

    return to_string(*this);

}

#endif //<SIMPLEJSONPARSER_INCLUDE_UTILS_JSON_PARSER_IMPL_H_