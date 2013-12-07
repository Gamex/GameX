//
//  CDataCenterManager.h
//  GameX
//
//  Created by 马 俊 on 13-8-23.
//
//

#ifndef __GameX__CDataCenterManager__
#define __GameX__CDataCenterManager__

#include "CSingleton.h"
#include "DTUnit.h"
#include "DTSkill.h"
#include "DTEffect.h"



class CDataCenterManager : public CSingleton<CDataCenterManager>
{
public:
    CDataCenterManager();
    virtual ~CDataCenterManager();
    virtual bool initialize();
    
    DTUnit* getDTUnit(){return m_DTUnit;}
    DTSkill* getDTSkill(){return m_DTSkill;}
    DTEffect* getDTEffect(){return m_DTEffect;}
protected:
private:

    DTUnit* m_DTUnit = nullptr;
    DTSkill* m_DTSkill = nullptr;
    DTEffect* m_DTEffect = nullptr;
};


#define DATA_CENTER         (CDataCenterManager::getInstance())
#define DTUNIT              (DATA_CENTER->getDTUnit())
#define DTSKILL             (DATA_CENTER->getDTSkill())
#define DTEFFECT            (DATA_CENTER->getDTEffect())

#endif /* defined(__GameX__CDataCenterManager__) */
