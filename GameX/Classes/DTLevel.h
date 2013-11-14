#ifndef __DTLevel__
#define __DTLevel__
#include "cocos2d.h"
#include <string>

using namespace std;
USING_NS_CC;

class DTLevel
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
			
			elem->setObject(String::create("10001"), "roundID");
			elem->setObject(String::create("1"), "levelID");
			elem->setObject(String::create("5"), "time");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("1001"), "monsterID");
			elem->setObject(String::create("5"), "num");
			elem->setObject(String::create("1"), "positionID");
			elem->setObject(String::create("5"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("10002"), "roundID");
			elem->setObject(String::create("1"), "levelID");
			elem->setObject(String::create("5"), "time");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("1001"), "monsterID");
			elem->setObject(String::create("5"), "num");
			elem->setObject(String::create("2"), "positionID");
			elem->setObject(String::create("5"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("10003"), "roundID");
			elem->setObject(String::create("1"), "levelID");
			elem->setObject(String::create("5"), "time");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("1001"), "monsterID");
			elem->setObject(String::create("5"), "num");
			elem->setObject(String::create("3"), "positionID");
			elem->setObject(String::create("5"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("10004"), "roundID");
			elem->setObject(String::create("1"), "levelID");
			elem->setObject(String::create("5"), "time");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("1001"), "monsterID");
			elem->setObject(String::create("5"), "num");
			elem->setObject(String::create("4"), "positionID");
			elem->setObject(String::create("5"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("10005"), "roundID");
			elem->setObject(String::create("1"), "levelID");
			elem->setObject(String::create("5"), "time");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("1001"), "monsterID");
			elem->setObject(String::create("5"), "num");
			elem->setObject(String::create("5"), "positionID");
			elem->setObject(String::create("5"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("10006"), "roundID");
			elem->setObject(String::create("1"), "levelID");
			elem->setObject(String::create("10"), "time");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("1001"), "monsterID");
			elem->setObject(String::create("5"), "num");
			elem->setObject(String::create("1"), "positionID");
			elem->setObject(String::create("3"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("10007"), "roundID");
			elem->setObject(String::create("1"), "levelID");
			elem->setObject(String::create("10"), "time");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("1001"), "monsterID");
			elem->setObject(String::create("5"), "num");
			elem->setObject(String::create("3"), "positionID");
			elem->setObject(String::create("3"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("10008"), "roundID");
			elem->setObject(String::create("1"), "levelID");
			elem->setObject(String::create("10"), "time");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("1001"), "monsterID");
			elem->setObject(String::create("5"), "num");
			elem->setObject(String::create("5"), "positionID");
			elem->setObject(String::create("3"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("10009"), "roundID");
			elem->setObject(String::create("1"), "levelID");
			elem->setObject(String::create("15"), "time");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("1001"), "monsterID");
			elem->setObject(String::create("5"), "num");
			elem->setObject(String::create("1"), "positionID");
			elem->setObject(String::create("3"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("10010"), "roundID");
			elem->setObject(String::create("1"), "levelID");
			elem->setObject(String::create("15"), "time");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("1001"), "monsterID");
			elem->setObject(String::create("10"), "num");
			elem->setObject(String::create("2"), "positionID");
			elem->setObject(String::create("3"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("10011"), "roundID");
			elem->setObject(String::create("1"), "levelID");
			elem->setObject(String::create("15"), "time");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("1001"), "monsterID");
			elem->setObject(String::create("20"), "num");
			elem->setObject(String::create("3"), "positionID");
			elem->setObject(String::create("5"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("10012"), "roundID");
			elem->setObject(String::create("1"), "levelID");
			elem->setObject(String::create("15"), "time");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("1001"), "monsterID");
			elem->setObject(String::create("10"), "num");
			elem->setObject(String::create("4"), "positionID");
			elem->setObject(String::create("3"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			Dictionary* elem = Dictionary::create();
			
			elem->setObject(String::create("10013"), "roundID");
			elem->setObject(String::create("1"), "levelID");
			elem->setObject(String::create("15"), "time");
			elem->setObject(String::create("1"), "type");
			elem->setObject(String::create("1001"), "monsterID");
			elem->setObject(String::create("5"), "num");
			elem->setObject(String::create("5"), "positionID");
			elem->setObject(String::create("3"), "duration");

			
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

	String* get_levelID_Value(int key)
	{
		return getValueOf(key, "levelID");
	}
	String* get_levelID_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "levelID");
	}

	String* get_time_Value(int key)
	{
		return getValueOf(key, "time");
	}
	String* get_time_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "time");
	}

	String* get_type_Value(int key)
	{
		return getValueOf(key, "type");
	}
	String* get_type_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "type");
	}

	String* get_monsterID_Value(int key)
	{
		return getValueOf(key, "monsterID");
	}
	String* get_monsterID_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "monsterID");
	}

	String* get_num_Value(int key)
	{
		return getValueOf(key, "num");
	}
	String* get_num_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "num");
	}

	String* get_positionID_Value(int key)
	{
		return getValueOf(key, "positionID");
	}
	String* get_positionID_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "positionID");
	}

	String* get_duration_Value(int key)
	{
		return getValueOf(key, "duration");
	}
	String* get_duration_Value(Dictionary* subDict)
	{
		return getValueOf(subDict, "duration");
	}



protected:
	DTLevel():m_pArray(nullptr)
	{}
	~DTLevel()
	{
		CC_SAFE_RELEASE(m_pArray);
	}
	
private:
	Array* m_pArray;
};


#endif	// __DTLevel__