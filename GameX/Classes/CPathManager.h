//
//  CPathManager.h
//  EliminationPlane
//
//  Created by 马 俊 on 13-6-3.
//
//

#ifndef __EliminationPlane__TFPathManager__
#define __EliminationPlane__TFPathManager__

#include "Common.h"
#include "CSingleton.h"
#if 0

class CPath;

class CPathManager : public CSingleton<CPathManager>
{
    CC_SYNTHESIZE_RETAIN(Dictionary*, paths_, Paths);
public:
    CPathManager();
    virtual ~CPathManager();
    virtual bool initialize();
    
    virtual std::string makeRandomPath(const Point& sp, const Point& ep);
    virtual void removePath(const std::string& name);
    virtual CPath* getPathByName(const std::string& name);
protected:
    std::string makeTempPathName();
private:
    int m_tempPathNameIdx;
    const std::string m_tempPathNamePrefix;
};


#define PATH_MANAGER (CPathManager::getInstance())

#endif
#endif /* defined(__EliminationPlane__TFPathManager__) */
