#ifndef __DTUnit__
#define __DTUnit__
#include "cocos2d.h"
#include <string>

using namespace std;
USING_NS_CC;

class DTUnit
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
			
			elem->setObject(String::create("unit_1"), "name");
			elem->setObject(String::create("0"), "type");
			elem->setObject(String::create("unit0"), "resourceID");
			elem->setObject(String::create("CWarriorUnit0"), "className");
			elem->setObject(String::create("-9"), "x");
			elem->setObject(String::create("-15"), "y");
			elem->setObject(String::create("23"), "width");
			elem->setObject(String::create("43"), "hight");
			elem->setObject(String::create("1"), "gridWidth");
			elem->setObject(String::create("1"), "gridHeight");
			elem->setObject(String::create("120"), "hp");
			elem->setObject(String::create("10"), "atk");
			elem->setObject(String::create("1"), "def");
			elem->setObject(String::create("0"), "deftype");
			elem->setObject(String::create("1"), "dimension");
			elem->setObject(String::create("0"), "target");
			elem->setObject(String::create("4"), "radius");
			elem->setObject(String::create("3"), "speed");
			elem->setObject(String::create("1"), "rate");
			elem->setObject(String::create("1"), "skill0");
			elem->setObject(String::create("10001"), "skill1");
			elem->setObject(String::create(""), "skill2");
			elem->setObject(String::create(""), "skill3");
			elem->setObject(String::create(""), "skill4");
			elem->setObject(String::create(""), "skill5");

			
			m_pDictionary->setObject(elem, "1");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("unit_2"), "name");
			elem->setObject(String::create("0"), "type");
			elem->setObject(String::create("unit1"), "resourceID");
			elem->setObject(String::create("CWarriorUnit1"), "className");
			elem->setObject(String::create("-9"), "x");
			elem->setObject(String::create("-15"), "y");
			elem->setObject(String::create("15"), "width");
			elem->setObject(String::create("40"), "hight");
			elem->setObject(String::create("1"), "gridWidth");
			elem->setObject(String::create("1"), "gridHeight");
			elem->setObject(String::create("80"), "hp");
			elem->setObject(String::create("8"), "atk");
			elem->setObject(String::create("0"), "def");
			elem->setObject(String::create("0"), "deftype");
			elem->setObject(String::create("1"), "dimension");
			elem->setObject(String::create("0"), "target");
			elem->setObject(String::create("4"), "radius");
			elem->setObject(String::create("3"), "speed");
			elem->setObject(String::create("1"), "rate");
			elem->setObject(String::create("2"), "skill0");
			elem->setObject(String::create("10002"), "skill1");
			elem->setObject(String::create(""), "skill2");
			elem->setObject(String::create(""), "skill3");
			elem->setObject(String::create(""), "skill4");
			elem->setObject(String::create(""), "skill5");

			
			m_pDictionary->setObject(elem, "2");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("unit_3"), "name");
			elem->setObject(String::create("0"), "type");
			elem->setObject(String::create("unit2"), "resourceID");
			elem->setObject(String::create("CWarriorUnit2"), "className");
			elem->setObject(String::create("-9"), "x");
			elem->setObject(String::create("-15"), "y");
			elem->setObject(String::create("32"), "width");
			elem->setObject(String::create("37"), "hight");
			elem->setObject(String::create("2"), "gridWidth");
			elem->setObject(String::create("2"), "gridHeight");
			elem->setObject(String::create("250"), "hp");
			elem->setObject(String::create("32"), "atk");
			elem->setObject(String::create("2"), "def");
			elem->setObject(String::create("0"), "deftype");
			elem->setObject(String::create("1"), "dimension");
			elem->setObject(String::create("0"), "target");
			elem->setObject(String::create("4"), "radius");
			elem->setObject(String::create("2"), "speed");
			elem->setObject(String::create("0.5"), "rate");
			elem->setObject(String::create("3"), "skill0");
			elem->setObject(String::create("10003"), "skill1");
			elem->setObject(String::create(""), "skill2");
			elem->setObject(String::create(""), "skill3");
			elem->setObject(String::create(""), "skill4");
			elem->setObject(String::create(""), "skill5");

			
			m_pDictionary->setObject(elem, "3");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("unit_4"), "name");
			elem->setObject(String::create("0"), "type");
			elem->setObject(String::create("unit3"), "resourceID");
			elem->setObject(String::create("CWarriorUnit3"), "className");
			elem->setObject(String::create("-9"), "x");
			elem->setObject(String::create("-15"), "y");
			elem->setObject(String::create("47"), "width");
			elem->setObject(String::create("35"), "hight");
			elem->setObject(String::create("2"), "gridWidth");
			elem->setObject(String::create("2"), "gridHeight");
			elem->setObject(String::create("100"), "hp");
			elem->setObject(String::create("12"), "atk");
			elem->setObject(String::create("1"), "def");
			elem->setObject(String::create("0"), "deftype");
			elem->setObject(String::create("1"), "dimension");
			elem->setObject(String::create("0"), "target");
			elem->setObject(String::create("4"), "radius");
			elem->setObject(String::create("2"), "speed");
			elem->setObject(String::create("0.6"), "rate");
			elem->setObject(String::create("4"), "skill0");
			elem->setObject(String::create("10004"), "skill1");
			elem->setObject(String::create(""), "skill2");
			elem->setObject(String::create(""), "skill3");
			elem->setObject(String::create(""), "skill4");
			elem->setObject(String::create(""), "skill5");

			
			m_pDictionary->setObject(elem, "4");
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

	String* get_name_Value(const string& key)
	{
		return getValueOf(key, "name");
	}
	String* get_name_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "name");
	}

	String* get_type_Value(const string& key)
	{
		return getValueOf(key, "type");
	}
	String* get_type_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "type");
	}

	String* get_resourceID_Value(const string& key)
	{
		return getValueOf(key, "resourceID");
	}
	String* get_resourceID_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "resourceID");
	}

	String* get_className_Value(const string& key)
	{
		return getValueOf(key, "className");
	}
	String* get_className_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "className");
	}

	String* get_x_Value(const string& key)
	{
		return getValueOf(key, "x");
	}
	String* get_x_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "x");
	}

	String* get_y_Value(const string& key)
	{
		return getValueOf(key, "y");
	}
	String* get_y_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "y");
	}

	String* get_width_Value(const string& key)
	{
		return getValueOf(key, "width");
	}
	String* get_width_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "width");
	}

	String* get_hight_Value(const string& key)
	{
		return getValueOf(key, "hight");
	}
	String* get_hight_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "hight");
	}

	String* get_gridWidth_Value(const string& key)
	{
		return getValueOf(key, "gridWidth");
	}
	String* get_gridWidth_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "gridWidth");
	}

	String* get_gridHeight_Value(const string& key)
	{
		return getValueOf(key, "gridHeight");
	}
	String* get_gridHeight_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "gridHeight");
	}

	String* get_hp_Value(const string& key)
	{
		return getValueOf(key, "hp");
	}
	String* get_hp_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "hp");
	}

	String* get_atk_Value(const string& key)
	{
		return getValueOf(key, "atk");
	}
	String* get_atk_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "atk");
	}

	String* get_def_Value(const string& key)
	{
		return getValueOf(key, "def");
	}
	String* get_def_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "def");
	}

	String* get_deftype_Value(const string& key)
	{
		return getValueOf(key, "deftype");
	}
	String* get_deftype_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "deftype");
	}

	String* get_dimension_Value(const string& key)
	{
		return getValueOf(key, "dimension");
	}
	String* get_dimension_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "dimension");
	}

	String* get_target_Value(const string& key)
	{
		return getValueOf(key, "target");
	}
	String* get_target_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "target");
	}

	String* get_radius_Value(const string& key)
	{
		return getValueOf(key, "radius");
	}
	String* get_radius_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "radius");
	}

	String* get_speed_Value(const string& key)
	{
		return getValueOf(key, "speed");
	}
	String* get_speed_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "speed");
	}

	String* get_rate_Value(const string& key)
	{
		return getValueOf(key, "rate");
	}
	String* get_rate_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "rate");
	}

	String* get_skill0_Value(const string& key)
	{
		return getValueOf(key, "skill0");
	}
	String* get_skill0_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "skill0");
	}

	String* get_skill1_Value(const string& key)
	{
		return getValueOf(key, "skill1");
	}
	String* get_skill1_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "skill1");
	}

	String* get_skill2_Value(const string& key)
	{
		return getValueOf(key, "skill2");
	}
	String* get_skill2_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "skill2");
	}

	String* get_skill3_Value(const string& key)
	{
		return getValueOf(key, "skill3");
	}
	String* get_skill3_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "skill3");
	}

	String* get_skill4_Value(const string& key)
	{
		return getValueOf(key, "skill4");
	}
	String* get_skill4_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "skill4");
	}

	String* get_skill5_Value(const string& key)
	{
		return getValueOf(key, "skill5");
	}
	String* get_skill5_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "skill5");
	}



protected:
	DTUnit():m_pDictionary(nullptr)
	{}
	~DTUnit()
	{
		CC_SAFE_RELEASE(m_pDictionary);
	}
	
private:
	Dictionary* m_pDictionary;
};


#endif	// __DTUnit__