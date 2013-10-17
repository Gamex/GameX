//
//  CState.cpp
//  TheForce
//
//  Created by 马 俊 on 13-1-24.
//
//

#include "Common.h"

#include "CState.h"


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
        m_nextState = state;
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
    if (m_nextState != STATE_NONE)
    {
        changeState(m_nextState);
        m_nextState = STATE_NONE;
    }
}



void CState::clearState()
{
    unlockState();
    m_currentState = STATE_NONE;
}



bool CState::isStateLocked() const
{
    return m_isStateLocked;
}

