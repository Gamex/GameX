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
#include "DTRequirement.h"
#include "DTConstructTable.h"

class CDataCenterManager : public CSingleton<CDataCenterManager>
{
public:
    CDataCenterManager();
    virtual ~CDataCenterManager();
    virtual bool initialize();
    
    DTUnit* getDTUnit(){return m_DTUnit;}
    DTSkill* getDTSkill(){return m_DTSkill;}
    DTEffect* getDTEffect(){return m_DTEffect;}
    DTRequirement* getRequirement(){return m_DTRequirement;}
    DTConstructTable* getConstructTable(){return m_DTConstructTable;}
protected:
private:

    DTUnit* m_DTUnit = nullptr;
    DTSkill* m_DTSkill = nullptr;
    DTEffect* m_DTEffect = nullptr;
    DTRequirement* m_DTRequirement = nullptr;
    DTConstructTable* m_DTConstructTable = nullptr;
};


#define DATA_CENTER         (CDataCenterManager::getInstance())
#define DTUNIT              (DATA_CENTER->getDTUnit())
#define DTSKILL             (DATA_CENTER->getDTSkill())
#define DTEFFECT            (DATA_CENTER->getDTEffect())
#define DTREQUIREMENT       (DATA_CENTER->getRequirement())
#define DTCONSTRUCTTABLE    (DATA_CENTER->getConstructTable())

#endif /* defined(__GameX__CDataCenterManager__) */
