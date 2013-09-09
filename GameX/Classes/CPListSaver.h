//
//  CPListSaver.h
//  EliminationPlane
//
//  Created by 马 俊 on 13-4-24.
//
//

#ifndef __EliminationPlane__CPListSaver__
#define __EliminationPlane__CPListSaver__

#include "cocos2d.h"

USING_NS_CC;

// USAGE:
// string filename = cocos2d::CCFileUtils::sharedFileUtils()->getWriteablePath() + string("test.plist");
// CPListSaver::save2Plist(pDictToSave, filename.c_str());

class CPListSaver
{
public:
    static bool save2Plist(CCDictionary* pDict, const char* filename);
protected:
    static bool saveArray(CCArray* pArray, tinyxml2::XMLElement* node, tinyxml2::XMLDocument* doc);
    static bool saveDictionary(CCDictionary* pDict, tinyxml2::XMLElement* node, tinyxml2::XMLDocument* doc);
    static bool saveKey(const char* key, tinyxml2::XMLElement* node, tinyxml2::XMLDocument* doc);
    static bool saveString(const char* str, tinyxml2::XMLElement* node, tinyxml2::XMLDocument* doc);
private:
};

#endif /* defined(__EliminationPlane__CPListSaver__) */
