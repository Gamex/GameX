//
//  CVisibleObject.h
//  TheForce
//
//  Created by Ray M on 13-3-7.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFVisibleObject__
#define __TheForce__TFVisibleObject__

#include "CObjectBase.h"
#include "CSensor.h"

class CVisibleObject : public CObjectBase
{
    CC_SYNTHESIZE_RETAIN(CSensor*, m_pSensor, Sensor);
public:
    virtual ~CVisibleObject();

    virtual void enableAlphaTest(float value);
    virtual CCRect getSpriteBoundingBox() const;
    virtual CCRect getSpriteBoundingBoxInWorldSpace();
    virtual CCPoint getSpritePositionInWorldSpace();
    virtual CCPoint getSpritePosition() const;
    virtual void setSpritePosition(const CCPoint& point);
    virtual void setSpriteVisible(bool visible);
    virtual void setSpriteScaleX(float sx);
    virtual void setSpriteScaleY(float sy);
    virtual void setSpriteScale(float s);
    virtual void setSpriteRotation(float degree);
    virtual float getSpriteRatatioin();
    virtual void setSpriteFlipX(bool f);
    virtual void setSpriteFlipY(bool f);
    virtual bool getSpriteFlipX();
    virtual bool getSpriteFlipY();
    virtual bool isSpriteVisible();
    virtual CCSize getSpriteContentSize();
    virtual void setSpriteZOrder(int z);
    virtual bool isSpriteInScreen();
    virtual void removeSpriteFromParentAndCleanup(bool cleanup=true);
    virtual bool runSpriteAction(CCAction* action);
    virtual void setSpriteAnchorPoint(const CCPoint& point);
    virtual void stopSpriteAllActions();
    
    virtual void setSpriteVertexZ(float z);
    virtual float getSpriteVertexZ() const;
    
    virtual bool attachSpriteTo(CCNode* parent, int zOrder = 0, int tag = -1);
    virtual bool dettachSpriteFrom(bool cleanup = true);
    
    virtual bool isNeedCheckCollision();
    virtual bool isCollsionWith(TFCollisionProtocol* obj);
    
    virtual void update(float dt);
    
    virtual void turnOffCollision();
    virtual void turnOnCollision();
    
    virtual void die();
    virtual void revive();
    
    virtual void clearAll();
    
    virtual CCNode* getInnerSprite() const=0;
    
    virtual bool addSlot(CVisibleObject* vo, int tag);
    virtual void removeSlot(CVisibleObject* vo);
    virtual void removeSlotByTag(int tag);
    virtual void updateSlots(float dt);
 
protected:
    CVisibleObject();
    void clearThis();
    
    virtual void _setSpriteVertexZ_R(CCNode* node, float z);
    virtual void _enableAlphaTestR(CCNode* node, float value);
    
    virtual void updateBoundingBoxInWorldSpace();
    virtual void onSensor(CCObject* obj);
    virtual void onSetSensorType(CSensor* pSensor);
   
    CCRect m_boundingBoxInWorldSpace;
    CCPoint m_positionInWorldSpace;
    bool m_isCachePosition;
    
    CCArray m_runningActions;
    
    MISVO m_slots;
private:
};

#endif /* defined(__TheForce__TFVisibleObject__) */
