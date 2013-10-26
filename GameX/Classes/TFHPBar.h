//
//  TFHPBar.h
//  TheForce
//
//  Created by Ray M on 13-2-19.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFHPBar__
#define __TheForce__TFHPBar__

#include "CSpriteObject.h"
#include "CScale9SpriteObject.h"


class TFHPBar : public CSpriteObject
{
    friend class CObjectBase;
    CC_SYNTHESIZE_RETAIN(CScale9SpriteObject*, m_pBar, Bar);
public:
    FACTORY_CREATE_FUNC(TFHPBar);
    virtual ~TFHPBar();

    virtual void setPercentage(float percentage);
    virtual void setSpriteVisible(bool visible);
    virtual bool init();
    virtual void update(float dt);
    virtual void clearAll();

protected:
    TFHPBar();
    void clearThis();
    
    void updateBar();

    float m_percentage;
private:
    CCSize OrigBarSize_;
    
};

#endif /* defined(__TheForce__TFHPBar__) */
