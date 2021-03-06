//
//  CPlayerInfo.h
//  GameX
//
//  Created by 马 俊 on 13-12-10.
//
//

#ifndef __GameX__CPlayerInfo__
#define __GameX__CPlayerInfo__

#include "Common.h"
#include "CSingleton.h"

class CPlayerInfo
: public CSingleton<CPlayerInfo>
{
    CC_SYNTHESIZE(int, m_uid, UID);
    CC_SYNTHESIZE(int, m_pid, PID);
    CC_SYNTHESIZE(int, m_level, Level);
    CC_SYNTHESIZE(int, m_gas, Gas);
    CC_SYNTHESIZE(int, m_mineral, Mineral);
    CC_SYNTHESIZE(int, m_money, Money);
    CC_SYNTHESIZE(string, m_nickname, NickName);
public:
    CPlayerInfo();
    ~CPlayerInfo();
};


#define PLAYER_INFO     (CPlayerInfo::getInstance())

#endif /* defined(__GameX__CPlayerInfo__) */
