#ifndef __DTlevel__
#define __DTlevel__
#include "cocos2d.h"
#include <string>

using namespace std;
USING_NS_CC;

class DTlevel
{
	friend class CDataCenterManager;
public:
	void loadData2CCArray()
    {
        if (NULL == m_pArray)
        {
            m_pArray = CCArray::create();
            CC_SAFE_RETAIN(m_pArray);
        }


    }
        
    CCDictionary* getData(int key)
    {
        CC_ASSERT(m_pArray);
        if(key < 0 || key >= m_pArray->count()) return NULL;
        return dynamic_cast<CCDictionary*>(m_pArray->objectAtIndex(key));
    }

    CCString* getValueOf(int key, const string& subKey)
    {
        CC_ASSERT(m_pArray);
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
	DTlevel():m_pArray(NULL)
	{}
	~DTlevel()
	{
		CC_SAFE_RELEASE(m_pArray);
	}
	
private:
	CCArray* m_pArray;
};


#endif	// __DTlevel__