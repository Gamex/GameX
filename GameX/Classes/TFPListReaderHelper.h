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
    static void split(std::string src, const char* token, Array& vect);
    static bool splitWithForm(const char* pStr, Array& strs);

protected:
private:
};


//#define PREPARE_READ_FROM_DICT_AND_RETURN(__return__)  \
//Dictionary* pDict = getObjectDictionary();\
//if (nullptr == pDict)\
//{\
//return __return__;\
//}
//
//#define PREPARE_READ_FROM_DICT  \
//Dictionary* pDict = getObjectDictionary();\
//if (nullptr == pDict)\
//{\
//return;\
//}
//
//#define READ_INT_FROM_DICT(__key__)  \
//String* str = dynamic_cast<String*>(pDict->objectForKey(#__key__));\
//if (nullptr == str)\
//{\
//return 0;\
//}\
//return str->intValue();
//
//#define DECLARE_DICTFUNC(__type, __key)  virtual __type get##__key##FromDict();
//#define DECLARE_DICTFUNC_BY_LEVEL(__type, __key) virtual __type get##__key##FromDictByLevel(int level);
//
//#define DEFINE_DICTFUNC_STR(__class, __key) \
//String* __class::get##__key##FromDict()\
//{\
//PREPARE_READ_FROM_DICT_AND_RETURN(nullptr);\
//String* str = dynamic_cast<String*>(pDict->objectForKey(#__key));\
//return str;\
//}
//
//#define DEFINE_DICTFUNC(__class, __type, __key, __return) \
//__type __class::get##__key##FromDict()\
//{\
//PREPARE_READ_FROM_DICT_AND_RETURN(__return)\
//String* str = dynamic_cast<String*>(pDict->objectForKey(#__key));\
//if (nullptr == str)\
//{\
//return __return;\
//}\
//return str->__type##Value();\
//}
//
//#define DEFINE_DICTFUNC_ARRAY(__class, __key)   \
//Array* __class::get##__key##FromDict()\
//{\
//PREPARE_READ_FROM_DICT_AND_RETURN(nullptr)\
//Array* array = dynamic_cast<Array*>(pDict->objectForKey(#__key));\
//if (nullptr == array)\
//{\
//return nullptr;\
//}\
//return array;\
//}
//
//#define DEFINE_DICTFUNC_DICTIONARY(__class, __key)   \
//Dictionary* __class::get##__key##FromDict()\
//{\
//PREPARE_READ_FROM_DICT_AND_RETURN(nullptr)\
//Dictionary* dict = dynamic_cast<Dictionary*>(pDict->objectForKey(#__key));\
//if (nullptr == dict)\
//{\
//return nullptr;\
//}\
//return dict;\
//}
//
//#define DEFINE_DICTFUNC_BY_LEVEL(__class, __type, __key, __return)\
//__type __class::get##__key##FromDictByLevel(int level)\
//{\
//PREPARE_READ_FROM_DICT_AND_RETURN(__return);\
//String* str = dynamic_cast<String*>(pDict->objectForKey(#__key));\
//if (nullptr == str)\
//{\
//return __return;\
//}\
//Array array;\
//if (TFPListReaderHelper::splitWithForm(str->getCString(), array))\
//{\
//String* dat = dynamic_cast<String*>(array.getObjectAtIndex(level));\
//if (nullptr != dat)\
//{\
//return dat->__type##Value();\
//}\
//}\
//return __return;\
//}
//
//#define DEFINE_DICTFUNC_STR_BY_LEVEL(__class, __key)\
//String* __class::get##__key##FromDictByLevel(int level)\
//{\
//PREPARE_READ_FROM_DICT_AND_RETURN(nullptr);\
//String* str = dynamic_cast<String*>(pDict->objectForKey(#__key));\
//if (nullptr == str)\
//{\
//return __return;\
//}\
//Array array;\
//if (TFPListReaderHelper::splitWithForm(str->getCString(), array))\
//{\
//return dynamic_cast<String*>(array.getObjectAtIndex(level));\
//}\
//return nullptr;\
//}


#endif /* defined(__TheForce__TFPListReaderHelper__) */
