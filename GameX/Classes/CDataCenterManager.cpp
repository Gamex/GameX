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
: m_DTLevel(nullptr)
, m_DTScene(nullptr)
, m_DTUnit(nullptr)
{
}


CDataCenterManager::~CDataCenterManager()
{
    CC_SAFE_DELETE(m_DTLevel);
    CC_SAFE_DELETE(m_DTScene);
    CC_SAFE_DELETE(m_DTUnit);
    CC_SAFE_DELETE(m_DTSkill);
}



bool CDataCenterManager::initialize()
{
    do
    {
        m_DTLevel = new DTLevel;
        m_DTLevel->loadData2CCArray();
        
        m_DTScene = new DTScene;
        m_DTScene->loadData2CCDictionary();
        
        m_DTUnit = new DTUnit;
        m_DTUnit->loadData2CCDictionary();
        
        m_DTSkill = new DTSkill;
        m_DTSkill->loadData2CCDictionary();
        
        m_DTEffect = new DTEffect;
        m_DTEffect->loadData2CCArray();
        
        return true;
    } while (false);
    
    return false;
}
