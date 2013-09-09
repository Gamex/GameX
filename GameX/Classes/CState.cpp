//
//  CState.cpp
//  TheForce
//
//  Created by 马 俊 on 13-1-24.
//
//

#include "CState.h"
#include "cocos2d.h"
#include "CComponent.h"
#include "CComponentParameter.h"

USING_NS_CC;

CState::CState() :
isStateLocked_(false)
{
	
}



CState::~CState()
{
	
}



string CState::getCurrentState() const
{
	return currentState_;
}



bool CState::changeState(const string& state, CComponentParameter* parameter, bool force)
{
    if (isStateLocked_)
    {
        return false;
    }
    if (!force)
    {
        if (currentState_.compare(state) == 0)
        {
            return false;
        }
    }
    
	if(!currentState_.empty())
    {
        onLeaveState(currentState_);
    }
	
	currentState_ = state;
	
	onEnterState(currentState_);
    
    if (parameter)
    {
        setComponentParameter(parameter);
    }
	return true;
}



void CState::onEnterState(const string& s)
{
    MSC_IT it = components_.find(currentState_);
    if (it != components_.end())
    {
        SC& sc = (*it).second;
        SC_IT sc_it = sc.begin();
        for (; sc_it != sc.end(); ++sc_it)
        {
            (*sc_it)->onEnterComponent();
        }
    }
}



void CState::onLeaveState(const string& s)
{
    MSC_IT it = components_.find(currentState_);
    if (it != components_.end())
    {
        SC& sc = (*it).second;
        SC_IT sc_it = sc.begin();
        for (; sc_it != sc.end(); ++sc_it)
        {
            (*sc_it)->onLeaveComponent();
        }
    }
}



void CState::lockState()
{
    isStateLocked_ = true;
}



void CState::unlockState()
{
    isStateLocked_ = false;
}



void CState::clearState()
{
    unlockState();
    currentState_.clear();
}



void CState::addComponentForState(const string& state, CComponent* component)
{
    SC& sc = components_[state];
    if (sc.find(component) == sc.end())
    {
        CC_SAFE_RETAIN(component);
        components_[state].insert(component);
    }
    
}



void CState::removeState(const string& state)
{
    MSC_IT it = components_.find(state);
    if (it != components_.end())
    {
        SC& sc = (*it).second;
        SC_IT sc_it = sc.begin();
        for (; sc_it != sc.end(); ++sc_it)
        {
            CC_SAFE_RELEASE(*sc_it);
        }
        components_.erase(it);
    }
}



void CState::removeComponentFromState(const string& state, CComponent* component)
{
    MSC_IT it = components_.find(state);
    if (it != components_.end())
    {
        SC_IT sc_it = (*it).second.find(component);
        if (sc_it != (*it).second.end())
        {
            CC_SAFE_RELEASE(*sc_it);
            (*it).second.erase(sc_it);
        }
    }
}



void CState::updateComponents(float dt)
{
    MSC_IT it = components_.find(currentState_);
    if (it != components_.end())
    {
        SC& sc = (*it).second;
        SC_IT sc_it = sc.begin();
        for (; sc_it != sc.end(); ++sc_it)
        {
            (*sc_it)->update(dt);
        }
    }
}



void CState::setComponentParameter(CComponentParameter* pamaremter)
{
    MSC_IT it = components_.find(currentState_);
    if (it != components_.end())
    {
        SC& sc = (*it).second;
        SC_IT sc_it = sc.begin();
        for (; sc_it != sc.end(); ++sc_it)
        {
            (*sc_it)->setParameter(pamaremter);
        }
    }
}
