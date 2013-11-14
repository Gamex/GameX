//
//  UtilityFunction.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-14.
//
//

#include "UtilityFunction.h"
#include "CVisibleObject.h"

namespace utility
{
    float computeDistanceSquare(CVisibleObject* o1, CVisibleObject* o2)
    {
        Point p1 = o1->getSpritePosition();
        Point p2 = o2->getSpritePosition();
        
        return computeDistanceSquare(p1, p2);
    }
    
    
    
    float computeDistanceSquare(const Point& p1, const Point& p2)
    {
        Point vec(p1.x - p2.x, p1.y - p2.y);
        return vec.getLengthSq();
    }
    
    
//    Array* allTouchesSet(Set* touches)
//    {
//        Array *arr = Array::create();
//        
//        SetIterator it;
//        
//        for( it = touches->begin(); it != touches->end(); it++)
//        {
//            arr->addObject((Touch *)*it);
//        }
//        
//        return arr;
//        
//    }
}


