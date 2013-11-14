#ifndef __DTSkill__
#define __DTSkill__
#include "cocos2d.h"
#include <string>

using namespace std;
USING_NS_CC;

class DTSkill
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
			
			elem->setObject(String::create("skill_1"), "name");
			elem->setObject(String::create("CSkillMeleeAttack"), "className");
			elem->setObject(String::create("0"), "cd");
			elem->setObject(String::create("0"), "trigger");
			elem->setObject(String::create("0"), "param");
			elem->setObject(String::create("1"), "target");
			elem->setObject(String::create("1"), "dimension");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("2.25"), "range");
			elem->setObject(String::create("0"), "angle");
			elem->setObject(String::create("0"), "bullet");
			elem->setObject(String::create("0"), "speed");
			elem->setObject(String::create("0"), "resourceID");
			elem->setObject(String::create("atk"), "animation");
			elem->setObject(String::create(""), "atk_se");
			elem->setObject(String::create(""), "hit_eft");
			elem->setObject(String::create(""), "buff1");
			elem->setObject(String::create(""), "buff2");
			elem->setObject(String::create(""), "buff3");
			elem->setObject(String::create("1000"), "debuff1");
			elem->setObject(String::create(""), "debuff2");
			elem->setObject(String::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "1");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("skill_2"), "name");
			elem->setObject(String::create("CSkillMarineGunAttack"), "className");
			elem->setObject(String::create("0"), "cd");
			elem->setObject(String::create("0"), "trigger");
			elem->setObject(String::create("0"), "param");
			elem->setObject(String::create("1"), "target");
			elem->setObject(String::create("3"), "dimension");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("25"), "range");
			elem->setObject(String::create("0"), "angle");
			elem->setObject(String::create("2"), "bullet");
			elem->setObject(String::create("100"), "speed");
			elem->setObject(String::create("bullet_line_1.png"), "resourceID");
			elem->setObject(String::create("atk"), "animation");
			elem->setObject(String::create(""), "atk_se");
			elem->setObject(String::create(""), "hit_eft");
			elem->setObject(String::create(""), "buff1");
			elem->setObject(String::create(""), "buff2");
			elem->setObject(String::create(""), "buff3");
			elem->setObject(String::create("1000"), "debuff1");
			elem->setObject(String::create(""), "debuff2");
			elem->setObject(String::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "2");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("skill_3"), "name");
			elem->setObject(String::create("CSkillMeleeAttack"), "className");
			elem->setObject(String::create("0"), "cd");
			elem->setObject(String::create("0"), "trigger");
			elem->setObject(String::create("0"), "param");
			elem->setObject(String::create("1"), "target");
			elem->setObject(String::create("1"), "dimension");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("2.25"), "range");
			elem->setObject(String::create("0"), "angle");
			elem->setObject(String::create("0"), "bullet");
			elem->setObject(String::create("0"), "speed");
			elem->setObject(String::create("0"), "resourceID");
			elem->setObject(String::create("atk"), "animation");
			elem->setObject(String::create(""), "atk_se");
			elem->setObject(String::create(""), "hit_eft");
			elem->setObject(String::create(""), "buff1");
			elem->setObject(String::create(""), "buff2");
			elem->setObject(String::create(""), "buff3");
			elem->setObject(String::create("1000"), "debuff1");
			elem->setObject(String::create(""), "debuff2");
			elem->setObject(String::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "3");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("skill_4"), "name");
			elem->setObject(String::create("CSkillComp"), "className");
			elem->setObject(String::create("0"), "cd");
			elem->setObject(String::create("0"), "trigger");
			elem->setObject(String::create("0"), "param");
			elem->setObject(String::create("1"), "target");
			elem->setObject(String::create("1"), "dimension");
			elem->setObject(String::create("3"), "type");
			elem->setObject(String::create("9"), "range");
			elem->setObject(String::create("90"), "angle");
			elem->setObject(String::create("0"), "bullet");
			elem->setObject(String::create("0"), "speed");
			elem->setObject(String::create("0"), "resourceID");
			elem->setObject(String::create("atk"), "animation");
			elem->setObject(String::create(""), "atk_se");
			elem->setObject(String::create(""), "hit_eft");
			elem->setObject(String::create(""), "buff1");
			elem->setObject(String::create(""), "buff2");
			elem->setObject(String::create(""), "buff3");
			elem->setObject(String::create("1000"), "debuff1");
			elem->setObject(String::create(""), "debuff2");
			elem->setObject(String::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "4");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("skill_10001"), "name");
			elem->setObject(String::create("CSkillComp"), "className");
			elem->setObject(String::create("0"), "cd");
			elem->setObject(String::create("1"), "trigger");
			elem->setObject(String::create("3"), "param");
			elem->setObject(String::create("3"), "target");
			elem->setObject(String::create("0"), "dimension");
			elem->setObject(String::create("0"), "type");
			elem->setObject(String::create("0"), "range");
			elem->setObject(String::create("0"), "angle");
			elem->setObject(String::create("0"), "bullet");
			elem->setObject(String::create("0"), "speed");
			elem->setObject(String::create("0"), "resourceID");
			elem->setObject(String::create("skill1"), "animation");
			elem->setObject(String::create(""), "atk_se");
			elem->setObject(String::create(""), "hit_eft");
			elem->setObject(String::create("24002"), "buff1");
			elem->setObject(String::create(""), "buff2");
			elem->setObject(String::create(""), "buff3");
			elem->setObject(String::create(""), "debuff1");
			elem->setObject(String::create(""), "debuff2");
			elem->setObject(String::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "10001");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("skill_10002"), "name");
			elem->setObject(String::create("CSkillComp"), "className");
			elem->setObject(String::create("10000"), "cd");
			elem->setObject(String::create("0"), "trigger");
			elem->setObject(String::create("0"), "param");
			elem->setObject(String::create("3"), "target");
			elem->setObject(String::create("0"), "dimension");
			elem->setObject(String::create("0"), "type");
			elem->setObject(String::create("0"), "range");
			elem->setObject(String::create("0"), "angle");
			elem->setObject(String::create("0"), "bullet");
			elem->setObject(String::create("0"), "speed");
			elem->setObject(String::create("0"), "resourceID");
			elem->setObject(String::create("skill1"), "animation");
			elem->setObject(String::create(""), "atk_se");
			elem->setObject(String::create(""), "hit_eft");
			elem->setObject(String::create("23001"), "buff1");
			elem->setObject(String::create("24001"), "buff2");
			elem->setObject(String::create(""), "buff3");
			elem->setObject(String::create(""), "debuff1");
			elem->setObject(String::create(""), "debuff2");
			elem->setObject(String::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "10002");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("skill_10003"), "name");
			elem->setObject(String::create("CSkillComp"), "className");
			elem->setObject(String::create("10000"), "cd");
			elem->setObject(String::create("0"), "trigger");
			elem->setObject(String::create("0"), "param");
			elem->setObject(String::create("1"), "target");
			elem->setObject(String::create("1"), "dimension");
			elem->setObject(String::create("2"), "type");
			elem->setObject(String::create("4"), "range");
			elem->setObject(String::create("0"), "angle");
			elem->setObject(String::create("0"), "bullet");
			elem->setObject(String::create("0"), "speed");
			elem->setObject(String::create("0"), "resourceID");
			elem->setObject(String::create("skill1"), "animation");
			elem->setObject(String::create(""), "atk_se");
			elem->setObject(String::create(""), "hit_eft");
			elem->setObject(String::create(""), "buff1");
			elem->setObject(String::create(""), "buff2");
			elem->setObject(String::create(""), "buff3");
			elem->setObject(String::create(""), "debuff1");
			elem->setObject(String::create(""), "debuff2");
			elem->setObject(String::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "10003");
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("skill_10004"), "name");
			elem->setObject(String::create("CSkillComp"), "className");
			elem->setObject(String::create("10000"), "cd");
			elem->setObject(String::create("2"), "trigger");
			elem->setObject(String::create("0"), "param");
			elem->setObject(String::create("1"), "target");
			elem->setObject(String::create("1"), "dimension");
			elem->setObject(String::create("2"), "type");
			elem->setObject(String::create("9"), "range");
			elem->setObject(String::create("0"), "angle");
			elem->setObject(String::create("0"), "bullet");
			elem->setObject(String::create("0"), "speed");
			elem->setObject(String::create("0"), "resourceID");
			elem->setObject(String::create("skill1"), "animation");
			elem->setObject(String::create(""), "atk_se");
			elem->setObject(String::create(""), "hit_eft");
			elem->setObject(String::create(""), "buff1");
			elem->setObject(String::create(""), "buff2");
			elem->setObject(String::create(""), "buff3");
			elem->setObject(String::create("1000"), "debuff1");
			elem->setObject(String::create(""), "debuff2");
			elem->setObject(String::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "10004");
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

	String* get_className_Value(const string& key)
	{
		return getValueOf(key, "className");
	}
	String* get_className_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "className");
	}

	String* get_cd_Value(const string& key)
	{
		return getValueOf(key, "cd");
	}
	String* get_cd_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "cd");
	}

	String* get_trigger_Value(const string& key)
	{
		return getValueOf(key, "trigger");
	}
	String* get_trigger_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "trigger");
	}

	String* get_param_Value(const string& key)
	{
		return getValueOf(key, "param");
	}
	String* get_param_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "param");
	}

	String* get_target_Value(const string& key)
	{
		return getValueOf(key, "target");
	}
	String* get_target_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "target");
	}

	String* get_dimension_Value(const string& key)
	{
		return getValueOf(key, "dimension");
	}
	String* get_dimension_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "dimension");
	}

	String* get_type_Value(const string& key)
	{
		return getValueOf(key, "type");
	}
	String* get_type_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "type");
	}

	String* get_range_Value(const string& key)
	{
		return getValueOf(key, "range");
	}
	String* get_range_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "range");
	}

	String* get_angle_Value(const string& key)
	{
		return getValueOf(key, "angle");
	}
	String* get_angle_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "angle");
	}

	String* get_bullet_Value(const string& key)
	{
		return getValueOf(key, "bullet");
	}
	String* get_bullet_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "bullet");
	}

	String* get_speed_Value(const string& key)
	{
		return getValueOf(key, "speed");
	}
	String* get_speed_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "speed");
	}

	String* get_resourceID_Value(const string& key)
	{
		return getValueOf(key, "resourceID");
	}
	String* get_resourceID_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "resourceID");
	}

	String* get_animation_Value(const string& key)
	{
		return getValueOf(key, "animation");
	}
	String* get_animation_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "animation");
	}

	String* get_atk_se_Value(const string& key)
	{
		return getValueOf(key, "atk_se");
	}
	String* get_atk_se_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "atk_se");
	}

	String* get_hit_eft_Value(const string& key)
	{
		return getValueOf(key, "hit_eft");
	}
	String* get_hit_eft_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "hit_eft");
	}

	String* get_buff1_Value(const string& key)
	{
		return getValueOf(key, "buff1");
	}
	String* get_buff1_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "buff1");
	}

	String* get_buff2_Value(const string& key)
	{
		return getValueOf(key, "buff2");
	}
	String* get_buff2_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "buff2");
	}

	String* get_buff3_Value(const string& key)
	{
		return getValueOf(key, "buff3");
	}
	String* get_buff3_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "buff3");
	}

	String* get_debuff1_Value(const string& key)
	{
		return getValueOf(key, "debuff1");
	}
	String* get_debuff1_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "debuff1");
	}

	String* get_debuff2_Value(const string& key)
	{
		return getValueOf(key, "debuff2");
	}
	String* get_debuff2_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "debuff2");
	}

	String* get_debuff3_Value(const string& key)
	{
		return getValueOf(key, "debuff3");
	}
	String* get_debuff3_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "debuff3");
	}



protected:
	DTSkill():m_pDictionary(nullptr)
	{}
	~DTSkill()
	{
		CC_SAFE_RELEASE(m_pDictionary);
	}
	
private:
	Dictionary* m_pDictionary;
};


#endif	// __DTSkill__