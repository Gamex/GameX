//
//  CGameEffect.cpp
//  GameX
//
//  Created by 马 俊 on 13-10-23.
//
//

#include "CGameEffect.h"
#include "CRole.h"


void CGameEffect::clearThis()
{
}



CGameEffect::CGameEffect()
: m_damage(0.f)
, m_effectTarget(nullptr)
, m_effectOwner(nullptr)
{
}



CGameEffect::~CGameEffect()
{
}



bool CGameEffect::init(const string& ccbi_name)
{
    do
    {
        BREAK_IF_FAILED(CSpriteObject::init());
        BREAK_IF_FAILED(setSpriteFromCcbi(ccbi_name.c_str()));
        enableAlphaTest(0.5f);
        return true;
    } while (false);
    
	return false;
}



bool CGameEffect::attachSpriteTo(Node* parent, int zOrder, int tag)
{
	return CSpriteObject::attachSpriteTo(parent, zOrder, tag);
}



void CGameEffect::die()
{
    CSpriteObject::die();
    setSpriteVisible(false);
}



void CGameEffect::revive()
{
    CSpriteObject::revive();
    setSpriteVisible(true);
}



void CGameEffect::update(float dt)
{
}



void CGameEffect::clearAll()
{
}



SEL_CallFuncN CGameEffect::onResolveCCBCCCallFuncSelector(Object * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onEffectHit", CGameEffect::onEffectHit);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onEffectOver", CGameEffect::onEffectOver);
    return nullptr;
}



void CGameEffect::onEffectHit(Node* obj)
{
    m_effectTarget->damage(m_damage, m_effectTarget);
}



void CGameEffect::onEffectOver(Node* obj)
{
    die();
}



void CGameEffect::setEffectTarget(CRole* target)
{
    CC_ASSERT(target);
    m_effectTarget = target;
    this->setSpriteVertexZ(m_effectTarget->getSpriteVertexZ() + .2);
}



CRole* CGameEffect::getEffectTarget()
{
    return m_effectTarget;
}

