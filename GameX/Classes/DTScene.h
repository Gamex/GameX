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

		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("600"), "positionx");
			elem->setObject(CCString::create("32"), "positiony");
			elem->setObject(CCString::create("60"), "length");
			elem->setObject(CCString::create("32"), "width");
			elem->setObject(CCString::create("1"), "target");
			elem->setObject(CCString::create("0"), "related1");
			elem->setObject(CCString::create("1"), "wt1");
			elem->setObject(CCString::create("2"), "related2");
			elem->setObject(CCString::create("1"), "wt2");

			
			m_pDictionary->setObject(elem, "1");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("600"), "positionx");
			elem->setObject(CCString::create("96"), "positiony");
			elem->setObject(CCString::create("60"), "length");
			elem->setObject(CCString::create("32"), "width");
			elem->setObject(CCString::create("2"), "target");
			elem->setObject(CCString::create("1"), "related1");
			elem->setObject(CCString::create("1"), "wt1");
			elem->setObject(CCString::create("3"), "related2");
			elem->setObject(CCString::create("1"), "wt2");

			
			m_pDictionary->setObject(elem, "2");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("600"), "positionx");
			elem->setObject(CCString::create("160"), "positiony");
			elem->setObject(CCString::create("60"), "length");
			elem->setObject(CCString::create("32"), "width");
			elem->setObject(CCString::create("3"), "target");
			elem->setObject(CCString::create("2"), "related1");
			elem->setObject(CCString::create("1"), "wt1");
			elem->setObject(CCString::create("4"), "related2");
			elem->setObject(CCString::create("1"), "wt2");

			
			m_pDictionary->setObject(elem, "3");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("600"), "positionx");
			elem->setObject(CCString::create("224"), "positiony");
			elem->setObject(CCString::create("60"), "length");
			elem->setObject(CCString::create("32"), "width");
			elem->setObject(CCString::create("4"), "target");
			elem->setObject(CCString::create("3"), "related1");
			elem->setObject(CCString::create("1"), "wt1");
			elem->setObject(CCString::create("5"), "related2");
			elem->setObject(CCString::create("1"), "wt2");

			
			m_pDictionary->setObject(elem, "4");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("600"), "positionx");
			elem->setObject(CCString::create("288"), "positiony");
			elem->setObject(CCString::create("60"), "length");
			elem->setObject(CCString::create("32"), "width");
			elem->setObject(CCString::create("5"), "target");
			elem->setObject(CCString::create("4"), "related1");
			elem->setObject(CCString::create("1"), "wt1");
			elem->setObject(CCString::create("0"), "related2");
			elem->setObject(CCString::create("1"), "wt2");

			
			m_pDictionary->setObject(elem, "5");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("300"), "positionx");
			elem->setObject(CCString::create("-40"), "positiony");
			elem->setObject(CCString::create("60"), "length");
			elem->setObject(CCString::create("32"), "width");
			elem->setObject(CCString::create("1"), "target");
			elem->setObject(CCString::create("0"), "related1");
			elem->setObject(CCString::create("1"), "wt1");
			elem->setObject(CCString::create("2"), "related2");
			elem->setObject(CCString::create("1"), "wt2");

			
			m_pDictionary->setObject(elem, "6");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("300"), "positionx");
			elem->setObject(CCString::create("360"), "positiony");
			elem->setObject(CCString::create("60"), "length");
			elem->setObject(CCString::create("32"), "width");
			elem->setObject(CCString::create("5"), "target");
			elem->setObject(CCString::create("4"), "related1");
			elem->setObject(CCString::create("1"), "wt1");
			elem->setObject(CCString::create("0"), "related2");
			elem->setObject(CCString::create("1"), "wt2");

			
			m_pDictionary->setObject(elem, "7");
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

	CCString* get_positionx_Value(const string& key)
	{
		return getValueOf(key, "positionx");
	}
	CCString* get_positionx_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "positionx");
	}

	CCString* get_positiony_Value(const string& key)
	{
		return getValueOf(key, "positiony");
	}
	CCString* get_positiony_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "positiony");
	}

	CCString* get_length_Value(const string& key)
	{
		return getValueOf(key, "length");
	}
	CCString* get_length_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "length");
	}

	CCString* get_width_Value(const string& key)
	{
		return getValueOf(key, "width");
	}
	CCString* get_width_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "width");
	}

	CCString* get_target_Value(const string& key)
	{
		return getValueOf(key, "target");
	}
	CCString* get_target_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "target");
	}

	CCString* get_related1_Value(const string& key)
	{
		return getValueOf(key, "related1");
	}
	CCString* get_related1_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "related1");
	}

	CCString* get_wt1_Value(const string& key)
	{
		return getValueOf(key, "wt1");
	}
	CCString* get_wt1_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "wt1");
	}

	CCString* get_related2_Value(const string& key)
	{
		return getValueOf(key, "related2");
	}
	CCString* get_related2_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "related2");
	}

	CCString* get_wt2_Value(const string& key)
	{
		return getValueOf(key, "wt2");
	}
	CCString* get_wt2_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "wt2");
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