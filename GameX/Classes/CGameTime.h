//
//  CGameTime.h
//  GameX
//
//  Created by 马 俊 on 13-6-7.
//
//

#ifndef __GameX__CGameTime__
#define __GameX__CGameTime__

#include "CSingleton.h"

class CGameTime : public CSingleton<CGameTime>
{
public:
    CGameTime();
    virtual ~CGameTime();
    
    virtual void update(float dt);
    virtual float getTime();
    virtual float getDeltaTime();
protected:

private:
    float m_Time;
    float m_DelataTime;
};


#define GAME_TIME (CGameTime::getInstance())

#endif /* defined(__GameX__CGameTime__) */
