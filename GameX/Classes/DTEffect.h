#ifndef __DTEffect__
#define __DTEffect__
#include "cocos2d.h"
#include <string>

using namespace std;
USING_NS_CC;

class DTEffect
{
	friend class CDataCenterManager;
public:
    int getArrayCount() const
    {
        return m_pArray->count();
    }
    
	CCArray* getRoot() const
	{
		return m_pArray;
	}
    
	void loadData2CCArray()
    {
        if (NULL == m_pArray)
        {
            m_pArray = CCArray::create();
            CC_SAFE_RETAIN(m_pArray);
        }

		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("1"), "skillID");
			elem->setObject(CCString::create("CGameEffect"), "className");
			elem->setObject(CCString::create("100"), "cacheNum");
			elem->setObject(CCString::create("Effect0"), "resourceID");

			
			m_pArray->addObject(elem);
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

	CCString* get_className_Value(int key)
	{
		return getValueOf(key, "className");
	}
	CCString* get_className_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "className");
	}

	CCString* get_cacheNum_Value(int key)
	{
		return getValueOf(key, "cacheNum");
	}
	CCString* get_cacheNum_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "cacheNum");
	}

	CCString* get_resourceID_Value(int key)
	{
		return getValueOf(key, "resourceID");
	}
	CCString* get_resourceID_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "resourceID");
	}



protected:
	DTEffect():m_pArray(NULL)
	{}
	~DTEffect()
	{
		CC_SAFE_RELEASE(m_pArray);
	}
	
private:
	CCArray* m_pArray;
};


#endif	// __DTEffect__