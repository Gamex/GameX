#ifndef __DTUnit__
#define __DTUnit__
#include "Common.h"


class DTUnit
{
	friend class CDataCenterManager;
public:
	class _Data
	{
	public:
		string ID;
		string name;
		string resourceID;
		string className;
		int gridWidth;
		int gridHeight;
		int buildingTime;
		int mineralCost;
		int gasCost;
		int hp;
		int atk;
		int dimension;
		int target;
		float radius;
		float speed;
		float rate;
		string skill0;
		string skill1;
		string skill2;
		string skill3;
		string skill4;
		string skill5;

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
        std::string fullPath = fu->fullPathForFilename("DTUnit.json");
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
			d->resourceID = json_string_value(json_object_get(value, "resourceID"));
			d->className = json_string_value(json_object_get(value, "className"));
			d->gridWidth = json_integer_value(json_object_get(value, "gridWidth"));
			d->gridHeight = json_integer_value(json_object_get(value, "gridHeight"));
			d->buildingTime = json_integer_value(json_object_get(value, "buildingTime"));
			d->mineralCost = json_integer_value(json_object_get(value, "mineralCost"));
			d->gasCost = json_integer_value(json_object_get(value, "gasCost"));
			d->hp = json_integer_value(json_object_get(value, "hp"));
			d->atk = json_integer_value(json_object_get(value, "atk"));
			d->dimension = json_integer_value(json_object_get(value, "dimension"));
			d->target = json_integer_value(json_object_get(value, "target"));
			{json_t* o = json_object_get(value, "radius"); d->radius = (float)(json_is_real(o) ? json_real_value(o) : json_integer_value(o));}
			{json_t* o = json_object_get(value, "speed"); d->speed = (float)(json_is_real(o) ? json_real_value(o) : json_integer_value(o));}
			{json_t* o = json_object_get(value, "rate"); d->rate = (float)(json_is_real(o) ? json_real_value(o) : json_integer_value(o));}
			d->skill0 = json_string_value(json_object_get(value, "skill0"));
			d->skill1 = json_string_value(json_object_get(value, "skill1"));
			d->skill2 = json_string_value(json_object_get(value, "skill2"));
			d->skill3 = json_string_value(json_object_get(value, "skill3"));
			d->skill4 = json_string_value(json_object_get(value, "skill4"));
			d->skill5 = json_string_value(json_object_get(value, "skill5"));

            
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


#endif	// __DTUnit__