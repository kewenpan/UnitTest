//
// Created by blithepan on 2021/4/1.
//
//#ifdef RR_SMART_WASH
#include "singleton.h"

#define REDUNDANCY_VALUE  0.2
class SmartWash : public Singleton<SmartWash>{
    friend class Singleton<SmartWash>;
public:
    void Reset();
    void ConfigUserMode(int intervalUnit, bool smartFlag);
    //没定制模式使用下面3个
    bool GetFirstWashFlag(){return this->firstWash;};
    void ClearFirstWashFlag() {this->firstWash = false;};
    void SetCurMaxUnit(int curMaxUnit);
    //有定制模式带modeID
    bool SetCurMaxUnit(int modeID, int curMaxUnit);

    int GetCurMaxUnit(){ return this->curMaxUnit;};
    bool NeedWash(int IncUnit, bool finishCur=false);
    void ReportManualWash();
    int GetLastWashUnit();
    bool FinishMop();
    //设置精拖等比例
    void SetMopModeScale(float scale){ this->mopModeScale = scale;};
    float GetMopModeScale(){return this->mopModeScale;};

    void SetRedundancyValue(float value) {redundancyValue = value;};
    float GetRedundancyValue() {return  redundancyValue;};

    int GetCurUnit(){return this->curUnit;};
private:
    int lastWashUnit;
    bool smartFlag;
    int intervalUnit;
    int curMaxUnit;
    int modeID = -1;
    float redundancyValue = REDUNDANCY_VALUE;
    bool firstWash = true;
    float mopModeScale = 1.0;
    int curUnit = 0;
};
//#endif
