//
//  CPListSaver.cpp
//  EliminationPlane
//
//  Created by 马 俊 on 13-4-24.
//
//

#include "CPListSaver.h"
#include "Common.h"

using namespace tinyxml2;

#define BAD_CAST
#define ROOT_NODE_NAME BAD_CAST("plist")
#define ROOT_PLIST_PROP BAD_CAST("version")
#define ROOT_PLIST_VERSION BAD_CAST("1.0")
#define DICT_NODE_DICT BAD_CAST("dict")
#define DICT_NODE_KEY BAD_CAST("key")
#define DICT_NODE_ARRAY BAD_CAST("array")
#define DICT_NODE_STRING BAD_CAST("string")

bool CPListSaver::save2Plist(CCDictionary* pDict, const char* filename)
{
    do
    {
        XMLDocument* xmlDoc = new XMLDocument;

        BREAK_IF(!xmlDoc);
        BREAK_IF(!pDict);
        BREAK_IF(!filename);

        
        XMLDeclaration* decl = xmlDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
        BREAK_IF(!decl);
        xmlDoc->LinkEndChild(decl);
        
        
        XMLElement* root = xmlDoc->NewElement(ROOT_NODE_NAME);
        BREAK_IF(!root);
        xmlDoc->LinkEndChild(root);
        
        root->SetAttribute(ROOT_PLIST_PROP, 1.f);
        
        BREAK_IF(!saveDictionary(pDict, root, xmlDoc));

        xmlDoc->SaveFile(filename);

        delete xmlDoc;
        return true;
    } while (false);
    
    return false;
}



bool CPListSaver::saveArray(CCArray* pArray, tinyxml2::XMLElement* node, tinyxml2::XMLDocument* doc)
{
    do
    {
        XMLElement* array_node = doc->NewElement(DICT_NODE_ARRAY);
        BREAK_IF(!array_node);
        node->LinkEndChild(array_node);
        
        CCObject* obj;
        CCARRAY_FOREACH(pArray, obj)
        {
            if (dynamic_cast<CCString*>(obj))
            {
                CCString* s = dynamic_cast<CCString*>(obj);
                BREAK_IF(!saveString(s->getCString(), array_node, doc));
            }
            else if (dynamic_cast<CCDictionary*>(obj))
            {
                BREAK_IF(!saveDictionary(dynamic_cast<CCDictionary*>(obj), array_node, doc));
            }
            else if (dynamic_cast<CCArray*>(obj))
            {
                BREAK_IF(!saveArray(dynamic_cast<CCArray*>(obj), array_node, doc));
            }
        }
        return true;
    } while (false);
    
    return false;
}



bool CPListSaver::saveDictionary(CCDictionary* pDict, tinyxml2::XMLElement* node, tinyxml2::XMLDocument* doc)
{
    do
    {
        XMLElement* dict_node = doc->NewElement(DICT_NODE_DICT);
        BREAK_IF(!dict_node);
        node->LinkEndChild(dict_node);
        
        CCDictElement* pElem;
        CCDICT_FOREACH(pDict, pElem)
        {
            saveKey(pElem->getStrKey(), dict_node, doc);
            
            CCObject* obj = pElem->getObject();

            if (dynamic_cast<CCString*>(obj))
            {
                CCString* s = dynamic_cast<CCString*>(obj);
                BREAK_IF(!saveString(s->getCString(), dict_node, doc));
            }
            else if (dynamic_cast<CCDictionary*>(obj))
            {
                BREAK_IF(!saveDictionary(dynamic_cast<CCDictionary*>(obj), dict_node, doc));
            }
            else if (dynamic_cast<CCArray*>(obj))
            {
                BREAK_IF(!saveArray(dynamic_cast<CCArray*>(obj), dict_node, doc));
            }
        }
        return true;
    } while (false);
    
    return false;
}



bool CPListSaver::saveKey(const char* key, tinyxml2::XMLElement* node, tinyxml2::XMLDocument* doc)
{
    do
    {
        XMLElement* tmpNode = doc->NewElement(DICT_NODE_KEY);
        XMLText* content = doc->NewText(key);
        BREAK_IF(!tmpNode);
        BREAK_IF(!content);
        node->LinkEndChild(tmpNode);
        tmpNode->LinkEndChild(content);

        return true;
    } while (false);
    
    return false;
}



bool CPListSaver::saveString(const char* str, tinyxml2::XMLElement* node, tinyxml2::XMLDocument* doc)
{
    do
    {
        XMLElement* tmpNode = doc->NewElement(DICT_NODE_STRING);
        XMLText* content = doc->NewText(str);
        BREAK_IF(!tmpNode);
        BREAK_IF(!content);
        node->LinkEndChild(tmpNode);
        tmpNode->LinkEndChild(content);

        return true;
    } while (false);
    
    return false;
}
