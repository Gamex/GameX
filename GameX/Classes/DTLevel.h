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
	CCArray* getRoot() const
	{
		return m_pArray;
	}
	void loadData2CCArray()
    {
        if (NULL == m_pArray)
        {
            m_pArray = CCArray::create();
            CC_SAFE_RETAIN(m_pArray);
        }

		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("10001"), "roundID");
			elem->setObject(CCString::create("1"), "levelID");
			elem->setObject(CCString::create("5"), "time");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("1001"), "monsterID");
			elem->setObject(CCString::create("5"), "num");
			elem->setObject(CCString::create("1"), "positionID");
			elem->setObject(CCString::create("5"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("10002"), "roundID");
			elem->setObject(CCString::create("1"), "levelID");
			elem->setObject(CCString::create("5"), "time");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("1001"), "monsterID");
			elem->setObject(CCString::create("5"), "num");
			elem->setObject(CCString::create("2"), "positionID");
			elem->setObject(CCString::create("5"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("10003"), "roundID");
			elem->setObject(CCString::create("1"), "levelID");
			elem->setObject(CCString::create("5"), "time");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("1001"), "monsterID");
			elem->setObject(CCString::create("5"), "num");
			elem->setObject(CCString::create("3"), "positionID");
			elem->setObject(CCString::create("5"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("10004"), "roundID");
			elem->setObject(CCString::create("1"), "levelID");
			elem->setObject(CCString::create("5"), "time");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("1001"), "monsterID");
			elem->setObject(CCString::create("5"), "num");
			elem->setObject(CCString::create("4"), "positionID");
			elem->setObject(CCString::create("5"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("10005"), "roundID");
			elem->setObject(CCString::create("1"), "levelID");
			elem->setObject(CCString::create("5"), "time");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("1001"), "monsterID");
			elem->setObject(CCString::create("5"), "num");
			elem->setObject(CCString::create("5"), "positionID");
			elem->setObject(CCString::create("5"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("10006"), "roundID");
			elem->setObject(CCString::create("1"), "levelID");
			elem->setObject(CCString::create("10"), "time");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("1001"), "monsterID");
			elem->setObject(CCString::create("5"), "num");
			elem->setObject(CCString::create("1"), "positionID");
			elem->setObject(CCString::create("3"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("10007"), "roundID");
			elem->setObject(CCString::create("1"), "levelID");
			elem->setObject(CCString::create("10"), "time");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("1001"), "monsterID");
			elem->setObject(CCString::create("5"), "num");
			elem->setObject(CCString::create("3"), "positionID");
			elem->setObject(CCString::create("3"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("10008"), "roundID");
			elem->setObject(CCString::create("1"), "levelID");
			elem->setObject(CCString::create("10"), "time");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("1001"), "monsterID");
			elem->setObject(CCString::create("5"), "num");
			elem->setObject(CCString::create("5"), "positionID");
			elem->setObject(CCString::create("3"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("10009"), "roundID");
			elem->setObject(CCString::create("1"), "levelID");
			elem->setObject(CCString::create("15"), "time");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("1001"), "monsterID");
			elem->setObject(CCString::create("5"), "num");
			elem->setObject(CCString::create("1"), "positionID");
			elem->setObject(CCString::create("3"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("10010"), "roundID");
			elem->setObject(CCString::create("1"), "levelID");
			elem->setObject(CCString::create("15"), "time");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("1001"), "monsterID");
			elem->setObject(CCString::create("10"), "num");
			elem->setObject(CCString::create("2"), "positionID");
			elem->setObject(CCString::create("3"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("10011"), "roundID");
			elem->setObject(CCString::create("1"), "levelID");
			elem->setObject(CCString::create("15"), "time");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("1001"), "monsterID");
			elem->setObject(CCString::create("20"), "num");
			elem->setObject(CCString::create("3"), "positionID");
			elem->setObject(CCString::create("5"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("10012"), "roundID");
			elem->setObject(CCString::create("1"), "levelID");
			elem->setObject(CCString::create("15"), "time");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("1001"), "monsterID");
			elem->setObject(CCString::create("10"), "num");
			elem->setObject(CCString::create("4"), "positionID");
			elem->setObject(CCString::create("3"), "duration");

			
			m_pArray->addObject(elem);
		}
		{
			CCDictionary* elem = CCDictionary::create();
			
			elem->setObject(CCString::create("10013"), "roundID");
			elem->setObject(CCString::create("1"), "levelID");
			elem->setObject(CCString::create("15"), "time");
			elem->setObject(CCString::create("1"), "type");
			elem->setObject(CCString::create("1001"), "monsterID");
			elem->setObject(CCString::create("5"), "num");
			elem->setObject(CCString::create("5"), "positionID");
			elem->setObject(CCString::create("3"), "duration");

			
			m_pArray->addObject(elem);
		}

    }
        
    CCDictionary* getData(int key)
    {
        CC_ASSERT(m_pArray);
        if(key < 0 || key >= m_pArray->count()) return NULL;
        return dynamic_cast<CCDictionary*>(m_pArray->objectAtIndex(key));
    }

    CCString* getValueOf(int key, const string& subKey)
    {
        CC_ASSERT(m_pArray);
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

	CCString* get_levelID_Value(int key)
	{
		return getValueOf(key, "levelID");
	}
	CCString* get_levelID_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "levelID");
	}

	CCString* get_time_Value(int key)
	{
		return getValueOf(key, "time");
	}
	CCString* get_time_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "time");
	}

	CCString* get_type_Value(int key)
	{
		return getValueOf(key, "type");
	}
	CCString* get_type_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "type");
	}

	CCString* get_monsterID_Value(int key)
	{
		return getValueOf(key, "monsterID");
	}
	CCString* get_monsterID_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "monsterID");
	}

	CCString* get_num_Value(int key)
	{
		return getValueOf(key, "num");
	}
	CCString* get_num_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "num");
	}

	CCString* get_positionID_Value(int key)
	{
		return getValueOf(key, "positionID");
	}
	CCString* get_positionID_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "positionID");
	}

	CCString* get_duration_Value(int key)
	{
		return getValueOf(key, "duration");
	}
	CCString* get_duration_Value(CCDictionary* subDict)
	{
		return getValueOf(subDict, "duration");
	}



protected:
	DTLevel():m_pArray(NULL)
	{}
	~DTLevel()
	{
		CC_SAFE_RELEASE(m_pArray);
	}
	
private:
	CCArray* m_pArray;
};


#endif	// __DTLevel__