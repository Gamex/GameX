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
	CCDictionary* getRoot() const
	{
		return m_pDictionary;
	}
	void loadData2CCDictionary()
    {
        if (NULL == m_pDictionary)
        {
            m_pDictionary = CCDictionary::create();
            CC_SAFE_RETAIN(m_pDictionary);
        }

		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("unitname_1"), "name");
			elem->setObject(CCString::create("0"), "type");
			elem->setObject(CCString::create("Unit0"), "resourceID");
			elem->setObject(CCString::create("-9"), "x");
			elem->setObject(CCString::create("-15"), "y");
			elem->setObject(CCString::create("19"), "width");
			elem->setObject(CCString::create("35"), "hight");
			elem->setObject(CCString::create("1"), "gridWidth");
			elem->setObject(CCString::create("1"), "gridHeight");
			elem->setObject(CCString::create("5000"), "hp");
			elem->setObject(CCString::create("20"), "atk");
			elem->setObject(CCString::create("2"), "def");
			elem->setObject(CCString::create("1"), "dimension");
			elem->setObject(CCString::create("0"), "target");
			elem->setObject(CCString::create("0"), "radius");
			elem->setObject(CCString::create("0"), "speed");
			elem->setObject(CCString::create("1"), "skill0");
			elem->setObject(CCString::create(""), "skill1");
			elem->setObject(CCString::create(""), "skill2");
			elem->setObject(CCString::create(""), "skill3");
			elem->setObject(CCString::create(""), "skill4");
			elem->setObject(CCString::create(""), "skill5");

			
			m_pDictionary->setObject(elem, "0");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("unitname_1"), "name");
			elem->setObject(CCString::create("0"), "type");
			elem->setObject(CCString::create("Unit1"), "resourceID");
			elem->setObject(CCString::create("-9"), "x");
			elem->setObject(CCString::create("-15"), "y");
			elem->setObject(CCString::create("19"), "width");
			elem->setObject(CCString::create("35"), "hight");
			elem->setObject(CCString::create("1"), "gridWidth");
			elem->setObject(CCString::create("1"), "gridHeight");
			elem->setObject(CCString::create("5000"), "hp");
			elem->setObject(CCString::create("20"), "atk");
			elem->setObject(CCString::create("2"), "def");
			elem->setObject(CCString::create("1"), "dimension");
			elem->setObject(CCString::create("0"), "target");
			elem->setObject(CCString::create("0"), "radius");
			elem->setObject(CCString::create("0"), "speed");
			elem->setObject(CCString::create("1"), "skill0");
			elem->setObject(CCString::create(""), "skill1");
			elem->setObject(CCString::create(""), "skill2");
			elem->setObject(CCString::create(""), "skill3");
			elem->setObject(CCString::create(""), "skill4");
			elem->setObject(CCString::create(""), "skill5");

			
			m_pDictionary->setObject(elem, "1");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("unitname_2"), "name");
			elem->setObject(CCString::create("0"), "type");
			elem->setObject(CCString::create("Unit2"), "resourceID");
			elem->setObject(CCString::create("-9"), "x");
			elem->setObject(CCString::create("-15"), "y");
			elem->setObject(CCString::create("19"), "width");
			elem->setObject(CCString::create("35"), "hight");
			elem->setObject(CCString::create("2"), "gridWidth");
			elem->setObject(CCString::create("2"), "gridHeight");
			elem->setObject(CCString::create("1000"), "hp");
			elem->setObject(CCString::create("10"), "atk");
			elem->setObject(CCString::create("1"), "def");
			elem->setObject(CCString::create("1"), "dimension");
			elem->setObject(CCString::create("0"), "target");
			elem->setObject(CCString::create("0"), "radius");
			elem->setObject(CCString::create("0"), "speed");
			elem->setObject(CCString::create("2"), "skill0");
			elem->setObject(CCString::create(""), "skill1");
			elem->setObject(CCString::create(""), "skill2");
			elem->setObject(CCString::create(""), "skill3");
			elem->setObject(CCString::create(""), "skill4");
			elem->setObject(CCString::create(""), "skill5");

			
			m_pDictionary->setObject(elem, "2");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("unitname_3"), "name");
			elem->setObject(CCString::create("0"), "type");
			elem->setObject(CCString::create("Unit2"), "resourceID");
			elem->setObject(CCString::create("-9"), "x");
			elem->setObject(CCString::create("-15"), "y");
			elem->setObject(CCString::create("19"), "width");
			elem->setObject(CCString::create("35"), "hight");
			elem->setObject(CCString::create("2"), "gridWidth");
			elem->setObject(CCString::create("2"), "gridHeight");
			elem->setObject(CCString::create("1000"), "hp");
			elem->setObject(CCString::create("10"), "atk");
			elem->setObject(CCString::create("1"), "def");
			elem->setObject(CCString::create("1"), "dimension");
			elem->setObject(CCString::create("0"), "target");
			elem->setObject(CCString::create("0"), "radius");
			elem->setObject(CCString::create("0"), "speed");
			elem->setObject(CCString::create("0"), "skill0");
			elem->setObject(CCString::create("10001"), "skill1");
			elem->setObject(CCString::create(""), "skill2");
			elem->setObject(CCString::create(""), "skill3");
			elem->setObject(CCString::create(""), "skill4");
			elem->setObject(CCString::create(""), "skill5");

			
			m_pDictionary->setObject(elem, "3");
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

	CCString* get_name_Value(const string& key)
	{
		return getValueOf(key, "name");
	}
	CCString* get_name_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "name");
	}

	CCString* get_type_Value(const string& key)
	{
		return getValueOf(key, "type");
	}
	CCString* get_type_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "type");
	}

	CCString* get_resourceID_Value(const string& key)
	{
		return getValueOf(key, "resourceID");
	}
	CCString* get_resourceID_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "resourceID");
	}

	CCString* get_x_Value(const string& key)
	{
		return getValueOf(key, "x");
	}
	CCString* get_x_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "x");
	}

	CCString* get_y_Value(const string& key)
	{
		return getValueOf(key, "y");
	}
	CCString* get_y_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "y");
	}

	CCString* get_width_Value(const string& key)
	{
		return getValueOf(key, "width");
	}
	CCString* get_width_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "width");
	}

	CCString* get_hight_Value(const string& key)
	{
		return getValueOf(key, "hight");
	}
	CCString* get_hight_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "hight");
	}

	CCString* get_gridWidth_Value(const string& key)
	{
		return getValueOf(key, "gridWidth");
	}
	CCString* get_gridWidth_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "gridWidth");
	}

	CCString* get_gridHeight_Value(const string& key)
	{
		return getValueOf(key, "gridHeight");
	}
	CCString* get_gridHeight_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "gridHeight");
	}

	CCString* get_hp_Value(const string& key)
	{
		return getValueOf(key, "hp");
	}
	CCString* get_hp_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "hp");
	}

	CCString* get_atk_Value(const string& key)
	{
		return getValueOf(key, "atk");
	}
	CCString* get_atk_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "atk");
	}

	CCString* get_def_Value(const string& key)
	{
		return getValueOf(key, "def");
	}
	CCString* get_def_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "def");
	}

	CCString* get_dimension_Value(const string& key)
	{
		return getValueOf(key, "dimension");
	}
	CCString* get_dimension_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "dimension");
	}

	CCString* get_target_Value(const string& key)
	{
		return getValueOf(key, "target");
	}
	CCString* get_target_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "target");
	}

	CCString* get_radius_Value(const string& key)
	{
		return getValueOf(key, "radius");
	}
	CCString* get_radius_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "radius");
	}

	CCString* get_speed_Value(const string& key)
	{
		return getValueOf(key, "speed");
	}
	CCString* get_speed_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "speed");
	}

	CCString* get_skill0_Value(const string& key)
	{
		return getValueOf(key, "skill0");
	}
	CCString* get_skill0_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "skill0");
	}

	CCString* get_skill1_Value(const string& key)
	{
		return getValueOf(key, "skill1");
	}
	CCString* get_skill1_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "skill1");
	}

	CCString* get_skill2_Value(const string& key)
	{
		return getValueOf(key, "skill2");
	}
	CCString* get_skill2_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "skill2");
	}

	CCString* get_skill3_Value(const string& key)
	{
		return getValueOf(key, "skill3");
	}
	CCString* get_skill3_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "skill3");
	}

	CCString* get_skill4_Value(const string& key)
	{
		return getValueOf(key, "skill4");
	}
	CCString* get_skill4_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "skill4");
	}

	CCString* get_skill5_Value(const string& key)
	{
		return getValueOf(key, "skill5");
	}
	CCString* get_skill5_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "skill5");
	}



protected:
	DTUnit():m_pDictionary(NULL)
	{}
	~DTUnit()
	{
		CC_SAFE_RELEASE(m_pDictionary);
	}
	
private:
	CCDictionary* m_pDictionary;
};


#endif	// __DTUnit__