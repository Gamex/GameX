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


class CFormationElement
{
public:
    CCPoint pos;
    std::string unitId;
};

class CFormation
{
public:
    virtual bool saveToFile(const char* filename = NULL);
    virtual bool loadFromFile(const char* filename = NULL);
    
    void clearAll();
    
    VFE m_elements;
    std::string m_filename;
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
    
    CFormation* getFormation1()
    {
        return &m_formation1;
    }
    
protected:
private:
    CFormation m_formation;
    CFormation m_formation1;
};

#define FORMATION_MANAGER       (CFormationManager::getInstance())

#endif /* defined(__GameX__CFormationManager__) */
