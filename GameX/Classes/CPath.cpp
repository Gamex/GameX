//
//  CPath.cpp
//  EliminationPlane
//
//  Created by 马 俊 on 13-6-3.
//
//

#include "CPath.h"
#include <math.h>
#include "Common.h"
#if 0
#define B_SPLINE(u, u_2, u_3, cntrl0, cntrl1, cntrl2, cntrl3) \
( \
( \
(-1*u_3 + 3*u_2 - 3*u + 1) * (cntrl0) + \
( 3*u_3 - 6*u_2 + 0*u + 4) * (cntrl1) + \
(-3*u_3 + 3*u_2 + 3*u + 1) * (cntrl2) + \
( 1*u_3 + 0*u_2 + 0*u + 0) * (cntrl3)   \
) / 6 \
)

#define CATMULL_ROM_SPLINE(u, u_2, u_3, cntrl0, cntrl1, cntrl2, cntrl3) \
( \
( \
(-1*u_3 + 2*u_2 - 1*u + 0) * (cntrl0) + \
( 3*u_3 - 5*u_2 + 0*u + 2) * (cntrl1) + \
(-3*u_3 + 4*u_2 + 1*u + 0) * (cntrl2) + \
( 1*u_3 - 1*u_2 + 0*u + 0) * (cntrl3)   \
) / 2 \
)

#define SPLINE  CATMULL_ROM_SPLINE


CPath::CPath()
: spline_(NULL)
{
    
}



CPath::~CPath()
{
    CC_SAFE_RELEASE(spline_);
}



bool CPath::initWithData(char* pData, int32_t length)
{
    do
    {
//        char* p = pData;
//        pathName_.clear();
//        int32_t pathNameLen = *((int32_t*)p);
//        p += sizeof(int32_t);
//        
//        pathName_.resize(pathNameLen + 1);
//        memcpy(&(pathName_[0]), p, pathNameLen);
//        p += pathNameLen;
//        
//        int len = length - sizeof(int32_t) - pathNameLen;
//
//        CCArray* controlPoint = CCArray::create();
//        double x, y;
//
//        len /= 2 * sizeof(double);
//        for (int i = 0; i < len; ++i)
        {
//            x = *((double*)p);
//            p += sizeof(double);
//            y = *((double*)p);
//            p += sizeof(double);
            
//            CCPoint* pt = new CCPoint(x, y);
//            pt->autorelease();
//            controlPoint->addObject(pt);
        }

//        BREAK_IF(!makeSpline(controlPoint));
        return true;
    } while (false);
    
    return false;
}



bool CPath::makeSpline(CCArray* cp)
{
    int division;
    int maxDivision = 0;
    float u, u_2, u_3;
    int cpCount = (int)cp->count();
    if (cpCount < 4) return false;
    
    CC_SAFE_RELEASE(spline_);
    spline_ = CCArray::create();
    CC_SAFE_RETAIN(spline_);
    
    cpCount -= 3;
    CCPoint cps[4];
    
    for (int i = 0; i < cpCount; ++i)
    {
        cps[0] = *dynamic_cast<CCPoint*>(cp->objectAtIndex(i));
        cps[1] = *dynamic_cast<CCPoint*>(cp->objectAtIndex(i+1));
        cps[2] = *dynamic_cast<CCPoint*>(cp->objectAtIndex(i+2));
        cps[3] = *dynamic_cast<CCPoint*>(cp->objectAtIndex(i+3));
        
        CCPoint startPoint;
        CCPoint endPoint;
        startPoint.x = SPLINE(0.f, 0.f, 0.f,
                              cps[0].x,
                              cps[1].x,
                              cps[2].x,
                              cps[3].x);
        startPoint.y = SPLINE(0.f, 0.f, 0.f,
                              cps[0].y,
                              cps[1].y,
                              cps[2].y,
                              cps[3].y);
        
        
        endPoint.x = SPLINE(1.f, 1.f, 1.f,
                            cps[0].x,
                            cps[1].x,
                            cps[2].x,
                            cps[3].x);
        endPoint.y = SPLINE(1.f, 1.f, 1.f,
                            cps[0].y,
                            cps[1].y,
                            cps[2].y,
                            cps[3].y);
        
        division = MAX(fabs(startPoint.x-endPoint.x), fabs(startPoint.y-endPoint.y));
        if (division > maxDivision)
        {
            maxDivision = division;
        }
        for(int j = 0; j < division; j++)
        {
            
			u = (float)j / division;
			u_2 = u * u;
			u_3 = u_2 * u;
            
            CCPoint* curveData = new CCPoint;
            curveData->autorelease();
            // Position
            curveData->x = SPLINE(u, u_2, u_3,
                                  cps[0].x,
                                  cps[1].x,
                                  cps[2].x,
                                  cps[3].x);
            
            curveData->y = SPLINE(u, u_2, u_3,
                                  cps[0].y,
                                  cps[1].y,
                                  cps[2].y,
                                  cps[3].y);
            
            spline_->addObject(curveData);
        }
    }
    
    return true;
}


bool CPath::initWithRandom(const CCPoint& sp, const CCPoint& ep)
{
    CCSize winSz = CCDirector::sharedDirector()->getWinSize();
    
    CCRect rect;
    rect.origin.x = MIN(sp.x, ep.x);
    rect.origin.y = MIN(sp.y, ep.y);
    rect.size.width = fabsf(sp.x - ep.x);
    rect.size.height = fabsf(sp.y - ep.y);
    
    CCArray* controlPoints = CCArray::create();
    
    CCPoint* cp1 = new CCPoint(sp);
    cp1->autorelease();

    CCPoint* cp2 = new CCPoint(rect.origin.x +  CCRANDOM_0_1() * rect.size.width,
                               rect.origin.y + CCRANDOM_0_1() * rect.size.width);
    cp2->autorelease();
    
    CCPoint* cp3 = new CCPoint(rect.origin.x +  CCRANDOM_0_1() * rect.size.width,
                               rect.origin.y + CCRANDOM_0_1() * rect.size.width);
    cp3->autorelease();

    CCPoint* cp4 = new CCPoint(ep);
    cp4->autorelease();
    
    CCPoint* cp0 = new CCPoint;
    cp0->autorelease();
    if (cp1->x < winSz.width / 2.f)
    {
        cp0->x = 0;
    }
    else
    {
        cp0->x = winSz.width;
    }
    if (cp1->y < winSz.height / 2.f)
    {
        cp0->y = 0;
    }
    else
    {
        cp0->y = winSz.height;
    }
    
    
    CCPoint* cp5 = new CCPoint;
    cp5->autorelease();
    
    if (cp0->x == 0)
    {
        cp5->x = winSz.width;
    }
    else
    {
        cp5->x = 0;
    }
    
    if (cp0->y == 0)
    {
        cp0->y = winSz.height;
    }
    else
    {
        cp0->y = 0;
    }
    
    controlPoints->addObject(cp0);
    controlPoints->addObject(cp1);
    controlPoints->addObject(cp2);
    controlPoints->addObject(cp3);
    controlPoints->addObject(cp4);
    controlPoints->addObject(cp5);
    
    return makeSpline(controlPoints);
}

#endif