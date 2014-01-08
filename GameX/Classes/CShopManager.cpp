//
//  CShopManager.cpp
//  GameX
//
//  Created by 马 俊 on 13-12-10.
//
//

#include "CShopManager.h"
#include "CDataCenterManager.h"

IMPLEMENT_SINGLETON(CShopManager);

CShopManager::CShopManager()
{
}



CShopManager::~CShopManager()
{
}



bool CShopManager::initialize()
{
    do
    {
        CCASSERT(DTREQUIREMENT, "you must initialize CDataManager first!");
        m_curLevel = 1;
        auto keys = DTCONSTRUCTTABLE->getAllKeys();
        for (int i = 0; i < keys.size(); ++i)
        {
            auto data = DTCONSTRUCTTABLE->getData(keys[i]);
            if (data->level == m_curLevel && data->type == m_TYPE)
            {
                m_IDs.push_back(data->unitId);
            }
        }
        return true;
    } while(false);
    
	return false;
}



const vector<string>& CShopManager::getShopListByLevel(int level)
{
    CC_ASSERT(level >= m_curLevel);
    if (level > m_curLevel)
    {
        auto keys = DTCONSTRUCTTABLE->getAllKeys();
        do
        {
            ++m_curLevel;
            
            for (int i = 0; i < keys.size(); ++i)
            {
                auto data = DTCONSTRUCTTABLE->getData(keys[i]);
                if (data->level == m_curLevel && data->type == m_TYPE)
                {
                    m_IDs.push_back(data->unitId);
                }
            }
            
        } while (level > m_curLevel);
    }

    return m_IDs;
}



