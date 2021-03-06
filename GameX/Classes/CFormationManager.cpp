//
//  CFormationManager.cpp
//  GameX
//
//  Created by 马 俊 on 13-9-1.
//
//

#include "Common.h"
#include "CFormationManager.h"


IMPLEMENT_SINGLETON(CFormationManager);


CFormationManager::CFormationManager()
{
    
}



CFormationManager::~CFormationManager()
{
    
}



bool CFormation::saveToFile(const char* filename)
{
    do
    {
        if (filename == nullptr)
        {
            filename = m_filename.c_str();
        }
        
        std::string path = FileUtils::getInstance()->getWritablePath();
        path += filename;
        FILE* fp = fopen(path.c_str(), "wb");
        BREAK_IF_FAILED(fp);
        
        int size = m_elements.size();
        fwrite(&size, sizeof(int), 1, fp);
        for (int i = 0 ; i < size; ++i)
        {
            CFormationElement* fe = m_elements[i];
            fwrite(&(fe->pos.x), sizeof(float), 1, fp);
            fwrite(&(fe->pos.y), sizeof(float), 1, fp);
            int data = fe->unitId.size() + 1;
            fwrite(&data, sizeof(int), 1, fp);
            fwrite(fe->unitId.c_str(), data, 1, fp);
        }
        
        fclose(fp);
        return true;
    } while (false);
    
	return false;
}



bool CFormation::loadFromFile(const char* filename)
{
    do
    {
        if (filename == nullptr)
        {
            filename = m_filename.c_str();
        }
        
        std::string path = FileUtils::getInstance()->getWritablePath();
        path += filename;
        FILE* fp = fopen(path.c_str(), "rb");
        BREAK_IF_FAILED(fp);
        
        clearAll();
        
        const int STR_LEN = 260;
        char str[STR_LEN];
        int size;
        fread(&size, sizeof(int), 1, fp);
        m_elements.resize(size);
        for (int i = 0 ; i < size; ++i)
        {
            CFormationElement* fe = new CFormationElement;
            fread(&(fe->pos.x), sizeof(float), 1, fp);
            fread(&(fe->pos.y), sizeof(float), 1, fp);
            int data;
            fread(&data, sizeof(int), 1, fp);
            CC_ASSERT(data < STR_LEN);
            fe->unitId.resize(data, 0);
            fread(str, data, 1, fp);
            fe->unitId = str;
            m_elements[i] = fe;
        }
        
        fclose(fp);
        return true;
    } while (false);
    
	return false;
}



void CFormation::clearAll()
{
    for (int i = 0; i < m_elements.size(); ++i)
    {
        CC_SAFE_DELETE(m_elements[i]);
    }
    m_elements.clear();
}

