//
//  CPath.h
//  EliminationPlane
//
//  Created by 马 俊 on 13-6-3.
//
//

#ifndef __EliminationPlane__TFPath__
#define __EliminationPlane__TFPath__

#include "Common.h"
#if 0
class CPath : public Object
{
public:    
    CPath();
    virtual ~CPath();
    
    bool initWithData(char* pData, int32_t length);
    bool initWithRandom(const Point& sp, const Point& ep);
    Array* getSpline() const {return spline_;}
    const std::string& getPathName(){return pathName_;}
protected:
    bool makeSpline(Array* cp);
private:
    Array* spline_;
    std::string pathName_;
};
#endif
#endif /* defined(__EliminationPlane__TFPath__) */
