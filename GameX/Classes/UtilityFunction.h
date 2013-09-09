//
//  UtilityFunction.h
//  GameX
//
//  Created by 马 俊 on 13-6-14.
//
//

#ifndef __GameX__UtilityFunction__
#define __GameX__UtilityFunction__

#include "cocos2d.h"

class CVisibleObject;

USING_NS_CC;

namespace utility
{
    float computeDistanceSquare(CVisibleObject* o1, CVisibleObject* o2);
    float computeDistanceSquare(const CCPoint& p1, const CCPoint& p2);
}

#endif /* defined(__GameX__UtilityFunction__) */
