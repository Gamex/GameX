//
//  UtilityFunction.h
//  GameX
//
//  Created by 马 俊 on 13-6-14.
//
//

#ifndef __GameX__UtilityFunction__
#define __GameX__UtilityFunction__

#include "Common.h"

class CVisibleObject;


namespace utility
{
    float computeDistanceSquare(CVisibleObject* o1, CVisibleObject* o2);
    float computeDistanceSquare(const Point& p1, const Point& p2);
    
    Array* allTouchesSet(Set* touches);
}

#endif /* defined(__GameX__UtilityFunction__) */
