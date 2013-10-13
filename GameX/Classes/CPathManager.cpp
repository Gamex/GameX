//
//  CPathManager.cpp
//  EliminationPlane
//
//  Created by 马 俊 on 13-6-3.
//
//

#include "CPathManager.h"
#include "CPath.h"
#include <vector>
#include "Common.h"

using namespace std;

IMPLEMENT_SINGLETON(CPathManager);


CPathManager::CPathManager()
: paths_(NULL)
, m_tempPathNamePrefix("__ray__pre__")
, m_tempPathNameIdx(0)
{
    
}



CPathManager::~CPathManager()
{
    setPaths(NULL);
}



bool CPathManager::initialize()
{
    return true;
#if 0           // 这里要重写，必须用getFileData一次性取出所有文件内容，而不能用fread一点点读，因为android系统下面这些文件都是压缩打包的
    do
    {
        setPaths(CCDictionary::create());
        BREAK_IF(!paths_);
        
        const char* cp = "game_path.pmp";
        const char* fcp = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(cp);
        
        FILE* fp = fopen(fcp, "rb");
        BREAK_IF(NULL == fp);
        int32_t pathCount;
        fread(&pathCount, sizeof(pathCount), 1, fp);
        vector<int32_t> offsetTable;
        vector<int32_t> lengthTable;
        int32_t offset, length;
        for (int32_t i = 0; i < pathCount; ++i)
        {
            fread(&offset, sizeof(int32_t), 1, fp);
            fread(&length, sizeof(int32_t), 1, fp);
            offsetTable.push_back(offset);
            lengthTable.push_back(length);
        }
        for (int32_t i = 0; i < pathCount; ++i)
        {
            offset = offsetTable[i];
            length = lengthTable[i];
            
            auto_ptr<char> pathData(new char[length]);
            fseek(fp, offset, SEEK_SET);
            fread(pathData.get(), length, 1, fp);
            
            CPath* path = new CPath;
            path->autorelease();
            BREAK_IF(!path->initWithData(pathData.get(), length));

//            paths_->setObject(path, path->getPathName());
        }

        return true;
    }while (false);
        
    return false;
#endif
}



CPath* CPathManager::getPathByName(const std::string& name)
{
    return dynamic_cast<CPath*>(paths_->objectForKey(name));
}



string CPathManager::makeRandomPath(const CCPoint& sp, const CCPoint& ep)
{
    do
    {
        CPath* path = new CPath;
        path->autorelease();
        path->initWithRandom(sp, ep);
        
        std::string name = makeTempPathName();
        paths_->setObject(path, name);
        
        return name;
    } while (false);
    
    
    return std::string();
}



string CPathManager::makeTempPathName()
{
    do
    {
        char name[260];
        m_tempPathNameIdx++;
        sprintf(name, "%s%d", m_tempPathNamePrefix.c_str(), m_tempPathNameIdx);

        if (paths_->objectForKey(name) == NULL)
        {
            return std::string(name);
        }
    } while (true);
}



void CPathManager::removePath(const std::string& name)
{
    if (!name.empty())
    {
        paths_->removeObjectForKey(name);
    }
}
