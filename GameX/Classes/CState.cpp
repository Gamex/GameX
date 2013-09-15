//
//  CState.cpp
//  TheForce
//
//  Created by 马 俊 on 13-1-24.
//
//

#include "CState.h"
#include "cocos2d.h"

USING_NS_CC;

CState::CState()
: m_isStateLocked(false)
, m_currentState(STATE_NONE)
, m_nextState(STATE_NONE)
{
	
}



CState::~CState()
{
	
}



int CState::getCurrentState() const
{
	return m_currentState;
}



bool CState::changeState(int state)
{
    if (m_isStateLocked)
    {
        return false;
    }
    
	if(m_currentState != STATE_NONE)
    {
        onLeaveState(m_currentState);
    }
	
	m_currentState = state;
	
	onEnterState(m_currentState);

	return true;
}



void CState::onEnterState(int s)
{
}



void CState::onLeaveState(int s)
{

}



void CState::lockState()
{
    m_isStateLocked = true;
}



void CState::unlockState()
{
    m_isStateLocked = false;
}



void CState::clearState()
{
    unlockState();
    m_currentState = STATE_NONE;
}


