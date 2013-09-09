//
//  CPathManager.h
//  EliminationPlane
//
//  Created by 马 俊 on 13-6-3.
//
//

#ifndef __EliminationPlane__TFPathManager__
#define __EliminationPlane__TFPathManager__

#include "cocos2d.h"
#include "CSingleton.h"
#include <string>

using namespace std;
USING_NS_CC;

class CPath;

class CPathManager : public CSingleton<CPathManager>
{
    CC_SYNTHESIZE_RETAIN(CCDictionary*, paths_, Paths);
public:
    CPathManager();
    virtual ~CPathManager();
    virtual bool initialize();
    
    virtual string makeRandomPath(const CCPoint& sp, const CCPoint& ep);
    virtual void removePath(const string& name);
    virtual CPath* getPathByName(const string& name);
protected:
    string makeTempPathName();
private:
    int m_tempPathNameIdx;
    const string m_tempPathNamePrefix;
};


#define PATH_MANAGER (CPathManager::getInstance())

#endif /* defined(__EliminationPlane__TFPathManager__) */
