//
//  CShopManager.h
//  GameX
//
//  Created by 马 俊 on 13-12-10.
//
//

#ifndef __GameX__CShopManager__
#define __GameX__CShopManager__

#include "Common.h"
#include "CSingleton.h"

class CShopManager
: public CSingleton<CShopManager>
{
public:
    CShopManager();
    ~CShopManager();

    bool initialize();
    const vector<string>& getShopListByLevel(int level);
protected:
private:
    int m_curLevel = 0;
    vector<string> m_IDs;
};


#define SHOP    (CShopManager::getInstance())

#endif /* defined(__GameX__CShopManager__) */
