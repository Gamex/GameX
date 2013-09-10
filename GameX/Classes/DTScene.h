#ifndef __DTScene__
#define __DTScene__
#include "cocos2d.h"
#include <string>

using namespace std;
USING_NS_CC;

class DTScene
{
	friend class CDataCenterManager;
public:
	void loadData2CCDictionary()
    {
        if (NULL == m_pDictionary)
        {
            m_pDictionary = CCDictionary::create();
            CC_SAFE_RETAIN(m_pDictionary);
        }


    }
        
    CCDictionary* getData(const string& key)
    {
        CC_ASSERT(m_pDictionary);
        return dynamic_cast<CCDictionary*>(m_pDictionary->objectForKey(key));
    }

    CCString* getValueOf(const string& key, const string& subKey)
    {
        CC_ASSERT(m_pDictionary);
        CCDictionary* sub = getData(key);
        if (sub)
        {
            return dynamic_cast<CCString*>(sub->objectForKey(subKey));
        }
        return NULL;
    }

    CCString* getValueOf(CCDictionary* subDict, const string& subKey)
    {
        CC_ASSERT(subDict);
        return dynamic_cast<CCString*>(subDict->objectForKey(subKey));
    }



protected:
	DTScene():m_pDictionary(NULL)
	{}
	~DTScene()
	{
		CC_SAFE_RELEASE(m_pDictionary);
	}
	
private:
	CCDictionary* m_pDictionary;
};


#endif	// __DTScene__