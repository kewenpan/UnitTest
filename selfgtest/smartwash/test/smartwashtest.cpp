//
// Created by blithepan on 2021/4/2.
//

#include <gtest/gtest.h>
#include "../include/smartwash.h"
//// 1 test {}
TEST(initTest, test1_Reset)
{
    SmartWash::GetInstance().ConfigUserMode(80,true);
    SmartWash::GetInstance().Reset();
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==0)<<"Reset error!";
}

//reset
TEST(autowash, reset)
{
    SmartWash::GetInstance().ConfigUserMode(60,true);
    SmartWash::GetInstance().Reset();
    bool b1 = SmartWash::GetInstance().GetFirstWashFlag();
    SmartWash::GetInstance().ClearFirstWashFlag();
    bool b2 = SmartWash::GetInstance().GetFirstWashFlag();
    bool b3 = SmartWash::GetInstance().SetCurMaxUnit(1,10);
    ASSERT_TRUE(b1 && !b2 && b3) << "第一次回洗/重置检查/再设置模式";
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(10, true))<<"notwash area1 error1!";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==0)<<"第一个留下了!";
    ASSERT_TRUE(SmartWash::GetInstance().GetCurUnit()==10)<<"当前总拖地到10!";
    SmartWash::GetInstance().SetMopModeScale(1.3);
    ASSERT_TRUE(abs(SmartWash::GetInstance().GetMopModeScale()-1.3)<0.001)<<"拖地系数";

    SmartWash::GetInstance().Reset();
    b1 = SmartWash::GetInstance().GetFirstWashFlag();
    int lastUnit = SmartWash::GetInstance().GetLastWashUnit();
    int curMaxuUnit = SmartWash::GetInstance().GetCurMaxUnit();
    ASSERT_TRUE(b1 && lastUnit==0 && curMaxuUnit==0) << "全局重置检查";
    ASSERT_TRUE(abs(SmartWash::GetInstance().GetMopModeScale()-1.0)<0.001)<<"拖地系数";
    ASSERT_TRUE(SmartWash::GetInstance().GetCurUnit()==0)<<"当前总拖地恢复到0!";
}

TEST(initTest, test2_notwash)
{
    SmartWash::GetInstance().ConfigUserMode(60,true);
    SmartWash::GetInstance().Reset();
    SmartWash::GetInstance().SetCurMaxUnit(72);
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(60))<<"notwash error1!";
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(11))<<"notwash error2!";
}

TEST(initTest, test2_wash)
{
    SmartWash::GetInstance().ConfigUserMode(60,true);
    SmartWash::GetInstance().Reset();
    SmartWash::GetInstance().SetCurMaxUnit(73);
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(60))<<"wash 剩余超过0.N!";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==60) << "当前清洗时的值";
}

//分区结束大于 0.n
TEST(FinishArea, test7_greaterthanN2)
{
    SmartWash::GetInstance().ConfigUserMode(60,true);
    SmartWash::GetInstance().Reset();
    SmartWash::GetInstance().SetCurMaxUnit(48);
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(48))<<"wash error1!";
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(0, true))<<"结束 清洗";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==48) << "当前清洗时的值";
}

//第一次不智能
TEST(notautowash, test3)
{
    SmartWash::GetInstance().ConfigUserMode(60,false);
    SmartWash::GetInstance().Reset();
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(50))<<"notwash error1!";
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(10))<<" 非智能 达到回洗 error2!";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==60)<<"最新回洗值60 error3!";
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(40))<<"notwash error4!";
    SmartWash::GetInstance().ReportManualWash();
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==100)<<"手动回洗值100 error5!";
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(50))<<"手动回洗值没超过 error6!";
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(10))<<"手动回洗超过超过 error7!";
    SmartWash::GetInstance().ConfigUserMode(30,false);
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(30))<<"动态调整清洗面积后 error8!";
}

//智能回洗未设置每个区最大面积 退化为不智能
TEST(notsmartauto, notmaxarea)
{
    SmartWash::GetInstance().ConfigUserMode(60,true);
    SmartWash::GetInstance().Reset();
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(50))<<"notwash error1!";
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(10))<<"notwash error2!";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==60)<<"最新回洗值60 error3!";
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(40))<<"notwash error4!";
    SmartWash::GetInstance().ReportManualWash();
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==100)<<"手动回洗值10 error5!";
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(50))<<"手动回洗值没超过 error6!";
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(10))<<"手动回洗超过超过 error7!";
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(10))<<" 160 -> 170 不回洗!";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==160)<<" 160 回洗过!";
    SmartWash::GetInstance().ConfigUserMode(30,true);
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(20))<<"增加20  error8!";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==190)<<"手动回洗值10 error5!";
}

//正常流程 > （1-0.n） 分区内回洗
TEST(autowash, finishareawash)
{
    SmartWash::GetInstance().ConfigUserMode(60,true);
    SmartWash::GetInstance().Reset();
    SmartWash::GetInstance().SetCurMaxUnit(108);
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(60))<<"超过N+1.n error1!";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==60)<<"当前回洗值72 error2!";
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(48, false))<<"超过0.n 未结束，不回洗 error3!";
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(0, true))<<"超过0.n 结束，回洗 error4!!";
}

//正常流程 < N/2 分区结束清洗 保留到下个分区
TEST(autowash, nextarea)
{
    SmartWash::GetInstance().ConfigUserMode(60,true);
    SmartWash::GetInstance().Reset();
    SmartWash::GetInstance().SetCurMaxUnit(5);
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(5, true))<<"notwash area1 error1!";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==0)<<"第一个留下了!";
    SmartWash::GetInstance().SetCurMaxUnit(5);
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(5,true))<<"notwash area2 error1!";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==0)<<"前两个预留下来!";

    SmartWash::GetInstance().SetCurMaxUnit(38);
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(38,false))<<"wash not finish area3 error1!";
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(0,true))<<"wash finish area3 error1!";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==48)<<"当前回洗值12 error2!";
}

//调整当前区域大小
TEST(autowash, updateCuraMaxUnit)
{
    SmartWash::GetInstance().ConfigUserMode(60,true);
    SmartWash::GetInstance().Reset();
    SmartWash::GetInstance().SetCurMaxUnit(72);
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(60, false))<<"剩余小于 0.2*N";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==0)<<"第一个留下了!";

    SmartWash::GetInstance().SetCurMaxUnit(73);
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(0, false))<<"剩余大于 0.2*N";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==60)<<" 清洗了!";
}

//调整当前区域大小
TEST(autowash, updateCuraMaxUnit_illegal)
{
    SmartWash::GetInstance().ConfigUserMode(60,true);
    SmartWash::GetInstance().Reset();
    SmartWash::GetInstance().SetCurMaxUnit(72);
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(60, false))<<"剩余小于 0.2*N";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==0)<<"第一个留下了!";

    //测试一下调小
    SmartWash::GetInstance().SetCurMaxUnit(71);
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(0, false))<<"剩余小于 0.2*N";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==0)<<" 不清洗了!";

    //测试一下调小
    SmartWash::GetInstance().SetCurMaxUnit(60);
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(0, false))<<"等于最大值了";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==60)<<" 不清洗了!";

    //测试一下调小 非法
    SmartWash::GetInstance().SetCurMaxUnit(50);
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(0, false))<<"等于最大值了";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==60)<<" 不清洗了!";
}

//切换模式
TEST(autowash, updateMode)
{
    SmartWash::GetInstance().ConfigUserMode(60,true);
    SmartWash::GetInstance().Reset();
    bool b1 = SmartWash::GetInstance().GetFirstWashFlag();
    SmartWash::GetInstance().ClearFirstWashFlag();
    bool b2 = SmartWash::GetInstance().GetFirstWashFlag();
    bool b3 = SmartWash::GetInstance().SetCurMaxUnit(1,10);
    ASSERT_TRUE(b1 && !b2 && b3) << "第一次回洗/重置检查/再设置模式";
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(10, true))<<"notwash area1 error1!";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==0)<<"第一个留下了!";

    bool b = SmartWash::GetInstance().SetCurMaxUnit(2,30);
    ASSERT_TRUE(b) << "切换模式";
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==10)<<"还没有!";
}

//手动清洗
TEST(ManualReport, test)
{
    SmartWash::GetInstance().ConfigUserMode(60,true);
    SmartWash::GetInstance().Reset();
    SmartWash::GetInstance().SetCurMaxUnit(100);
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(50))<<"notwash error1!";
    SmartWash::GetInstance().ReportManualWash();
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==50)<<" 当前回洗值 50 error1!";
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(0))<<"notwash error1!";
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(50))<<"notwash error2!";
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(50, true))<<"wash error3!";
    SmartWash::GetInstance().ReportManualWash();
    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==150)<<" 当前回洗值 150 error4!";
}
//
//拖地精度
TEST(mopModeScale, test)
{
    SmartWash::GetInstance().ConfigUserMode(60,true);
    SmartWash::GetInstance().Reset();
    SmartWash::GetInstance().SetMopModeScale(1.2);
    SmartWash::GetInstance().SetCurMaxUnit(100);
    ASSERT_TRUE(abs(SmartWash::GetInstance().GetMopModeScale()-1.2)<0.001)<<" 拖地比例1.2";
    ASSERT_TRUE(abs(SmartWash::GetInstance().GetCurMaxUnit()-120)<0.001)<<" 当前 120";

    SmartWash::GetInstance().SetMopModeScale(1.6);
    SmartWash::GetInstance().SetCurMaxUnit(100);
    ASSERT_TRUE(abs(SmartWash::GetInstance().GetMopModeScale()-1.6)<0.001)<<" 拖地比例1.2";
    ASSERT_TRUE(abs(SmartWash::GetInstance().GetCurMaxUnit()-160)<0.001)<<" 当前 120";
}

////一个分区多次结束+完成清洗  不支持
//TEST(repeatfinish, test)
//{
//    SmartWash::GetInstance().ConfigUserMode(60,true);
//    SmartWash::GetInstance().Reset();
//    SmartWash::GetInstance().SetCurMaxUnit(70);
//    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(70,true))<<"wash error1!";
//    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(70,true))<<"repeat wash error2!";
//    ASSERT_FALSE(SmartWash::GetInstance().FinishMop(70))<<"finish wash error3!";
//    ASSERT_TRUE(SmartWash::GetInstance().GetLastWashUnit()==0)<<" 当前回洗值 0 error4!";
//}

//修改模式
TEST(updatemode, test)
{
    SmartWash::GetInstance().ConfigUserMode(60,true);
    SmartWash::GetInstance().Reset();
    bool bWash = SmartWash::GetInstance().SetCurMaxUnit(1,100);
    ASSERT_TRUE(bWash)<<"wash error1!";
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(95))<<"notwash error1!";
    SmartWash::GetInstance().ReportManualWash();
    bWash = SmartWash::GetInstance().SetCurMaxUnit(1,100);
    ASSERT_FALSE(bWash)<<"同一个模式下继续拖地 error2!";
    bWash = SmartWash::GetInstance().SetCurMaxUnit(2,100);
    ASSERT_TRUE(bWash)<<"不同一个模式回洗 error3!";
}

//不同 剩余冗余参数
TEST(RedundancyParam, test)
{
    SmartWash::GetInstance().ConfigUserMode(60,true);
    SmartWash::GetInstance().Reset();
    SmartWash::GetInstance().SetRedundancyValue(0.3);
    ASSERT_TRUE(abs(SmartWash::GetInstance().GetRedundancyValue()-0.3)<0.01) << "冗余参数 错误！";
    SmartWash::GetInstance().SetCurMaxUnit(78);
    ASSERT_FALSE(SmartWash::GetInstance().NeedWash(60))<<"notwash error1!";
    SmartWash::GetInstance().SetCurMaxUnit(79);
    ASSERT_TRUE(SmartWash::GetInstance().NeedWash(60))<<"notwash error2!";
}
