#ifndef __DTEffect__
#define __DTEffect__
#include "Common.h"


class DTEffect
{
	friend class CDataCenterManager;
public:
	class _Data
	{
	public:
		string ID;
		string className;
		int cacheNum;
		string resourceID;

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
        std::string fullPath = fu->fullPathForFilename("DTEffect.json");
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

			d->className = json_string_value(json_object_get(value, "className"));
			d->cacheNum = json_integer_value(json_object_get(value, "cacheNum"));
			d->resourceID = json_string_value(json_object_get(value, "resourceID"));

            
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


#endif	// __DTEffect__