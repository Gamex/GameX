#ifndef __DTSkill__
#define __DTSkill__
#include "Common.h"


class DTSkill
{
	friend class CDataCenterManager;
public:
	class _Data
	{
	public:
		string ID;
		string name;
		string className;
		int cd;
		int trigger;
		int param;
		int target;
		int dimension;
		int type;
		float range;
		int angle;
		int bullet;
		int speed;
		string resourceID;
		string animation;
		int atk_se;
		int hit_eft;
		int buff1;
		int buff2;
		int buff3;
		int debuff1;
		int debuff2;
		int debuff3;

	};
    
    vector<string> getAllKeys()
    {
        vector<string> keys;
        auto it = m_data.begin();
        for (; it != m_data.end(); ++it)
        {
            keys.push_back((*it).first);
        }
        return keys;
    }
    
	void loadJSONData()
    {
        FileUtils* fu = FileUtils::getInstance();
        std::string fullPath = fu->fullPathForFilename("DTSkill.json");
        unsigned long size;
        const char *pFileContent = (char*)fu->getFileData(fullPath.c_str(), "r", &size);
        size_t flags = 0;
        json_error_t error;
        CC_ASSERT(pFileContent);
        json_t* root = json_loadb(pFileContent, size, flags, &error);
        json_t* value;
        const char* key;
        json_object_foreach(root, key, value)
        {
            _Data* d = new _Data;
            d->ID = key;
            CC_ASSERT(m_data.find(d->ID) == m_data.end());

			d->name = json_string_value(json_object_get(value, "name"));
			d->className = json_string_value(json_object_get(value, "className"));
			d->cd = json_integer_value(json_object_get(value, "cd"));
			d->trigger = json_integer_value(json_object_get(value, "trigger"));
			d->param = json_integer_value(json_object_get(value, "param"));
			d->target = json_integer_value(json_object_get(value, "target"));
			d->dimension = json_integer_value(json_object_get(value, "dimension"));
			d->type = json_integer_value(json_object_get(value, "type"));
			{json_t* o = json_object_get(value, "range"); d->range = (float)(json_is_real(o) ? json_real_value(o) : json_integer_value(o));}
			d->angle = json_integer_value(json_object_get(value, "angle"));
			d->bullet = json_integer_value(json_object_get(value, "bullet"));
			d->speed = json_integer_value(json_object_get(value, "speed"));
			d->resourceID = json_string_value(json_object_get(value, "resourceID"));
			d->animation = json_string_value(json_object_get(value, "animation"));
			d->atk_se = json_integer_value(json_object_get(value, "atk_se"));
			d->hit_eft = json_integer_value(json_object_get(value, "hit_eft"));
			d->buff1 = json_integer_value(json_object_get(value, "buff1"));
			d->buff2 = json_integer_value(json_object_get(value, "buff2"));
			d->buff3 = json_integer_value(json_object_get(value, "buff3"));
			d->debuff1 = json_integer_value(json_object_get(value, "debuff1"));
			d->debuff2 = json_integer_value(json_object_get(value, "debuff2"));
			d->debuff3 = json_integer_value(json_object_get(value, "debuff3"));

            
            m_data[d->ID] = d;
        }
    }
        
    const _Data* getData(const string& key)
    {
        auto it = m_data.find(key);
        if (it != m_data.end())
        {
            return (*it).second;
        }
        
        return nullptr;
    }

protected:
private:
	map<string, _Data*> m_data;
};


#endif	// __DTSkill__