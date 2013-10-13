//
//  CBallisticAOEBullet.cpp
//  GameX
//
//  Created by 马 俊 on 13-7-18.
//
//

#include "CBallisticAOEBullet.h"


DEFINE_DICTFUNC(CBallisticAOEBullet, float, DamageArea, 0);

CBallisticAOEBullet::CBallisticAOEBullet()
: m_isBombed(false)
, m_startBomb(false)
{
    
}



CBallisticAOEBullet::~CBallisticAOEBullet()
{
    
}



void CBallisticAOEBullet::onHitTarget()
{
//    changeState(BALLISTIC_AOE_BULLET_STATE_BOMB);
}



void CBallisticAOEBullet::update(float dt)
{
    CBallisticBullet::update(dt);
    
    
}



void CBallisticAOEBullet::onCollideWithTarget(TFCollisionProtocol* obj)
{
//    const std::string& state = getCurrentState();
//    
//    if (state.compare(BALLISTIC_AOE_BULLET_STATE_BOMB) == 0)
//    {
//        CObjectBase* object = dynamic_cast<CObjectBase*>(obj);
//        if (object)
//        {
//            object->die();
//        }
//    }
}



void CBallisticAOEBullet::updateBoundingBoxInWorldSpace()
{
//    const std::string& state = getCurrentState();
//
//    if (state.compare(BALLISTIC_AOE_BULLET_STATE_BOMB) == 0)
//    {
//        float DamageArea = getDamageAreaFromDict();
//        CCNode* pInnerSprite = getInnerSprite();
//        if (pInnerSprite)
//        {
//            m_positionInWorldSpace = getSpritePosition();
//            m_boundingBoxInWorldSpace.origin = ccp(m_positionInWorldSpace.x - DamageArea / 2.f, m_positionInWorldSpace.y - DamageArea / 2.f);
//            m_boundingBoxInWorldSpace.size = CCSize(DamageArea, DamageArea);
//            
//            if (NULL != pInnerSprite->getParent())
//            {
//                m_boundingBoxInWorldSpace.origin = pInnerSprite->getParent()->convertToWorldSpaceAR(m_boundingBoxInWorldSpace.origin);
//                m_positionInWorldSpace = pInnerSprite->getParent()->convertToWorldSpaceAR(m_positionInWorldSpace);
//            }
//        }
//    }
//    else
//    {
//        CBallisticBullet::updateBoundingBoxInWorldSpace();
//    }
}



void CBallisticAOEBullet::completedAnimationSequenceNamed(const char *name)
{
    if (strcmp(name, BALLISTIC_AOE_BULLET_STATE_BOMB) == 0)
    {
        die();
    }
}

