//
//  CNodeContainer.h
//  TheForce
//
//  Created by 马 俊 on 13-2-21.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFBatchNodeBase__
#define __TheForce__TFBatchNodeBase__

#include "Common.h"

class CObjectBase;

typedef bool (CCObject::*NODE_CONTAINER_INIT_CALL_BACK)(SOB& unUseArrray, CObjectBase* curObj, void* pUserData);

class CNodeContainer
{
public:
    CNodeContainer();
    virtual ~CNodeContainer();
    
    const SOB& getInUseArray() const;
    unsigned int  getInUseCount();
    virtual bool initCache(const std::string& name, int num, CCObject* target = NULL, NODE_CONTAINER_INIT_CALL_BACK callback = NULL, void* pUserData = NULL);
    virtual CObjectBase* checkoutElement();
    virtual void checkinElement(CObjectBase* elem);
    virtual void clear();

protected:
private:
    SOB m_containerInUseArray;
    SOB m_containerUnUseArray;
};

#endif /* defined(__TheForce__TFBatchNodeBase__) */
