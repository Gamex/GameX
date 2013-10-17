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
			
			elem->setObject(CCString::create("skill_1"), "name");
			elem->setObject(CCString::create("CSkillComp"), "className");
			elem->setObject(CCString::create("0"), "cd");
			elem->setObject(CCString::create("0"), "trigger");
			elem->setObject(CCString::create("0"), "param");
			elem->setObject(CCString::create("1"), "target");
			elem->setObject(CCString::create("1"), "dimension");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("2.25"), "range");
			elem->setObject(CCString::create("0"), "angle");
			elem->setObject(CCString::create("0"), "bullet");
			elem->setObject(CCString::create("0"), "speed");
			elem->setObject(CCString::create("0"), "resourceID");
			elem->setObject(CCString::create("atk"), "animation");
			elem->setObject(CCString::create(""), "atk_se");
			elem->setObject(CCString::create(""), "hit_eft");
			elem->setObject(CCString::create(""), "buff1");
			elem->setObject(CCString::create(""), "buff2");
			elem->setObject(CCString::create(""), "buff3");
			elem->setObject(CCString::create("1000"), "debuff1");
			elem->setObject(CCString::create(""), "debuff2");
			elem->setObject(CCString::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "1");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("skill_2"), "name");
			elem->setObject(CCString::create("CSkillComp"), "className");
			elem->setObject(CCString::create("0"), "cd");
			elem->setObject(CCString::create("0"), "trigger");
			elem->setObject(CCString::create("0"), "param");
			elem->setObject(CCString::create("1"), "target");
			elem->setObject(CCString::create("3"), "dimension");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("25"), "range");
			elem->setObject(CCString::create("0"), "angle");
			elem->setObject(CCString::create("2"), "bullet");
			elem->setObject(CCString::create("100"), "speed");
			elem->setObject(CCString::create("bullet_line_1.png"), "resourceID");
			elem->setObject(CCString::create("atk"), "animation");
			elem->setObject(CCString::create(""), "atk_se");
			elem->setObject(CCString::create(""), "hit_eft");
			elem->setObject(CCString::create(""), "buff1");
			elem->setObject(CCString::create(""), "buff2");
			elem->setObject(CCString::create(""), "buff3");
			elem->setObject(CCString::create("1000"), "debuff1");
			elem->setObject(CCString::create(""), "debuff2");
			elem->setObject(CCString::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "2");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("skill_3"), "name");
			elem->setObject(CCString::create("CSkillComp"), "className");
			elem->setObject(CCString::create("0"), "cd");
			elem->setObject(CCString::create("0"), "trigger");
			elem->setObject(CCString::create("0"), "param");
			elem->setObject(CCString::create("1"), "target");
			elem->setObject(CCString::create("1"), "dimension");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("2.25"), "range");
			elem->setObject(CCString::create("0"), "angle");
			elem->setObject(CCString::create("0"), "bullet");
			elem->setObject(CCString::create("0"), "speed");
			elem->setObject(CCString::create("0"), "resourceID");
			elem->setObject(CCString::create("atk"), "animation");
			elem->setObject(CCString::create(""), "atk_se");
			elem->setObject(CCString::create(""), "hit_eft");
			elem->setObject(CCString::create(""), "buff1");
			elem->setObject(CCString::create(""), "buff2");
			elem->setObject(CCString::create(""), "buff3");
			elem->setObject(CCString::create("1000"), "debuff1");
			elem->setObject(CCString::create(""), "debuff2");
			elem->setObject(CCString::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "3");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("skill_4"), "name");
			elem->setObject(CCString::create("CSkillComp"), "className");
			elem->setObject(CCString::create("0"), "cd");
			elem->setObject(CCString::create("0"), "trigger");
			elem->setObject(CCString::create("0"), "param");
			elem->setObject(CCString::create("1"), "target");
			elem->setObject(CCString::create("1"), "dimension");
			elem->setObject(CCString::create("3"), "type");
			elem->setObject(CCString::create("9"), "range");
			elem->setObject(CCString::create("90"), "angle");
			elem->setObject(CCString::create("0"), "bullet");
			elem->setObject(CCString::create("0"), "speed");
			elem->setObject(CCString::create("0"), "resourceID");
			elem->setObject(CCString::create("atk"), "animation");
			elem->setObject(CCString::create(""), "atk_se");
			elem->setObject(CCString::create(""), "hit_eft");
			elem->setObject(CCString::create(""), "buff1");
			elem->setObject(CCString::create(""), "buff2");
			elem->setObject(CCString::create(""), "buff3");
			elem->setObject(CCString::create("1000"), "debuff1");
			elem->setObject(CCString::create(""), "debuff2");
			elem->setObject(CCString::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "4");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("skill_10001"), "name");
			elem->setObject(CCString::create("CSkillComp"), "className");
			elem->setObject(CCString::create("0"), "cd");
			elem->setObject(CCString::create("1"), "trigger");
			elem->setObject(CCString::create("3"), "param");
			elem->setObject(CCString::create("3"), "target");
			elem->setObject(CCString::create("0"), "dimension");
			elem->setObject(CCString::create("0"), "type");
			elem->setObject(CCString::create("0"), "range");
			elem->setObject(CCString::create("0"), "angle");
			elem->setObject(CCString::create("0"), "bullet");
			elem->setObject(CCString::create("0"), "speed");
			elem->setObject(CCString::create("0"), "resourceID");
			elem->setObject(CCString::create("skill1"), "animation");
			elem->setObject(CCString::create(""), "atk_se");
			elem->setObject(CCString::create(""), "hit_eft");
			elem->setObject(CCString::create("24002"), "buff1");
			elem->setObject(CCString::create(""), "buff2");
			elem->setObject(CCString::create(""), "buff3");
			elem->setObject(CCString::create(""), "debuff1");
			elem->setObject(CCString::create(""), "debuff2");
			elem->setObject(CCString::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "10001");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("skill_10002"), "name");
			elem->setObject(CCString::create("CSkillComp"), "className");
			elem->setObject(CCString::create("10000"), "cd");
			elem->setObject(CCString::create("0"), "trigger");
			elem->setObject(CCString::create("0"), "param");
			elem->setObject(CCString::create("3"), "target");
			elem->setObject(CCString::create("0"), "dimension");
			elem->setObject(CCString::create("0"), "type");
			elem->setObject(CCString::create("0"), "range");
			elem->setObject(CCString::create("0"), "angle");
			elem->setObject(CCString::create("0"), "bullet");
			elem->setObject(CCString::create("0"), "speed");
			elem->setObject(CCString::create("0"), "resourceID");
			elem->setObject(CCString::create("skill1"), "animation");
			elem->setObject(CCString::create(""), "atk_se");
			elem->setObject(CCString::create(""), "hit_eft");
			elem->setObject(CCString::create("23001"), "buff1");
			elem->setObject(CCString::create("24001"), "buff2");
			elem->setObject(CCString::create(""), "buff3");
			elem->setObject(CCString::create(""), "debuff1");
			elem->setObject(CCString::create(""), "debuff2");
			elem->setObject(CCString::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "10002");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("skill_10003"), "name");
			elem->setObject(CCString::create("CSkillComp"), "className");
			elem->setObject(CCString::create("10000"), "cd");
			elem->setObject(CCString::create("0"), "trigger");
			elem->setObject(CCString::create("0"), "param");
			elem->setObject(CCString::create("1"), "target");
			elem->setObject(CCString::create("1"), "dimension");
			elem->setObject(CCString::create("2"), "type");
			elem->setObject(CCString::create("4"), "range");
			elem->setObject(CCString::create("0"), "angle");
			elem->setObject(CCString::create("0"), "bullet");
			elem->setObject(CCString::create("0"), "speed");
			elem->setObject(CCString::create("0"), "resourceID");
			elem->setObject(CCString::create("skill1"), "animation");
			elem->setObject(CCString::create(""), "atk_se");
			elem->setObject(CCString::create(""), "hit_eft");
			elem->setObject(CCString::create(""), "buff1");
			elem->setObject(CCString::create(""), "buff2");
			elem->setObject(CCString::create(""), "buff3");
			elem->setObject(CCString::create(""), "debuff1");
			elem->setObject(CCString::create(""), "debuff2");
			elem->setObject(CCString::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "10003");
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("skill_10004"), "name");
			elem->setObject(CCString::create("CSkillComp"), "className");
			elem->setObject(CCString::create("10000"), "cd");
			elem->setObject(CCString::create("2"), "trigger");
			elem->setObject(CCString::create("0"), "param");
			elem->setObject(CCString::create("1"), "target");
			elem->setObject(CCString::create("1"), "dimension");
			elem->setObject(CCString::create("2"), "type");
			elem->setObject(CCString::create("9"), "range");
			elem->setObject(CCString::create("0"), "angle");
			elem->setObject(CCString::create("0"), "bullet");
			elem->setObject(CCString::create("0"), "speed");
			elem->setObject(CCString::create("0"), "resourceID");
			elem->setObject(CCString::create("skill1"), "animation");
			elem->setObject(CCString::create(""), "atk_se");
			elem->setObject(CCString::create(""), "hit_eft");
			elem->setObject(CCString::create(""), "buff1");
			elem->setObject(CCString::create(""), "buff2");
			elem->setObject(CCString::create(""), "buff3");
			elem->setObject(CCString::create("1000"), "debuff1");
			elem->setObject(CCString::create(""), "debuff2");
			elem->setObject(CCString::create(""), "debuff3");

			
			m_pDictionary->setObject(elem, "10004");
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

	CCString* get_className_Value(const string& key)
	{
		return getValueOf(key, "className");
	}
	CCString* get_className_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "className");
	}

	CCString* get_cd_Value(const string& key)
	{
		return getValueOf(key, "cd");
	}
	CCString* get_cd_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "cd");
	}

	CCString* get_trigger_Value(const string& key)
	{
		return getValueOf(key, "trigger");
	}
	CCString* get_trigger_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "trigger");
	}

	CCString* get_param_Value(const string& key)
	{
		return getValueOf(key, "param");
	}
	CCString* get_param_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "param");
	}

	CCString* get_target_Value(const string& key)
	{
		return getValueOf(key, "target");
	}
	CCString* get_target_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "target");
	}

	CCString* get_dimension_Value(const string& key)
	{
		return getValueOf(key, "dimension");
	}
	CCString* get_dimension_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "dimension");
	}

	CCString* get_type_Value(const string& key)
	{
		return getValueOf(key, "type");
	}
	CCString* get_type_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "type");
	}

	CCString* get_range_Value(const string& key)
	{
		return getValueOf(key, "range");
	}
	CCString* get_range_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "range");
	}

	CCString* get_angle_Value(const string& key)
	{
		return getValueOf(key, "angle");
	}
	CCString* get_angle_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "angle");
	}

	CCString* get_bullet_Value(const string& key)
	{
		return getValueOf(key, "bullet");
	}
	CCString* get_bullet_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "bullet");
	}

	CCString* get_speed_Value(const string& key)
	{
		return getValueOf(key, "speed");
	}
	CCString* get_speed_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "speed");
	}

	CCString* get_resourceID_Value(const string& key)
	{
		return getValueOf(key, "resourceID");
	}
	CCString* get_resourceID_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "resourceID");
	}

	CCString* get_animation_Value(const string& key)
	{
		return getValueOf(key, "animation");
	}
	CCString* get_animation_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "animation");
	}

	CCString* get_atk_se_Value(const string& key)
	{
		return getValueOf(key, "atk_se");
	}
	CCString* get_atk_se_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "atk_se");
	}

	CCString* get_hit_eft_Value(const string& key)
	{
		return getValueOf(key, "hit_eft");
	}
	CCString* get_hit_eft_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "hit_eft");
	}

	CCString* get_buff1_Value(const string& key)
	{
		return getValueOf(key, "buff1");
	}
	CCString* get_buff1_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "buff1");
	}

	CCString* get_buff2_Value(const string& key)
	{
		return getValueOf(key, "buff2");
	}
	CCString* get_buff2_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "buff2");
	}

	CCString* get_buff3_Value(const string& key)
	{
		return getValueOf(key, "buff3");
	}
	CCString* get_buff3_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "buff3");
	}

	CCString* get_debuff1_Value(const string& key)
	{
		return getValueOf(key, "debuff1");
	}
	CCString* get_debuff1_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "debuff1");
	}

	CCString* get_debuff2_Value(const string& key)
	{
		return getValueOf(key, "debuff2");
	}
	CCString* get_debuff2_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "debuff2");
	}

	CCString* get_debuff3_Value(const string& key)
	{
		return getValueOf(key, "debuff3");
	}
	CCString* get_debuff3_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "debuff3");
	}



protected:
	DTSkill():m_pDictionary(NULL)
	{}
	~DTSkill()
	{
		CC_SAFE_RELEASE(m_pDictionary);
	}
	
private:
	CCDictionary* m_pDictionary;
};


#endif	// __DTSkill__