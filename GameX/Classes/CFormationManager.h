//
//  CFormationManager.h
//  GameX
//
//  Created by 马 俊 on 13-9-1.
//
//

#ifndef __GameX__CFormationManager__
#define __GameX__CFormationManager__

#include "Common.h"
#include "CSingleton.h"
#include <vector>

using namespace std;

class CFormationElement
{
public:
    CGridPos pos;
    int type;
};

class CFormation
{
public:
    typedef vector<CFormationElement*> VFE;
    typedef vector<CFormationElement*>::iterator VFE_IT;
    typedef vector<CFormationElement*>::const_iterator VFE_CIT;
    
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
