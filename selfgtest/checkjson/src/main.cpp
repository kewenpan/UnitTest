//
// Created by blithepan on 2020/8/13.
//

// rapidjson/example/simpledom/simpledom.cpp`
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include <iostream>
//#include "../include/jsoncheckfun.h"
#include "jsoncheckfun.cpp"
using namespace rapidjson;

int main() {
//    // 1. 把 JSON 解析至 DOM。
//    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
//    Document d;
//    d.Parse(json);
//
//    // 2. 利用 DOM 作出修改。
//    Value& s = d["stars"];
//    s.SetInt(s.GetInt() + 1);
//
//    // 3. 把 DOM 转换（stringify）成 JSON。
//    StringBuffer buffer;
//    Writer<StringBuffer> writer(buffer);
//    d.Accept(writer);
//
//    // Output {"project":"rapidjson","stars":11}
//    std::cout << buffer.GetString() << std::endl;
//    bool  b = JsonCheck(d,d);
//    std::cout << b << std::endl;
//    return 0;
//    const char json[] = "{\"one\":{\"type\":\"S\",\"force\":\"Y\"},\"two\":{\"type\":\"N\",\"force\":\"Y\"},\"three\":{\"type\":\"A\",\"force\":\"Y\",\"value\":{\"type\":\"S\"}},\"four\":{\"type\":\"AO\",\"force\":\"Y\",\"value\":{\"source\":{\"force\":\"Y\",\"type\":\"S\"},\"x\":{\"force\":\"N\",\"type\":\"N\"}}}}";
//
//    const char json2[] ="{\"one\":\"stringvalue\",\"two\":2,\"three\":[\"aa\",\"bb\"],\"four\":[{\"source\":\"rriot\",\"x\":1},{\"source\":\"tuya\"}]}";


    const char json11[] = "{\"id\":217226,\"method\":\"clean_roller\",\"params\":{\"action\":0}}";
    const char json22[] = "{\"params\":{\"force\":\"Y\",\"type\":\"O\",\"value\":{\"action\":{\"force\":\"Y\",\"type\":\"I\"}}}}";
    Document d11,d22;
    d11.Parse(json11);
    d22.Parse(json22);
    bool  b= JsonCheck(d11,d22);
    printf("check=%d \n", b);
    const char json[] ="{\"project\":\"rapidjson\",\"stars\":10}";
    const char json2[] = "{\"project\":\"rapidjson\",\"stars\":10}";
    printf("Original JSON:\n %s\n", json);
    printf("Original JSON2:\n %s\n", json2);
    printf("----------------------------------------\n");
    Document document,document2;  // Default template parameter uses UTF8 and MemoryPoolAllocator.

#if 0
    // "normal" parsing, decode strings to new buffers. Can use other input stream via ParseStream().
    if (document.Parse(json).HasParseError())
        return 1;
#else
    // In-situ parsing, decode strings directly in the source string. Source must be string.
    char buffer[sizeof(json)];
    memcpy(buffer, json, sizeof(json));
    if (document.ParseInsitu(buffer).HasParseError())
        return 1;
    printf("----------------------------------------\n");
    char buffer2[sizeof(json2)];
    memcpy(buffer2, json2, sizeof(json2));
    if (document2.ParseInsitu(buffer2).HasParseError()){
        std::cout<<"json2 error!"<<std::endl;
        return 1;
    }

#endif
    printf("----------------------------------------\n");
//    if(document2.Empty()){
//        printf("json string is empty!!!\n");
//        return 0;
//    }
    for (auto& m : document2.GetObject()) {
        printf("Type of member %s \n",
               m.name.GetString());
//        printf("value = %s\n",m.value.GetString());
    }
    JsonCheck(document2,document);
    printf("\nParsing to document succeeded.\n");
    std::cout << "This example requires C++11 compiler" << std::endl;
    return 1;
}
