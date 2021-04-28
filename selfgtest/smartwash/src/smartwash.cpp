//
// Created by blithepan on 2021/4/1.
//

//#ifdef RR_SMART_WASH

#include <string>
#include "smartwash.h"
#include "logprint.h"

using namespace std;


void SmartWash::Reset() {
    this->lastWashUnit = 0;
    this->curMaxUnit = 0;
    this->firstWash = true;
    this->modeID = -1;
    this->mopModeScale = 1.0;
    this->curUnit = 0;
    LOGMSG (ZONE_INFO, "Reset modeID=%d lastWashUnit=%d, curMaxUnit=%d, intervalUnit=%d, smartFlag=%d firstWash=%d mopModeScale=%f curUnit=%d",
            this->modeID, this->lastWashUnit, this->curMaxUnit, this->intervalUnit, this->smartFlag, this->firstWash, this->mopModeScale,
            this->curUnit );
}

void SmartWash::ConfigUserMode(int intervalUnit, bool smartFlag){
    this->intervalUnit = intervalUnit;
    this->smartFlag = smartFlag;
    LOGMSG (ZONE_INFO, "ConfigUserMode intervalUnit=%d smartFlag=%d", this->intervalUnit, this->smartFlag);
}

void SmartWash::SetCurMaxUnit(int curMaxUnit){
    this->curMaxUnit = curMaxUnit*this->mopModeScale;
    LOGMSG (ZONE_INFO, "SetCurMaxUnit curMaxUnit=%d ", this->curMaxUnit);
}

bool SmartWash::NeedWash(int incUnit, bool finishCur) {
    this->curUnit += incUnit;
    LOGMSG (ZONE_INFO, "NeedWash[auto=%d] incUnit=%d,  curUnit=%d, finishCur=%d, lastWashUnit=%d, curMaxUnit=%d ,intervalUnit=%d",
        this->smartFlag, incUnit, this->curUnit, finishCur, this->lastWashUnit, this->curMaxUnit, this->intervalUnit);

    if(this->curUnit  < this->lastWashUnit) {
        return false;
    }
    bool bWash = false;
    if(!this->smartFlag || 0==this->curMaxUnit || (this->curMaxUnit < this->lastWashUnit)){  //按固定面积计算
        if((this->curUnit - this->lastWashUnit) >= this->intervalUnit){
            bWash = true;
            LOGMSG (ZONE_INFO, "0 Fixed Interval");
        }
    }else{
        int diffUnit = (this->curUnit - this->lastWashUnit);
        LOGMSG (ZONE_INFO, "diff = %d ", diffUnit);
        if(finishCur && ( diffUnit >= (this->intervalUnit * (1 - redundancyValue)))){
            bWash = true;
            LOGMSG (ZONE_INFO, "1 Area Finish > (1-0.n)");
        } else if(diffUnit >= this->intervalUnit){
            if(this->curUnit >= this->curMaxUnit){
                if(diffUnit >= (this->intervalUnit)){
                    bWash = true;
                    LOGMSG (ZONE_INFO, "2 new Area diff >= interval");
                }
            }else if ((this->curMaxUnit - this->curUnit) > (this->intervalUnit*redundancyValue)){
                bWash = true;
                LOGMSG (ZONE_INFO, "3 remainder > 0.n");
            }
        }
    }

    if(bWash){
        this->lastWashUnit = this->curUnit;
    }
    LOGMSG (ZONE_INFO, "return=%d lastWashUnit=%d", bWash, this->lastWashUnit);
    return bWash;
}

void SmartWash::ReportManualWash() {
    LOGMSG (ZONE_INFO, "ReportManualWash  curUnit=%d", this->curUnit);
    this->lastWashUnit = this->curUnit;
}

int SmartWash::GetLastWashUnit(){
    return this->lastWashUnit;
}

bool SmartWash::FinishMop() {
    bool bRet = this->curUnit > this->lastWashUnit? true:false;
    this->lastWashUnit = 0;
    this->curMaxUnit = 0;
    this->curUnit = 0;
    LOGMSG (ZONE_INFO, "FinishMop curUnit=%d, lastWashUnit=%d, ret=%d", this->curUnit, this->lastWashUnit, bRet);
    return bRet;
}

bool SmartWash::SetCurMaxUnit(int modeID, int curMaxUnit){
    this->SetCurMaxUnit(curMaxUnit);
    if(modeID != this->modeID){
        this->modeID = modeID;
        this->lastWashUnit = this->curUnit;
        return true;
    }
    return false;
}

//#endif
