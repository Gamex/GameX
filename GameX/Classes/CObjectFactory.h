//
//  CObjectFactory.h
//  EliminationPlane
//
//  Created by Ray M on 13-4-3.
//
//

#ifndef __EliminationPlane__TFObjectFactory__
#define __EliminationPlane__TFObjectFactory__

#include "CSingleton.h"

#include <map>
#include <string>

class CObjectBase;

using namespace std;


class CObjectFactory : public CSingleton<CObjectFactory>
{
public:
    typedef CObjectBase* (*FACTORY_CREATE_FUNC)();

    CObjectFactory();
    virtual ~CObjectFactory();
    
    bool Initialize();
    CObjectBase* createInstance(const string& className);
    
protected:
    bool registerClass(const string&  className, FACTORY_CREATE_FUNC func);
private:
    typedef map<string, FACTORY_CREATE_FUNC> MSCF;
    typedef map<string, FACTORY_CREATE_FUNC>::iterator MSCF_IT;
    typedef map<string, FACTORY_CREATE_FUNC>::const_iterator MSCF_CIT;
    
    MSCF FactoryTable_;
    
};

#define FACTORY_CREATE_FUNC(__type) static CObjectBase* create() \
{ \
    __type *pRet = new __type(); \
    if (pRet) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

#define OBJECT_FACTORY (CObjectFactory::getInstance())


#endif /* defined(__EliminationPlane__TFObjectFactory__) */
