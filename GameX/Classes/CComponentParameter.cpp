//
//  CComponentParameter.cpp
//  GingyBattle
//
//  Created by 马 俊 on 13-4-23.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CComponentParameter.h"
#include "Common.h"

CComponentParameter::CComponentParameter()
: parameters_(NULL)
{
    
}



CComponentParameter::~CComponentParameter()
{
    setParameters(NULL);
}



bool CComponentParameter::init()
{
    do
    {
        setParameters(CCDictionary::create());
        BREAK_IF(!getParameters());
        return true;
    } while (false);
    return false;
}



bool CComponentParameter::addObjectParameter(const string& name, CCObject* value)
{
    parameters_->setObject(value, name);
    return true;
}



bool CComponentParameter::addStringParameter(const string& name, const string& value)
{
    CCString* str = CCString::create(value);
    parameters_->setObject(str, name);
    return true;
}



bool CComponentParameter::addIntParameter(const string& name, int value)
{
    parameters_->setObject(CCInteger::create(value), name);
    return true;
}



bool CComponentParameter::addFloatParameter(const string& name, float value)
{
    parameters_->setObject(CCFloat::create(value), name);
    return true;
}



bool CComponentParameter::addBoolParameter(const string& name, bool value)
{
    parameters_->setObject(CCBool::create(value), name);
    return true;
}



bool CComponentParameter::getObjectParameter(const string& name, CCObject** value)
{
    *value = parameters_->objectForKey(name);
    
    if (*value)
    {
        return true;
    }
    return false;
}



bool CComponentParameter::getStringParameter(const string& name, string& value)
{
    CCString* str = dynamic_cast<CCString*>(parameters_->objectForKey(name));
    if (!str)
    {
        return false;
    }
    value = str->getCString();
    
    return true;
}



bool CComponentParameter::getIntParameter(const string& name, int& value)
{
    CCInteger* str = dynamic_cast<CCInteger*>(parameters_->objectForKey(name));
    if (!str)
    {
        return false;
    }
    value = str->getValue();
    
    return true;
}



bool CComponentParameter::getFloatParameter(const string& name, float& value)
{
    CCFloat* str = dynamic_cast<CCFloat*>(parameters_->objectForKey(name));
    if (!str)
    {
        return false;
    }
    value = str->getValue();
    
    return true;
}



bool CComponentParameter::getBoolParameter(const string& name, bool& value)
{
    CCBool* str = dynamic_cast<CCBool*>(parameters_->objectForKey(name));
    if (!str)
    {
        return false;
    }
    value = str->getValue();
    
    return true;
}



