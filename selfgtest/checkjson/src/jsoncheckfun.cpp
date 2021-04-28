//
// Created by blithepan on 2020/8/13.
//

#include "../include/jsoncheckfun.h"
#include "reader.h"
#include "stringbuffer.h"
#include "filereadstream.h"
#include "filewritestream.h"

#include <cstdio>
#include <iostream>
#include <stdlib.h>

using namespace rapidjson;
using namespace std;

#define KEY     "key"
#define TYPE    "type"
#define LEN     "len"
#define VALUE   "value"
#define FORCE   "force"
#define FORCE_FLAG   "Y"

#define JOSON_TYPE_STRING   "S"
#define JOSON_TYPE_INT      "N"
#define JOSON_TYPE_INT64    "N64"
#define JOSON_TYPE_DOUBLE   "D"
#define JOSON_TYPE_OBJECT   "O"
#define JOSON_TYPE_ARRAY    "A"
#define JOSON_TYPE_OBJECT_ARRAY   "AO"

bool JsonCheckObject(const Value & v,const Value& checkjson, const char* name, string type, unsigned int len);

static const char* kTypeNames[] =
        { "Null", "False", "True", "Object", "Array", "String", "Number" };

void logValue(const Value& v, const char* name){
    if(!name){
        printf(" log name is not null!\n");
        return ;
    }
    printf("node=>%s ",name);
    if(v.IsString()) {
        printf("=%s\n",v.GetString());
        return ;
    }else if(v.IsDouble()){
        printf("=%f\n",v.GetDouble());
        return ;
    } else if(v.IsInt()){
        printf("=%d\n",v.GetInt());
        return ;
    }else if(v.IsInt64()){
        printf("=%lld\n",v.GetInt64());
        return ;
    }else if(v.IsObject()) {
        for (Value::ConstMemberIterator iter = v.MemberBegin(); iter != v.MemberEnd(); ++iter) {
            const char *subName = iter->name.GetString();
            logValue(iter->value, subName);
        }
        printf("\n");
    }else if(v.IsArray()) {
        printf("array ...\n");
    }else{
        printf("\n log error\n");
    }
}

unsigned int GetLenParam(const Value& checkjson){
    if (checkjson.HasMember(LEN)) {
        if(!checkjson[LEN].IsNumber()){
            printf("len is not number!\n");
            return false;
        }
        return checkjson[LEN].GetInt();
    }
    return 0;
}

bool fetchvalue(const Value& v, string type) {
    if(v.IsString() && JOSON_TYPE_STRING == type) {
        printf("value string=%s\n",v.GetString());
        return true;
    } else if(v.IsInt() && (JOSON_TYPE_INT == type)){  //int
        printf("value Number=%d\n",v.GetInt());
        return true;
    } else if(v.IsInt64() && (JOSON_TYPE_INT64 == type)){
        printf("value int64=%lld\n",v.GetInt64());
        return true;
    } else if(v.IsDouble() && (JOSON_TYPE_DOUBLE == type)){
        printf("value Double=%f\n",v.GetDouble());
        return true;
    } else if(v.IsString()&& (JOSON_TYPE_INT == type)) {  //string-->int
        char *num;
        const char* valueStr = v.GetString();
        long result = strtol(valueStr, &num, 10);
        if (*num != '\0') {
            printf("value strtol error!%s\n", v.GetString());
            return false;
            /*...input is not a decimal number */
        }
        printf("value Number=%ld\n", result);
        return true;
    }
    std::cout <<"type not match:"<<type<<std::endl;
    return false;
}

bool JsonCheckObjectType(const Value & v,const Value& checkjson, const char* name){
    if(!name){
        printf("name is not null!\n");
        return false;
    }
    printf("object <type>  log [%s]:\n", name);
    if(!v.IsObject()) {
        printf("value is not object!\n");
        return false;
    }
    if(!checkjson.IsObject() ) {
        printf("check is not object!\n");
        return false;
    }
    printf("----json data---!\n");
    logValue(v,name);
    printf("----check data---!\n");
    logValue(checkjson,name);

    const Value &checkParams = checkjson;
    if(!checkParams.HasMember(TYPE)) {
        printf("* check type miss!\n");
        return false;
    }
    string type = checkParams[TYPE].GetString();
    const char * keyName = name;
    printf("value name =%s!\n", keyName);
    if(checkParams.HasMember(FORCE)) {
        if (checkParams[FORCE].IsString() && FORCE_FLAG == checkParams[FORCE]) {
            if(!v.HasMember(keyName)) {
                printf("O json  key  is miss!\n");
                return  false;
            }
        }
    }
    //可以为空检查类型
    if(!v.HasMember(keyName)){
        return true;
    }
    const Value & vItem = v[keyName];
    bool b = true;
    if(JOSON_TYPE_OBJECT == type || JOSON_TYPE_OBJECT_ARRAY == type || JOSON_TYPE_ARRAY == type) {
        if(!checkParams.HasMember(VALUE)) {
            printf("value miss ! [%s]\n", name);
            return false;
        }
        b =  JsonCheckObject(vItem, checkParams[VALUE] , name, type, GetLenParam(checkParams));
    }else{
        b = JsonCheckObject(vItem, checkParams , name, type, GetLenParam(checkParams) );
    }
    if (!b) {
        printf("JsonCheckObject failed!\n");
        return false;
    }
    return true;
}


bool JsonCheckObject(const Value & v,const Value& checkjson, const char* name, string type, unsigned int len=0) {
    if(!name){
        printf("name is not null!\n");
        return false;
    }
    if(!checkjson.IsObject()){
        printf("checkjson is not object!\n");
        return false;
    }
    printf("jsoncheck log:[%s]\n", name);
    logValue(v,name);
    printf("----checkjson 2 data---!\n");
    logValue(checkjson,name);

    if (v.IsArray()&&(JOSON_TYPE_OBJECT_ARRAY==type || JOSON_TYPE_ARRAY == type)) {
        printf("array size = %d! len=%d\n",v.Size(), len);
        if(v.Size()<len){
            printf("array size less than %d!\n",len);
            return false;
        }
        if (JOSON_TYPE_ARRAY == type) { //数组中是单纯数据了
            if (!checkjson.HasMember(TYPE)||!checkjson[TYPE].IsString()) {
                printf("checkjosn array  value--type  error!\n");
                return false;
            }
            const Value &array= v;
            for (unsigned int i=0;i<array.Size();i++) {
                const Value &arrayItem = array[i];
                string objectType = checkjson[TYPE].GetString();
                if(JOSON_TYPE_ARRAY==objectType){
                    if (!checkjson.HasMember(VALUE)) {
                        printf("checkjosn array-array  value  miss!\n");
                        return false;
                    }

                    if(!JsonCheckObject(arrayItem, checkjson[VALUE], "array", objectType, GetLenParam(checkjson))){
                        printf("JsonCheckObject array-array  value !\n");
                        return false;
                    }
                }else if (JOSON_TYPE_OBJECT_ARRAY == objectType){
                    if (!checkjson.HasMember(VALUE)) {
                        printf("checkjosn array-object  value  miss!\n");
                        return false;
                    }
                    if(!JsonCheckObject(arrayItem, checkjson[VALUE], "arrayobject", objectType,GetLenParam(checkjson))){
                        printf("JsonCheckObject array-arrayobject  value !\n");
                        return false;
                    }
                }
                else if(!fetchvalue(arrayItem,objectType)) { //取值了
                    return false;
                }
            }
            return true;
        } else { //AO
            const Value &array= v;
            for (unsigned int i=0;i<array.Size();i++) {
                const Value &arrayItem = array[i];
                for (Value::ConstMemberIterator iter = checkjson.MemberBegin(); iter != checkjson.MemberEnd(); ++iter){
                    printf("** AO:key=%s\n", iter->name.GetString());
                    if (!JsonCheckObjectType(arrayItem,iter->value,iter->name.GetString())) {
                        printf("object subname JsonCheckObject failed![%s]\n", iter->name.GetString());
                        return false;
                    }
                }
            }
            return true;
        }
    }else if(v.IsObject() && (JOSON_TYPE_OBJECT == type)){
        for (Value::ConstMemberIterator iter = checkjson.MemberBegin(); iter != checkjson.MemberEnd(); ++iter){
            const char* subName = iter->name.GetString();
            if (!JsonCheckObjectType(v,iter->value,subName)) {
                printf("object subname JsonCheckObject failed![%s]\n", subName);
                return false;
            }
        }
    } else {
        return  fetchvalue(v,type);
    }

    return true;
}


bool JsonCheck(Document& doc,Document& checkjson){
//    printf("----------------------------------------1\n");
//    if(doc.Empty()){
//        printf("json string is empty!!!\n");
//        return false;
//    }
//    if (checkjson.Empty()){
//        printf("checkjson string is empty!!!\n");
//        return false;
//    }
    for (Value::ConstMemberIterator m = checkjson.MemberBegin(); m != checkjson.MemberEnd(); ++m){
        printf("key [%s] is %s\n",
               m->name.GetString(), kTypeNames[m->value.GetType()]);
        if(!JsonCheckObjectType(doc, m->value, m->name.GetString())) {
            return false;
        }
    }
    return true;
}

