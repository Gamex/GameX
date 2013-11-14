//
//  CSoldierBuildTask.h
//  GameX
//
//  Created by 马 俊 on 13-6-13.
//
//

#ifndef __GameX__CSoldierBuildTask__
#define __GameX__CSoldierBuildTask__

#include "Common.h"

class CSoldierBuildTask
{
public:
    CSoldierBuildTask();
    CSoldierBuildTask(const CSoldierBuildTask& obj);
    CSoldierBuildTask& operator= (const CSoldierBuildTask& obj);
    
    std::string m_soldierName;
    float m_buildTime;
    Point m_bothPosition;
protected:
private:
};

#endif /* defined(__GameX__CSoldierBuildTask__) */
