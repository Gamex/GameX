//
//  CComponentParameter.h
//  GingyBattle
//
//  Created by 马 俊 on 13-4-23.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __GingyBattle__GBComponentParameter__
#define __GingyBattle__GBComponentParameter__

#include "cocos2d.h"
#include <string>

using namespace std;
USING_NS_CC;

class CComponentParameter : public CCObject
{
    CC_SYNTHESIZE_RETAIN(CCDictionary*, parameters_, Parameters);
public:
    CREATE_FUNC(CComponentParameter);
    
    virtual bool init();
    
    virtual bool addObjectParameter(const string& name, CCObject* value);
    virtual bool addStringParameter(const string& name, const string& value);
    virtual bool addIntParameter(const string& name, int value);
    virtual bool addFloatParameter(const string& name, float value);
    virtual bool addBoolParameter(const string& name, bool value);
    
    virtual bool getObjectParameter(const string& name, CCObject** value);
    virtual bool getStringParameter(const string& name, string& value);
    virtual bool getIntParameter(const string& name, int& value);
    virtual bool getFloatParameter(const string& name, float& value);
    virtual bool getBoolParameter(const string& name, bool& value);
protected:
    CComponentParameter();
    virtual ~CComponentParameter();
    
private:

};

#endif /* defined(__GingyBattle__GBComponentParameter__) */
