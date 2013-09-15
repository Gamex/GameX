//
//  CFormationManager.h
//  GameX
//
//  Created by 马 俊 on 13-9-1.
//
//

#ifndef __GameX__CFormationManager__
#define __GameX__CFormationManager__

#include "cocos2d.h"
#include "Common.h"
#include "CSingleton.h"
#include <vector>

USING_NS_CC;
using namespace std;

class CFormationElement
{
public:
    CCPoint pos;
    string objName;
};

class CFormation
{
public:
    typedef vector<CFormationElement*> VFE;
    typedef vector<CFormationElement*>::iterator VFE_IT;
    typedef vector<CFormationElement*>::const_iterator VFE_CIT;
    
    virtual bool saveToFile(const char* filename);
    virtual bool loadFromFile(const char* filename);
    
    void clearAll();
    
    VFE m_elements;
};

class CFormationManager : public CSingleton<CFormationManager>
{
public:
    CFormationManager();
    virtual ~CFormationManager();
    
    CFormation* getFormation()
    {
        return &m_formation;
    }
    
protected:
private:
    CFormation m_formation;
};

#define FORMATION_MANAGER       (CFormationManager::getInstance())

#endif /* defined(__GameX__CFormationManager__) */
