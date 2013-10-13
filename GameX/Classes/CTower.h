//
//  CTower.h
//  GameX
//
//  Created by 马 俊 on 13-6-11.
//
//

#ifndef __GameX__CTower__
#define __GameX__CTower__

#include "CRole.h"
#include "TFCollisionProtocol.h"

class CPath;

class CTower : public CRole
{
    friend class CObjectBase;
public:
    FACTORY_CREATE_FUNC(CTower);

#ifdef DEBUG
    virtual std::string whoAmI(){return "Tower";}
#endif

protected:
    virtual void onSensor(CCObject* obj);

private:
};

#endif /* defined(__GameX__CTower__) */
