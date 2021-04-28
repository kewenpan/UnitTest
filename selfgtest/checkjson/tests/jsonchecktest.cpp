//
// Created by blithepan on 2020/8/13.
//

#include <gtest/gtest.h>
#include "../../src/jsoncheckfun.cpp"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

using namespace rapidjson;
//// 1 test {}
//TEST(jsoncheckfun, test1_null)
//{
//    const char json1[] ="{\"project\":\"rapidjson\",\"stars\":10}";
//    const char json2[] = "{}";
//    Document d1,d2;
//    d1.Parse(json1);
//    d2.Parse(json2);
//    ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} check erro!";
//}
//
//TEST(jsoncheckfun, test1_null_ao)
//{
//    const char json1[] ="{\"project\":[1,2],\"stars\":10}";
//    const char json2[] = "{\"project\":{\"force\":\"Y\",\"type\":\"AO\",\"value\":{}}}";
//    Document d1,d2;
//    d1.Parse(json1);
//    d2.Parse(json2);
//    ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} check erro!";
//}
//
//TEST(jsoncheckfun, test1_null_ao2)
//{
//const char json1[] ="{\"project\":[{\"1\":1},{\"1\":2}],\"stars\":10}";
//const char json2[] = "{\"project\":{\"force\":\"Y\",\"type\":\"AO\",\"value\":{}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} check erro!";
//}
//
////2 test type
//TEST(jsoncheckfun, test1_miss_type)
//{
//    const char json1[] ="{\"project\":\"rapidjson\",\"stars\":10}";
//    const char json2[] = "{\"project\":{\"force\":\"Y\"}}";
//    Document d1,d2;
//    d1.Parse(json1);
//    d2.Parse(json2);
//    ASSERT_TRUE(JsonCheck(d1,d2)==false)<<" check json {} check miss type!";
//}
//
//TEST(jsoncheckfun, test1_miss_type_N)
//{
//const char json1[] ="{\"project\":\"rapidjson\",\"stars\":10}";
//const char json2[] = "{\"project\":{\"force\":\"Y\"}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==false)<<" check json {} check miss type!";
//}
//
//TEST(jsoncheckfun, test1_type_ao)
//{
//const char json1[] ="{\"project\":[{\"1\":1},{\"1\":2}],\"stars\":10}";
//const char json2[] = "{\"project\":{\"type\":\"AO\",\"force\":\"Y\",\"value\":{\"1\":{\"force\":\"Y\",\"type\":\"N\"}}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check oa type!";
//}
//
//TEST(jsoncheckfun, test1_type_ao_misstype)
//{
//const char json1[] ="{\"project\":[{\"1\":1},{\"1\":2}],\"stars\":10}";
//const char json2[] = "{\"project\":{\"type\":\"AO\",\"force\":\"Y\",\"value\":{\"1\":{\"force\":\"Y\"}}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==false)<<" check oa type miss!";
//}
//
//TEST(jsoncheckfun, test1_type_all)
//{
//const char json1[] = "{\"project\":\"rapidjson\",\"stars\":10,\"one\":[],\"two\":[11,12]}";
//const char json2[] = "{\"project\":{\"type\":\"S\",\"force\":\"Y\"},\"stars\":{\"type\":\"N\",\"force\":\"Y\"},\"one\":{\"type\":\"AO\",\"force\":\"Y\",\"value\":{}},\"two\":{\"type\":\"A\",\"force\":\"Y\",\"value\":{\"type\":\"N\"}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check oa type all!";
//}
//
//TEST(jsoncheckfun, test1_check_type_erro)
//{
//const char json1[] ="{\"project\":\"rapidjson\",\"stars\":10}";
//const char json2[] = "{\"stars\":{\"force\":\"Y\",\"type\":\"S\"}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==false)<<" check json {} check type error!";
//}
//
//TEST(jsoncheckfun, test1_check_type_N)
//{
//const char json1[] ="{\"project\":\"rapidjson\",\"stars\":10}";
//const char json2[] = "{\"stars\":{\"force\":\"Y\",\"type\":\"N\"}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} check type N!";
//}
//
//TEST(jsoncheckfun, test1_check_type_I_String)
//{
//const char json1[] ="{\"project\":\"rapidjson\",\"stars\":\"10\"}";
//const char json2[] = "{\"stars\":{\"force\":\"Y\",\"type\":\"N\"}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} check type string to N!";
//}
//
//TEST(jsoncheckfun, test1_check_type_I_String_erro)
//{
//const char json1[] ="{\"project\":\"rapidjson\",\"stars\":\"10X\"}";
//const char json2[] = "{\"stars\":{\"force\":\"Y\",\"type\":\"N\"}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==false)<<" check json {} check type string to N error!";
//}
//
////3 test force
//TEST(jsoncheckfun, test1_miss_force)
//{
//    const char json1[] ="{\"project\":\"rapidjson\",\"stars\":10}";
//    const char json2[] = "{\"project\":{\"type\":\"S\"}}";
//    Document d1,d2;
//    d1.Parse(json1);
//    d2.Parse(json2);
//    ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} check miss force!";
//}
//
//TEST(jsoncheckfun, test1_check_ok)
//{
//    const char json1[] ="{\"project\":\"rapidjson\",\"stars\":10}";
//    const char json2[] = "{\"project\":{\"force\":\"Y\",\"type\":\"S\"}}";
//    Document d1,d2;
//    d1.Parse(json1);
//    d2.Parse(json2);
//    ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} check OK!";
//}
////test array
//
//TEST(jsoncheckfun, test1_array_ok)
//{
//const char json1[] = "{\"one\":[{\"abc\":1},{\"abc\":2}],\"two\":[11,12]}";
//const char json2[] = "{\"one\":{\"type\":\"AO\",\"force\":\"Y\",\"value\":{\"abc\":{\"force\":\"Y\",\"type\":\"N\"}}},\"two\":{\"type\":\"A\",\"force\":\"Y\",\"value\":{\"type\":\"N\"}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} test1_array_ok";
//}
//
//TEST(jsoncheckfun, test1_array_a_errodate)
//{
//const char json1[] = "{\"one\":[{\"abc\":1},{\"abcxxxx\":2}],\"two\":[11,12,13]}";
//const char json2[] = "{\"one\":{\"type\":\"AO\",\"force\":\"Y\",\"value\":{\"abc\":{\"force\":\"Y\",\"type\":\"N\"}}},\"two\":{\"type\":\"A\",\"force\":\"Y\",\"value\":{\"type\":\"N\"}}}";
//
////const char json1[] = "{\"one\":[{\"abc\":1},{\"abc\":2}],\"two\":[11,12,13x]}";
////const char json2[] = "{\"two\":{\"type\":\"A\",\"force\":\"Y\",\"value\":{\"type\":\"N\"}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==false)<<" check json {} test1_array_a_errodate";
//}
//
//TEST(jsoncheckfun, test1_array_a_errodatexxx)
//{
//const char json1[] = "{\"one\":[{\"abc\":1},{\"abcxxxx\":2}],\"two\":[11,12,13]}";
//const char json2[] = "{\"two\":{\"type\":\"A\",\"force\":\"Y\",\"value\":{\"type\":\"N\"}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} test1_array_a_errodate";
//}
//
//TEST(jsoncheckfun, test1_array_ao_errodate1)
//{
//const char json1[] = "{\"one\":[{\"abc\":1},{\"abcxxxx\":2}],\"two\":[11,12,13]}";
//const char json2[] = "{\"one\":{\"type\":\"AO\",\"force\":\"Y\",\"value\":{\"abc\":{\"force\":\"Y\",\"type\":\"N\"}}},\"two\":{\"type\":\"A\",\"force\":\"Y\",\"value\":{\"type\":\"N\"}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==false)<<" check json {} test1_array_a_errodate1";
//}
//
//TEST(jsoncheckfun, test1_array_ao_errodate2)
//{
//const char json1[] = "{\"one\":[{\"abc\":1},{\"abc\":2}],\"two\":[11,12,13]}";
//const char json2[] = "{\"two\":{\"type\":\"A\",\"force\":\"Y\",\"value\":{\"type\":\"N\"}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} test1_array_a_errodate2";
//}
//
//TEST(jsoncheckfun, clean_roller){
//    const char json1[] = "{\"id\":217226,\"method\":\"clean_roller\",\"params\":{\"action\":0}}";
//    const char json2[] = "{\"params\":{\"force\":\"Y\",\"type\":\"O\",\"value\":{\"action\":{\"force\":\"Y\",\"type\":\"N\"}}}}";
//    Document d1,d2;
//    d1.Parse(json1);
//    d2.Parse(json2);
//    ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} clean_roller ";
//}
//
//TEST(jsoncheckfun, test1_complex)
//{
//const char json1[] = "{\"one\":\"stringvalue\",\"two\":2,\"three\":[\"aa\",\"bb\"],\"four\":[{\"source\":\"rriot\",\"x\":1},{\"source\":\"tuya\",\"x\":2}]}";
//const char json2[] = "{\"one\":{\"type\":\"S\",\"force\":\"Y\"},\"two\":{\"type\":\"N\",\"force\":\"Y\"},\"three\":{\"type\":\"A\",\"force\":\"Y\",\"value\":{\"type\":\"S\"}},\"four\":{\"type\":\"AO\",\"force\":\"Y\",\"value\":{\"source\":{\"force\":\"Y\",\"type\":\"S\"},\"x\":{\"force\":\"N\",\"type\":\"N\"}}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} test1_complex";
//}
//
//
//TEST(jsoncheckfun, test1_N_a)
//{
//    const char json1[] ="{\"project\":[1,2],\"stars\":10}";
//    const char json2[] = "{\"project\":{\"force\":\"N\",\"type\":\"A\",\"value\":{\"type\":\"S\"}}}";
//    Document d1,d2;
//    d1.Parse(json1);
//    d2.Parse(json2);
//    ASSERT_TRUE(JsonCheck(d1,d2)==false)<<" check json {} check erro!";
//}
//
//TEST(jsoncheckfun, test1_type_int64_double)
//{
//const char json1[] ="{\"project\":[1,2],\"stars\":10.99}";
//const char json2[] = "{\"project\":{\"force\":\"Y\",\"type\":\"A\",\"value\":{\"type\":\"N64\"}},\"stars\":{\"force\":\"N\",\"type\":\"D\"}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} check erro!";
//}
//
//TEST(jsoncheckfun, test1_Array_2)
//{
//const char json1[] ="{\"project\":[[1],[2,3]],\"stars\":10}";
//const char json2[] = "{\"project\":{\"force\":\"Y\",\"type\":\"A\",\"value\":{\"type\":\"A\",\"value\":{\"type\":\"N\"}}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} check erro!";
//}
//
//TEST(jsoncheckfun, test1_Array_2_false1)
//{
//const char json1[] ="{\"project\":[[1],[2,3]],\"stars\":10}";
//const char json2[] = "{\"project\":{\"force\":\"Y\",\"type\":\"A\",\"value\":{\"type\":\"A\"}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==false)<<" check json {} check erro!";
//}
//
//
//TEST(jsoncheckfun, test1_Array_Object)
//{
//const char json1[] ="{\"project\":[[{\"aaa\":111,\"bb\":111}],[{\"bb\":222}]],\"stars\":10.99}";
//const char json2[] = "{\"project\":{\"force\":\"Y\",\"type\":\"A\",\"value\":{\"type\":\"AO\",\"value\":{\"bb\":{\"force\":\"Y\",\"type\":\"N\"}}}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} check erro!";
//}
//
//TEST(jsoncheckfun, test1_Array_Object2)
//{
//const char json1[] = "{\"project\":[[{\"aaa\":111,\"bb\":111},{\"bb\":111}],[{\"bb\":222}]],\"stars\":10.99}";
//const char json2[] = "{\"project\":{\"force\":\"Y\",\"type\":\"A\",\"value\":{\"type\":\"AO\",\"value\":{\"bb\":{\"force\":\"Y\",\"type\":\"N\"}}}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} check erro!";
//}
//
//TEST(jsoncheckfun, test1_Array_Object_false)
//{
//const char json1[] ="{\"project\":[[{\"aaa\":111,\"bb\":111}],[{\"bb\":222}]],\"stars\":10.99}";
//const char json2[] = "{\"project\":{\"force\":\"Y\",\"type\":\"A\",\"value\":{\"type\":\"AO\",\"value\":{\"aaa\":{\"force\":\"Y\",\"type\":\"N\"}}}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==false)<<" check json {} check erro!";
//}
//
//
////test array len
//
//TEST(jsoncheckfun, test1_array_len_ok)
//{
//const char json1[] = "{\"one\":[{\"abc\":1},{\"abc\":2}],\"two\":[11,12,33]}";
//const char json2[] = "{\"one\":{\"type\":\"AO\",\"force\":\"Y\",\"len\":2,\"value\":{\"abc\":{\"force\":\"Y\",\"type\":\"N\"}}},\"two\":{\"type\":\"A\",\"len\":3,\"force\":\"Y\",\"value\":{\"type\":\"N\"}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} test1_array_len_ok";
//}
//TEST(jsoncheckfun, test1_array_len_failed)
//{
//const char json1[] = "{\"one\":[{\"abc\":1},{\"abc\":2}],\"two\":[11,12]}";
//const char json2[] = "{\"one\":{\"type\":\"AO\",\"force\":\"Y\",\"len\":3,\"value\":{\"abc\":{\"force\":\"Y\",\"type\":\"N\"}}},\"two\":{\"type\":\"A\",\"force\":\"Y\",\"value\":{\"type\":\"N\"}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==false)<<" check json {} test1_array_len_ok";
//}
//
////real test
//TEST(jsoncheckfun, test1_array_real_test)
//{
//const char json1[] = "{\"params\":{\"map_index\":1,\"zone_data\":[[1,2,3,4],[5,6,7,8]]}}";
//const char json2[] = "{\"params\":{\"force\":\"Y\",\"type\":\"O\",\"value\":{\"map_index\":{\"force\":\"N\",\"type\":\"N\"},\"zone_data\":{\"force\":\"Y\",\"type\":\"A\",\"value\":{\"type\":\"A\",\"len\":4,\"value\":{\"type\":\"N\"}}}}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} test1_array_real_test";
//}
//
//TEST(jsoncheckfun, test1_array_real_test_miss_mapindex)
//{
//const char json1[] = "{\"params\":{\"zone_data\":[[1,2,3,4],[5,6,7,8]]}}";
//const char json2[] = "{\"params\":{\"force\":\"Y\",\"type\":\"O\",\"value\":{\"map_index\":{\"force\":\"N\",\"type\":\"N\"},\"zone_data\":{\"force\":\"Y\",\"type\":\"A\",\"value\":{\"type\":\"A\",\"len\":4,\"value\":{\"type\":\"N\"}}}}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} test1_array_real_test_miss_mapindex";
//}
//
//TEST(jsoncheckfun, test1_array_real_test_false)
//{
//const char json1[] = "{\"params\":{\"map_index\":1,\"zone_data\":[[1,2,3],[5,6,7,8]]}}";
//const char json2[] = "{\"params\":{\"force\":\"Y\",\"type\":\"O\",\"value\":{\"map_index\":{\"force\":\"N\",\"type\":\"N\"},\"zone_data\":{\"force\":\"Y\",\"type\":\"A\",\"value\":{\"type\":\"A\",\"len\":4,\"value\":{\"type\":\"N\"}}}}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==false)<<" check json {} test1_array_real_test_len_less";
//}
//
//TEST(jsoncheckfun, test1_array_real_test_type_error)
//{
//const char json1[] = "{\"params\":{\"zone_data\":[[\"d\",2,3,4],[5,6,7,8]]}}";
//const char json2[] = "{\"params\":{\"force\":\"Y\",\"type\":\"O\",\"value\":{\"map_index\":{\"force\":\"N\",\"type\":\"N\"},\"zone_data\":{\"force\":\"Y\",\"type\":\"A\",\"value\":{\"type\":\"A\",\"len\":4,\"value\":{\"type\":\"N\"}}}}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==false)<<" check json {} test1_array_real_test_type_error";
//}
//
//TEST(jsoncheckfun, test1_array_real_test_type_error2)
//{
//const char json1[] = "{\"params\":{\"zone_data\":[[\"11\",2,3,4],[5,6,7,8]]}}";
//const char json2[] = "{\"params\":{\"force\":\"Y\",\"type\":\"O\",\"value\":{\"map_index\":{\"force\":\"N\",\"type\":\"N\"},\"zone_data\":{\"force\":\"Y\",\"type\":\"A\",\"value\":{\"type\":\"A\",\"len\":4,\"value\":{\"type\":\"N\"}}}}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} test1_array_real_test_type_error";
//}


//TEST(jsoncheckfun, test1_array_real_test_appproxy)
//{
//const char json1[] = "{\"id\":131097,\"method\":\"clean_roller\",\"params\":{\"action\":0}}";
//const char json2[] = "{\"params\":{\"force\":\"Y\",\"type\":\"O\",\"value\":{\"action\":{\"force\":\"Y\",\"type\":\"N\"}}}}";
//Document d1,d2;
//d1.Parse(json1);
//d2.Parse(json2);
//ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} test1_array_real_test_type_error";
//}

TEST(jsoncheckfun, test1_setfanworktimeout)
{
const char json1[] = "{\"id\":367303,\"method\":\"set_fan_motor_work_timeout\",\"params\":{\"timeout\":\"360\"}}";
const char json2[] = "{\"params\":{\"force\":\"Y\",\"type\":\"O\",\"value\":{\"timeout\":{\"force\":\"Y\",\"type\":\"N\"}}}}";
Document d1,d2;
d1.Parse(json1);
d2.Parse(json2);
ASSERT_TRUE(JsonCheck(d1,d2)==true)<<" check json {} test1_array_real_test_type_error";
}