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
	Dictionary* getRoot() const
	{
		return m_pDictionary;
	}
	void loadData2CCDictionary()
    {
        if (nullptr == m_pDictionary)
        {
            m_pDictionary = Dictionary::create();
            CC_SAFE_RETAIN(m_pDictionary);
        }

		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("600"), "positionx");
			elem->setObject(String::create("32"), "positiony");
			elem->setObject(String::create("60"), "length");
			elem->setObject(String::create("32"), "width");
			elem->setObject(String::create("1"), "target");
			elem->setObject(String::create("0"), "related1");
			elem->setObject(String::create("1"), "wt1");
			elem->setObject(String::create("2"), "related2");
			elem->setObject(String::create("1"), "wt2");

			
			m_pDictionary->setObject(elem, "1");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("600"), "positionx");
			elem->setObject(String::create("96"), "positiony");
			elem->setObject(String::create("60"), "length");
			elem->setObject(String::create("32"), "width");
			elem->setObject(String::create("2"), "target");
			elem->setObject(String::create("1"), "related1");
			elem->setObject(String::create("1"), "wt1");
			elem->setObject(String::create("3"), "related2");
			elem->setObject(String::create("1"), "wt2");

			
			m_pDictionary->setObject(elem, "2");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("600"), "positionx");
			elem->setObject(String::create("160"), "positiony");
			elem->setObject(String::create("60"), "length");
			elem->setObject(String::create("32"), "width");
			elem->setObject(String::create("3"), "target");
			elem->setObject(String::create("2"), "related1");
			elem->setObject(String::create("1"), "wt1");
			elem->setObject(String::create("4"), "related2");
			elem->setObject(String::create("1"), "wt2");

			
			m_pDictionary->setObject(elem, "3");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("600"), "positionx");
			elem->setObject(String::create("224"), "positiony");
			elem->setObject(String::create("60"), "length");
			elem->setObject(String::create("32"), "width");
			elem->setObject(String::create("4"), "target");
			elem->setObject(String::create("3"), "related1");
			elem->setObject(String::create("1"), "wt1");
			elem->setObject(String::create("5"), "related2");
			elem->setObject(String::create("1"), "wt2");

			
			m_pDictionary->setObject(elem, "4");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("600"), "positionx");
			elem->setObject(String::create("288"), "positiony");
			elem->setObject(String::create("60"), "length");
			elem->setObject(String::create("32"), "width");
			elem->setObject(String::create("5"), "target");
			elem->setObject(String::create("4"), "related1");
			elem->setObject(String::create("1"), "wt1");
			elem->setObject(String::create("0"), "related2");
			elem->setObject(String::create("1"), "wt2");

			
			m_pDictionary->setObject(elem, "5");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("300"), "positionx");
			elem->setObject(String::create("-40"), "positiony");
			elem->setObject(String::create("60"), "length");
			elem->setObject(String::create("32"), "width");
			elem->setObject(String::create("1"), "target");
			elem->setObject(String::create("0"), "related1");
			elem->setObject(String::create("1"), "wt1");
			elem->setObject(String::create("2"), "related2");
			elem->setObject(String::create("1"), "wt2");

			
			m_pDictionary->setObject(elem, "6");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("300"), "positionx");
			elem->setObject(String::create("360"), "positiony");
			elem->setObject(String::create("60"), "length");
			elem->setObject(String::create("32"), "width");
			elem->setObject(String::create("5"), "target");
			elem->setObject(String::create("4"), "related1");
			elem->setObject(String::create("1"), "wt1");
			elem->setObject(String::create("0"), "related2");
			elem->setObject(String::create("1"), "wt2");

			
			m_pDictionary->setObject(elem, "7");
		}

    }
        
    Dictionary* getData(const string& key)
    {
        CC_ASSERT(m_pDictionary);
        return dynamic_cast<Dictionary*>(m_pDictionary->objectForKey(key));
    }

    String* getValueOf(const string& key, const string& subKey)
    {
        CC_ASSERT(m_pDictionary);
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

	String* get_positionx_Value(const string& key)
	{
		return getValueOf(key, "positionx");
	}
	String* get_positionx_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "positionx");
	}

	String* get_positiony_Value(const string& key)
	{
		return getValueOf(key, "positiony");
	}
	String* get_positiony_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "positiony");
	}

	String* get_length_Value(const string& key)
	{
		return getValueOf(key, "length");
	}
	String* get_length_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "length");
	}

	String* get_width_Value(const string& key)
	{
		return getValueOf(key, "width");
	}
	String* get_width_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "width");
	}

	String* get_target_Value(const string& key)
	{
		return getValueOf(key, "target");
	}
	String* get_target_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "target");
	}

	String* get_related1_Value(const string& key)
	{
		return getValueOf(key, "related1");
	}
	String* get_related1_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "related1");
	}

	String* get_wt1_Value(const string& key)
	{
		return getValueOf(key, "wt1");
	}
	String* get_wt1_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "wt1");
	}

	String* get_related2_Value(const string& key)
	{
		return getValueOf(key, "related2");
	}
	String* get_related2_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "related2");
	}

	String* get_wt2_Value(const string& key)
	{
		return getValueOf(key, "wt2");
	}
	String* get_wt2_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "wt2");
	}



protected:
	DTScene():m_pDictionary(nullptr)
	{}
	~DTScene()
	{
		CC_SAFE_RELEASE(m_pDictionary);
	}
	
private:
	Dictionary* m_pDictionary;
};


#endif	// __DTScene__