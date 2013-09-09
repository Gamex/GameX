//
//  CSoldierBuildTask.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-13.
//
//

#include "CSoldierBuildTask.h"

CSoldierBuildTask::CSoldierBuildTask()
: m_buildTime(0.f)
{
    
}



CSoldierBuildTask::CSoldierBuildTask(const CSoldierBuildTask& obj)
{
    m_soldierName = obj.m_soldierName;
    m_buildTime = obj.m_buildTime;
    m_bothPosition = obj.m_bothPosition;
}



CSoldierBuildTask& CSoldierBuildTask::operator= (const CSoldierBuildTask& obj)
{
    m_soldierName = obj.m_soldierName;
    m_buildTime = obj.m_buildTime;
    m_bothPosition = obj.m_bothPosition;
    
    return *this;
}
