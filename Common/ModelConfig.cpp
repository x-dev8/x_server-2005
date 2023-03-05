#include "ModelConfig.h"
#include <algorithm>
#include "tstring.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"


bool ModelConfig::AddModelData(ModelConfig::ModelData &xModelData, bool bReplace /* = false*/)
{
	modeliter iter = m_mapModelData.find(xModelData.Id);
	if (iter != m_mapModelData.end())
	{
		if (bReplace) { iter->second = xModelData; }

		return bReplace;
	}

	if( m_mapModelData.find( xModelData.Id ) != m_mapModelData.end() )
		assert( 0 && "model duplicate" );

	m_mapModelData.insert(make_pair(xModelData.Id, xModelData));

	return true;
}

bool ModelConfig::RemoveModelData(unsigned short nId)
{
	modeliter iter = m_mapModelData.find(nId);
	if (iter != m_mapModelData.end())
	{
		m_mapModelData.erase(iter);
		return true;
	}

	return false;
}

ModelConfig::ModelData* ModelConfig::GetModelDataById(unsigned short nId)
{
	modeliter iter = m_mapModelData.find(nId);
	if (iter != m_mapModelData.end())
	{
		return &(iter->second);
	}

	return NULL;
}


////////////////////////////////////////////////////////////////////////////////
#define Root_Key			"Project"
#define Name_Key			"Name"
#define Version_Key			"Version"
#define Models_Key			"Models"
#define Model_Key			"Model"
#define Id_Key				"Id"
#define FilePath_Key		"FilePath"
#define HeadPicture_Key		"HeadPicture"
#define Description_Key		"Description"
//////////////////////////////////////////////////////////////////////////////
bool ModelConfig::LoadModelConfig(const char *szFile)
{
	if (szFile == NULL || *szFile == 0) { return false; }

	m_mapModelData.clear();

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(szFile, 1)) { return false; }

	MeXmlElement* pRoot = xMeXml.FirstChildElement(Root_Key);
	if (pRoot == NULL ) { return false; }

	//版本(是否需要检查)
	//////////////////////////////////////////////////////////
	MeXmlElement* pModels = pRoot->FirstChildElement(Models_Key);
	if (pModels == NULL) { return false; }

	MeXmlElement* pModel = pModels->FirstChildElement(Model_Key);
	while (pModel != NULL)
	{	
		ModelData xModelData;

		//id
		int nId;
		if (pModel->Attribute(Id_Key, &nId) == NULL || nId < 0 ) { return false; }
		xModelData.Id = nId;

		//FilePath
		Common::_tstring strPath = "";			
		strPath.fromUTF8(pModel->Attribute(FilePath_Key));
		//if (strPath.empty()) { return false; }
		xModelData.FilePath = strPath;

		//HeadPicture
		Common::_tstring strHeadPicture;			
		strHeadPicture.fromUTF8(pModel->Attribute(HeadPicture_Key));
		//if (strHeadPicture.empty())	{ return false; }
		if (strHeadPicture.length() > 0)
			xModelData.HeadPicture = strHeadPicture;

		//Description
		Common::_tstring strDescription;			
		strDescription.fromUTF8(pModel->Attribute(Description_Key));
		xModelData.Description = strDescription;

		if (!AddModelData(xModelData)) { return false; }

		//next
		pModel = pModel->NextSiblingElement();
	}

	return true;
}

bool ModelConfig::SaveModelConfig(const char *szFile)
{
	if (szFile == NULL || *szFile == 0) { return false;	}

	MeXmlDocument xMeXmlDoc;
	xMeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","UTF-8","yes"));

	MeXmlElement* pRoot = xMeXmlDoc.InsertEndChild((Root_Key))->ToElement();
	if (pRoot == NULL) { return false; }

	Common::_tstring strName = "HeroOnline";
	pRoot->SetAttribute(Name_Key, strName.toUTF8().c_str());
	pRoot->SetAttribute(Version_Key, ""); 	

	MeXmlElement* pModels = pRoot->InsertEndChild((Models_Key))->ToElement();
	if(pModels == NULL) { return false; }

	modeliter iter = m_mapModelData.begin();
	modeliter end = m_mapModelData.end();
	for (; iter != end; ++iter)
	{
		MeXmlElement* pModel = pModels->InsertEndChild((Model_Key))->ToElement();
		if (pModel == NULL) { return false; }

		pModel->SetAttribute(Id_Key, iter->second.Id);		

		//FilePath
		Common::_tstring strPath = iter->second.FilePath;		
		pModel->SetAttribute(FilePath_Key, strPath.toUTF8().c_str());

		//HeadPicture
		Common::_tstring strHeadPicture = iter->second.HeadPicture;		
		pModel->SetAttribute(HeadPicture_Key, strHeadPicture.toUTF8().c_str());

		//Description
		Common::_tstring strDescription = iter->second.Description;		
		pModel->SetAttribute(Description_Key, strDescription.toUTF8().c_str());
	}

	return xMeXmlDoc.SaveFile(szFile);
}