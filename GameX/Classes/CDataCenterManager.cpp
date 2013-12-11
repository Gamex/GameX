//
//  CDataCenterManager.cpp
//  GameX
//
//  Created by 马 俊 on 13-8-23.
//
//

#include "CDataCenterManager.h"

IMPLEMENT_SINGLETON(CDataCenterManager);

CDataCenterManager::CDataCenterManager()
{
}


CDataCenterManager::~CDataCenterManager()
{
    CC_SAFE_DELETE(m_DTUnit);
    CC_SAFE_DELETE(m_DTSkill);
    CC_SAFE_DELETE(m_DTEffect);
}



bool CDataCenterManager::initialize()
{
    do
    {
        m_DTUnit = new DTUnit;
        m_DTUnit->loadJSONData();
        
        m_DTSkill = new DTSkill;
        m_DTSkill->loadJSONData();
        
        m_DTEffect = new DTEffect;
        m_DTEffect->loadJSONData();
        
        m_DTRequirement = new DTRequirement;
        m_DTRequirement->loadJSONData();
        
        return true;
    } while (false);
    
    return false;
}
