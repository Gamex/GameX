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
    
	Array* getRoot() const
	{
		return m_pArray;
	}
    
	void loadData2CCArray()
    {
        if (nullptr == m_pArray)
        {
            m_pArray = Array::create();
            CC_SAFE_RETAIN(m_pArray);
        }

		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("1"), "skillID");
			elem->setObject(String::create("CGameEffect"), "className");
			elem->setObject(String::create("100"), "cacheNum");
			elem->setObject(String::create("effect0"), "resourceID");

			
			m_pArray->addObject(elem);
		}

    }
        
    Dictionary* getData(int key)
    {
        CC_ASSERT(m_pArray);
        if(key < 0 || key >= m_pArray->count()) return nullptr;
        return dynamic_cast<Dictionary*>(m_pArray->getObjectAtIndex(key));
    }

    String* getValueOf(int key, const string& subKey)
    {
        CC_ASSERT(m_pArray);
        Dictionary* sub = getData(key);
        if (sub)
        {
            return dynamic_cast<String*>(sub->objectForKey(subKey));
        }
        return nullptr;
    }

    String* getValueOf(Dictionary* subDict, const string& subKey)
    {
        CC_ASSERT(subDict);
        return dynamic_cast<String*>(subDict->objectForKey(subKey));
    }

	String* get_className_Value(int key)
	{
		return getValueOf(key, "className");
	}
	String* get_className_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "className");
	}

	String* get_cacheNum_Value(int key)
	{
		return getValueOf(key, "cacheNum");
	}
	String* get_cacheNum_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "cacheNum");
	}

	String* get_resourceID_Value(int key)
	{
		return getValueOf(key, "resourceID");
	}
	String* get_resourceID_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "resourceID");
	}



protected:
	DTEffect():m_pArray(nullptr)
	{}
	~DTEffect()
	{
		CC_SAFE_RELEASE(m_pArray);
	}
	
private:
	Array* m_pArray;
};


#endif	// __DTEffect__