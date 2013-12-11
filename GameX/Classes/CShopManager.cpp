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
        stringstream ss;
        ss << 1;
        string levelStr = ss.str();
        auto keys = DTREQUIREMENT->getAllKeys();
        for (int i = 0; i < keys.size(); ++i)
        {
            auto data = DTREQUIREMENT->getData(keys[i]);
            if (data->ex_unit == levelStr)
            {
                m_IDs.push_back(data->ID);
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
        auto keys = DTREQUIREMENT->getAllKeys();
        do
        {
            ++m_curLevel;
            stringstream ss;
            ss << m_curLevel;
            string levelStr = ss.str();
            
            for (int i = 0; i < keys.size(); ++i)
            {
                auto data = DTREQUIREMENT->getData(keys[i]);
                if (data->ex_unit == levelStr)
                {
                    m_IDs.push_back(data->ID);
                }
            }
            
        } while (level > m_curLevel);
    }

    return m_IDs;
}



