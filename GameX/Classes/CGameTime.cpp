//
//  CGameTime.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-7.
//
//

#include "CGameTime.h"

IMPLEMENT_SINGLETON(CGameTime);


CGameTime::CGameTime()
: m_Time(0.f)
{
    
}



CGameTime::~CGameTime()
{
    
}



void CGameTime::update(float dt)
{
    m_DelataTime = dt;
    m_Time += dt;
}



float CGameTime::getTime()
{
    return m_Time;
}



float CGameTime::getDeltaTime()
{
    return m_DelataTime;
}
