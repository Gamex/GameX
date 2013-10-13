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

class CPath : public CCObject
{
public:    
    CPath();
    virtual ~CPath();
    
    bool initWithData(char* pData, int32_t length);
    bool initWithRandom(const CCPoint& sp, const CCPoint& ep);
    CCArray* getSpline() const {return spline_;}
    const std::string& getPathName(){return pathName_;}
protected:
    bool makeSpline(CCArray* cp);
private:
    CCArray* spline_;
    std::string pathName_;
};

#endif /* defined(__EliminationPlane__TFPath__) */
