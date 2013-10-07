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
        CCPoint p1 = o1->getSpritePosition();
        CCPoint p2 = o2->getSpritePosition();
        
        return computeDistanceSquare(p1, p2);
    }
    
    
    
    float computeDistanceSquare(const CCPoint& p1, const CCPoint& p2)
    {
        CCPoint vec(p1.x - p2.x, p1.y - p2.y);
        return vec.getLengthSq();
    }
    
    
    CCArray* allTouchesSet(CCSet* touches)
    {
        CCArray *arr = CCArray::create();
        
        CCSetIterator it;
        
        for( it = touches->begin(); it != touches->end(); it++)
        {
            arr->addObject((CCTouch *)*it);
        }
        
        return arr;
        
    }
}


