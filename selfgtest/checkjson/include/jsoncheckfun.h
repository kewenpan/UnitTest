//
// Created by blithepan on 2020/8/13.
//

#ifndef RAPIDJSON_JSONCHECKFUN_H
#define RAPIDJSON_JSONCHECKFUN_H
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

bool JsonCheck(rapidjson::Document& doc,rapidjson::Document& checkjson);
#endif //RAPIDJSON_JSONCHECKFUN_H
