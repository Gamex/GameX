//
//  TFPListReaderHelper.h
//  TheForce
//
//  Created by Ray M on 13-3-7.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFPListReaderHelper__
#define __TheForce__TFPListReaderHelper__

#include "Common.h"

class TFPListReaderHelper
{
public:
    static void split(std::string src, const char* token, CCArray& vect);
    static bool splitWithForm(const char* pStr, CCArray& strs);

protected:
private:
};


//#define PREPARE_READ_FROM_DICT_AND_RETURN(__return__)  \
//CCDictionary* pDict = getObjectDictionary();\
//if (NULL == pDict)\
//{\
//return __return__;\
//}
//
//#define PREPARE_READ_FROM_DICT  \
//CCDictionary* pDict = getObjectDictionary();\
//if (NULL == pDict)\
//{\
//return;\
//}
//
//#define READ_INT_FROM_DICT(__key__)  \
//CCString* str = dynamic_cast<CCString*>(pDict->objectForKey(#__key__));\
//if (NULL == str)\
//{\
//return 0;\
//}\
//return str->intValue();
//
//#define DECLARE_DICTFUNC(__type, __key)  virtual __type get##__key##FromDict();
//#define DECLARE_DICTFUNC_BY_LEVEL(__type, __key) virtual __type get##__key##FromDictByLevel(int level);
//
//#define DEFINE_DICTFUNC_STR(__class, __key) \
//CCString* __class::get##__key##FromDict()\
//{\
//PREPARE_READ_FROM_DICT_AND_RETURN(NULL);\
//CCString* str = dynamic_cast<CCString*>(pDict->objectForKey(#__key));\
//return str;\
//}
//
//#define DEFINE_DICTFUNC(__class, __type, __key, __return) \
//__type __class::get##__key##FromDict()\
//{\
//PREPARE_READ_FROM_DICT_AND_RETURN(__return)\
//CCString* str = dynamic_cast<CCString*>(pDict->objectForKey(#__key));\
//if (NULL == str)\
//{\
//return __return;\
//}\
//return str->__type##Value();\
//}
//
//#define DEFINE_DICTFUNC_ARRAY(__class, __key)   \
//CCArray* __class::get##__key##FromDict()\
//{\
//PREPARE_READ_FROM_DICT_AND_RETURN(NULL)\
//CCArray* array = dynamic_cast<CCArray*>(pDict->objectForKey(#__key));\
//if (NULL == array)\
//{\
//return NULL;\
//}\
//return array;\
//}
//
//#define DEFINE_DICTFUNC_DICTIONARY(__class, __key)   \
//CCDictionary* __class::get##__key##FromDict()\
//{\
//PREPARE_READ_FROM_DICT_AND_RETURN(NULL)\
//CCDictionary* dict = dynamic_cast<CCDictionary*>(pDict->objectForKey(#__key));\
//if (NULL == dict)\
//{\
//return NULL;\
//}\
//return dict;\
//}
//
//#define DEFINE_DICTFUNC_BY_LEVEL(__class, __type, __key, __return)\
//__type __class::get##__key##FromDictByLevel(int level)\
//{\
//PREPARE_READ_FROM_DICT_AND_RETURN(__return);\
//CCString* str = dynamic_cast<CCString*>(pDict->objectForKey(#__key));\
//if (NULL == str)\
//{\
//return __return;\
//}\
//CCArray array;\
//if (TFPListReaderHelper::splitWithForm(str->getCString(), array))\
//{\
//CCString* dat = dynamic_cast<CCString*>(array.objectAtIndex(level));\
//if (NULL != dat)\
//{\
//return dat->__type##Value();\
//}\
//}\
//return __return;\
//}
//
//#define DEFINE_DICTFUNC_STR_BY_LEVEL(__class, __key)\
//CCString* __class::get##__key##FromDictByLevel(int level)\
//{\
//PREPARE_READ_FROM_DICT_AND_RETURN(NULL);\
//CCString* str = dynamic_cast<CCString*>(pDict->objectForKey(#__key));\
//if (NULL == str)\
//{\
//return __return;\
//}\
//CCArray array;\
//if (TFPListReaderHelper::splitWithForm(str->getCString(), array))\
//{\
//return dynamic_cast<CCString*>(array.objectAtIndex(level));\
//}\
//return NULL;\
//}


#endif /* defined(__TheForce__TFPListReaderHelper__) */
