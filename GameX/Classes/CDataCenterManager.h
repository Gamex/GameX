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
#include "DTLevel.h"
#include "DTScene.h"
#include "DTUnit.h"
#include "DTSkill.h"


class CDataCenterManager : public CSingleton<CDataCenterManager>
{
public:
    CDataCenterManager();
    virtual ~CDataCenterManager();
    
    virtual bool initialize();
    
    DTLevel* getDTLevel(){return m_DTLevel;}
    DTScene* getDTScene(){return m_DTScene;}
    DTUnit* getDTUnit(){return m_DTUnit;}
    DTSkill* getDTSkill(){return m_DTSkill;}
protected:
private:
    DTLevel* m_DTLevel;
    DTScene* m_DTScene;
    DTUnit* m_DTUnit;
    DTSkill* m_DTSkill;
};


#define DATA_CENTER         (CDataCenterManager::getInstance())
#define DTLEVEL             (DATA_CENTER->getDTLevel())
#define DTSCENE             (DATA_CENTER->getDTScene())
#define DTUNIT              (DATA_CENTER->getDTUnit())
#define DTSKILL             (DATA_CENTER->getDTSkill())

#endif /* defined(__GameX__CDataCenterManager__) */
