//
//  CCircleSensor.h
//  GameX
//
//  Created by 马 俊 on 13-6-10.
//
//

#ifndef __GameX__CCircleSensor__
#define __GameX__CCircleSensor__

#include "CSensor.h"

class CCircleSensor : public CSensor
{
    friend class CObjectBase;
public:
    virtual ~CCircleSensor();
    FACTORY_CREATE_FUNC(CCircleSensor);

    virtual bool isCollsionWith(TFCollisionProtocol* object);
protected:
    CCircleSensor();
private:
    float m_radius;
    float m_radiusSquare;
};

#endif /* defined(__GameX__CCircleSensor__) */
