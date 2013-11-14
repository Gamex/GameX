//
//  CHPBar.h
//  TheForce
//
//  Created by Ray M on 13-2-19.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__CHPBar__
#define __TheForce__CHPBar__

#include "CSpriteObject.h"
#include "CScale9SpriteObject.h"


class CHPBar : public CSpriteObject
{
    friend class CObjectBase;
    CC_SYNTHESIZE_RETAIN(CScale9SpriteObject*, m_pBar, Bar);
public:
    FACTORY_CREATE_FUNC(CHPBar);
    virtual ~CHPBar();

    virtual void setPercentage(float percentage);
    virtual void setSpriteVisible(bool visible);
    virtual bool init(const char* foregroundName, const char* backgroundName);
    virtual void update(float dt);
    virtual void clearAll();

    virtual bool attachSpriteTo(Node* parent, int zOrder = 0, int tag = -1);
protected:
    CHPBar();
    void clearThis();
    
    void updateBar();

    float m_percentage;
private:
    Size OrigBarSize_;
    
};

#endif /* defined(__TheForce__CHPBar__) */
