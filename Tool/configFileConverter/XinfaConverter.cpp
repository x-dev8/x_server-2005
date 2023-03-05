#include "StdAfx.h"
#include "XinfaConverter.h"
#include "MySlkReader.h"
#include "stringUtility.h"
#include "Logger.h"
#include "tstring.h"
#include <string>
#include <assert.h>

#include <list>

struct SXinFaInfo
{
	int index;	//���ڵ����ڵ���ţ�������ͬʱҲ�Ǹýڵ��һ���������ڵ����
	int maxIndex;	//���һ����������λ�õ����
	SXinFaInfo *pChild;
	SXinFaInfo *pSibling;
	SXinFaInfo():
	index(-1),
	pChild(NULL),
	pSibling(NULL)
	{

	}

	~SXinFaInfo()
	{
		Reset();
	}

	void Reset(void)
	{
		index = -1;

		if(pChild != NULL)
		{
			delete pChild;
			pChild = NULL;
		}

		if(pSibling != NULL)
		{
			delete pSibling;
			pSibling = NULL;
		}
	}
};

bool IsNewElem(const TString &str_)
{
	TString myStr = str_;
	TrimString(myStr);

	return TString::npos != myStr.find(_T(' '));
}

//��ȡһ���ڵ���Ϣ��
//info_��indexInfo_����Ϣ�����Ӧ���������ǵ���Ϣ����_value��
static bool ReadFile(CMySlkReader &reader_, const SXmlElementInfo &info_, const SXinFaInfo &indexInfo_, SXmlElementValue &_value)
{
	assert(indexInfo_.index > 0 && indexInfo_.maxIndex > 0 && indexInfo_.maxIndex >= indexInfo_.index);

	TString value;
	//��ȡ����������Ϣ
	for(int i = indexInfo_.index; i <= indexInfo_.maxIndex; ++i)
	{
		if(!reader_.GetStringField(i, value))
		{
			Log_outputLine(_T("��ȡ��%d�У���%d�г���"), reader_.GetCurrentLineIndex(), i);
			return false;
		}

// 		const CSlkReader::SField *pField = reader_.GetFieldOfLine(i);
// 		if(NULL == pField || NULL == pField->data.szValue || 0 == strlen(pField->data.szValue))
// 			return false;
// 
//		value = pField->data.szValue;

		_value.properties.push_back(value);
	}
	
	//�����ӽڵ�
	if(info_.pChild != NULL)
	{
		if(indexInfo_.pChild != NULL)
		{
			_value.pChild = new SXmlElementValue;
			if(!ReadFile(reader_, *info_.pChild, *indexInfo_.pChild, *_value.pChild))
				return false;
		}
	}

	//�����ֵܽڵ�
	if(info_.pSibling != NULL)
	{
		if(indexInfo_.pSibling != NULL)
		{
			_value.pSibling = new SXmlElementValue;
			if(!ReadFile(reader_, *info_.pSibling, *indexInfo_.pSibling, *_value.pSibling))
				return false;
		}
	}

	return true;
}


CXinfaConverter::CXinfaConverter(void)
{
	m_converterName = _T("xinfa Converter");
}

CXinfaConverter::~CXinfaConverter(void)
{
}

bool CXinfaConverter::InitElementInfo(const TCHAR *fileName_ /*= NULL*/)
{
	m_xmlHeadInfo.name = _T("Project");
	m_xmlHeadInfo.pChild = new SXmlElementInfo;
	m_xmlHeadInfo.pChild->name = _T("Heros");

	return true;
}

bool CXinfaConverter::LoadFile(const TString &fileName_, TXmlElementValues &_elementValues)
{
	CMySlkReader reader;
	std::string name = ToAnsi(fileName_);
	if( !reader.ReadFromFile(name.c_str()) )
	{        
		Log_outputLine(_T("�Ҳ���%s�ļ�\r\n"), fileName_.c_str());
		return false;
	}

	SXinFaInfo xinFaIndexInfo;
	int rowIndex = 2;  //����Ŵ�2��ʼ
	int filePosition = reader.GotoNextLine(rowIndex++);
	//������ͷ��Ϣ�����ݱ�ͷ��Ϣ��ʼ��xmlInfo
	if(CMySlkReader::ret_readover == filePosition)
		return false;
	{
		m_xmlInfo.Reset();
		SXmlElementInfo *pElemInfo = &m_xmlInfo;
		SXinFaInfo *pIndexInfo = &xinFaIndexInfo;
		pIndexInfo->index = 1;

		//�����ͷĳ���ֶ���Ϊmm nn��mmΪxml�ڵ�����nnΪ�ڵ��һ��������
		int fieldCount = reader.GetFieldNumOfLine();
		TString value;
		for(int i = pIndexInfo->index; i < fieldCount; ++i)
		{
			if(!reader.GetStringField(i, value))
			{
				Log_outputLine(_T("��ȡ��%d�У���%d�г���"), reader.GetCurrentLineIndex(), i);
				return false;
			}

			//ȥ��ͷβ�Ŀո�
			TrimString(value);

			TString::size_type charIndex = value.find(_T(' '));
			if(charIndex != TString::npos)
			{//�µĽڵ�

				//�õ�����
				TString itemName(value, 0, charIndex);
				TString propertyName(value, charIndex + 1, value.length() - charIndex - 1);


				if(pElemInfo->name.empty())
				{//��ǰ�ڵ㻹û�г�ʼ����˵���ǵ�ǰ�ڵ�Ŀ�ʼ
					pElemInfo->name = itemName;
					pElemInfo->properties.push_back(propertyName);
					pIndexInfo->index = i;
					pIndexInfo->maxIndex = i;
				}
				else
				{
					if(0 == pElemInfo->name.compare(itemName))
					{//�ֵܽڵ�
						pElemInfo->pSibling = new SXmlElementInfo;
						pIndexInfo->pSibling = new SXinFaInfo;

						pElemInfo = pElemInfo->pSibling;
						pIndexInfo = pIndexInfo->pSibling;
					}
					else
					{//�ӽڵ�
						pElemInfo->pChild = new SXmlElementInfo;
						pIndexInfo->pChild = new SXinFaInfo;

						pElemInfo = pElemInfo->pChild;
						pIndexInfo = pIndexInfo->pChild;
					}

					pElemInfo->name = itemName;
					pElemInfo->properties.push_back(propertyName);
					pIndexInfo->index = i;
					pIndexInfo->maxIndex = pIndexInfo->index;
				}
			}
			else
			{//��ǰ�ڵ������
				pElemInfo->properties.push_back(value);
				++pIndexInfo->maxIndex;
			}
		}
	}

	if(m_xmlInfo.name.empty())
	{
		m_xmlInfo.name = _T("Hero");
		xinFaIndexInfo.index = 1;
		xinFaIndexInfo.maxIndex = m_xmlInfo.properties.size();
	}

	//��ʼ�����ͷ�������Ч��������
	filePosition = reader.GotoNextLine(rowIndex++);
	while (filePosition != CMySlkReader::ret_readover) 
	{   
		if( CMySlkReader::ret_nothisline == filePosition )
		{	
			filePosition = reader.GotoNextLine(rowIndex++);
			continue;
		}

		SXmlElementValue *pElemValue = new SXmlElementValue;
		if(!ReadFile(reader, m_xmlInfo, xinFaIndexInfo, *pElemValue))
		{
			delete pElemValue;
			return false;
		}

		_elementValues.push_back(pElemValue);

		//��ȡ��һ��
		filePosition = reader.GotoNextLine(rowIndex++);
	}

	return true;
}


bool CXinfaConverter::LoadXinFile(const TString &fileName_,TXmlElementValues &_elementValues)
{
	CMySlkReader reader;
	std::string name = ToAnsi(fileName_);
	if (!reader.ReadFromFile(name.c_str()))
	{
		Log_outputLine(_T("�Ҳ���%s�ļ�\r\n"),fileName_.c_str());
		return false;
	}

	SXinFaInfo xinFaIndexInfo;
	mXinFaAttrs.clear();

	for (int row = 3;row < 10000000;++row)
	{
		if (reader.GotoNextLine(row) != CMySlkReader::ret_succ)
		{
			break;
		}

		XinFaAttribute attr;
		
		for (int col = 1;col <= reader.GetFieldNumOfLine();++col)
		{
			TString temp = "";
			reader.GetStringField(col,temp);
			TrimString(temp);

			switch (col)
			{
			case XinFaID:
				attr.XFID = atoi(temp.c_str());
				break;

			case XFLearningLevels:
				attr.XFLevel = atoi(temp.c_str());
				break;

			case IconID:
				attr.XFIconID = atoi(temp.c_str());
				break;
				
			case XinFaName:
				strcpy_s(attr.XFName, 32 - 1,  Common::_tstring(temp).toUTF8().c_str());
				break;

			case XinFaDesc:
				strcpy_s(attr.XFDesc,1024 - 1, Common::_tstring(temp).toUTF8().c_str());
				break;

			case XinFaPrev:
				attr.XFPrev = atoi(temp.c_str());
				break;

			case XinFaNeedProfession:
				strcpy_s(attr.XFProfession,32 - 1,temp.c_str());
				break;

			case XinFaNeedLevel:
				attr.XFNeedLevel = atoi(temp.c_str());
				break;

			case XinFaNeedMoney:
				attr.XFMoney = atoi(temp.c_str());
				break;

			case XinFaNeedExp:
				attr.XFEXP = atoi(temp.c_str());
				break;

			case CharAttrType1:
				strcpy_s(attr.XFAttrType1,32 - 1, temp.c_str());
				break;

			case CharAttrValue1:
				attr.XFAttrValue1 = atoi(temp.c_str());
				break;

			case CharAttrType2:
				strcpy_s(attr.XFAttrType2,32 - 1, temp.c_str());
				break;

			case CharAttrValue2:
				attr.XFAttrValue2 = atoi(temp.c_str());
				break;

			case SillkID:
				attr.SKID = atoi(temp.c_str());
				break;

			case SillkLevel:
				attr.SKLevel = atoi(temp.c_str());
				break;

			case AttrType1:
				strcpy_s(attr.SKAttrType1,32 - 1, temp.c_str());
				break;

			case AttrValue1:
				attr.SKAttrValue1 = atoi(temp.c_str());
				break;

			case AttrType2:
				strcpy_s(attr.SKAttrType2,32 - 1, temp.c_str());
				break;
	
			case AttrValue2:
				attr.SKAttrValue2 = atoi(temp.c_str());
				break;
			
			case SillkID1:
				attr.SKID1 = atoi(temp.c_str());
				break;

			case SillkLevel1:
				attr.SKLevel1 = atoi(temp.c_str());
				break;

			case AttrType1_1:
				strcpy_s(attr.SKAttrType1_1,32 - 1, temp.c_str());
				break;

			case AttrValue1_1:
				attr.SKAttrValue1_1 = atoi(temp.c_str());
				break;

			case AttrType2_1:
				strcpy_s(attr.SKAttrType2_1,32 - 1, temp.c_str());
				break;

			case AttrValue2_1:
				attr.SKAttrValue2_1 = atoi(temp.c_str());
				break;


			case SillkID2:
				attr.SKID2 = atoi(temp.c_str());
				break;

			case SillkLevel2:
				attr.SKLevel2 = atoi(temp.c_str());
				break;

			case AttrType1_2:
				strcpy_s(attr.SKAttrType1_2,32 - 1, temp.c_str());
				break;

			case AttrValue1_2:
				attr.SKAttrValue1_2 = atoi(temp.c_str());
				break;

			case AttrType2_2:
				strcpy_s(attr.SKAttrType2_2,32 - 1, temp.c_str());
				break;

			case AttrValue2_2:
				attr.SKAttrValue2_2 = atoi(temp.c_str());
				break;

			case SillkID3:
				attr.SKID3 = atoi(temp.c_str());
				break;

			case SillkLevel3:
				attr.SKLevel3 = atoi(temp.c_str());
				break;

			case AttrType1_3:
				strcpy_s(attr.SKAttrType1_3,32 - 1, temp.c_str());
				break;

			case AttrValue1_3:
				attr.SKAttrValue1_3 = atoi(temp.c_str());
				break;

			case AttrType2_3:
				strcpy_s(attr.SKAttrType2_3,32 - 1,temp.c_str());
				break;

			case AttrValue2_3:
				attr.SKAttrValue2_3 = atoi(temp.c_str());
				break;

			default:
				break;

				
		}
	}
	mXinFaAttrs.push_back(attr);
 }

	//����XML

	MeXmlDocument doc;
	doc.InsertEndChild(MeXmlDeclaration("1.0", "utf-8", "yes"));

	//
	MeXmlElement *Project = doc.InsertEndChild("Project")->ToElement();
	MeXmlElement *Talents = Project->InsertEndChild("Talents")->ToElement();

	std::vector<XinFaAttribute> attrs;

	for (int ClassID = 0 ; ClassID < 6 ; ++ClassID )
	{
		// ����ְҵ�ҳ����е��ķ�
		FindAttributeForXinFa(XINFA_CLASS_NAMES[ClassID],attrs); 
		for (int a = 0; a < attrs.size(); ++a)
		{
			XinFaAttribute *attribute = &attrs[a];

			// Append XinFa
			
			
			MeXmlElement *XinFa = Talents->InsertEndChild("XinFa ")->ToElement();
			XinFa->SetAttribute("ID",attribute->XFID);
			XinFa->SetAttribute("Level", attribute->XFLevel);
			XinFa->SetAttribute("IconID", attribute->XFIconID);
			XinFa->SetAttribute("Name", attribute->XFName);
			XinFa->SetAttribute("Desc", attribute->XFDesc);
			XinFa->SetAttribute("PrevXinFa", attribute->XFPrev);
			XinFa->SetAttribute("NeedProfession", attribute->XFProfession);
			XinFa->SetAttribute("NeedLevel", attribute->XFNeedLevel);
			XinFa->SetAttribute("NeedMoney", attribute->XFMoney);
			XinFa->SetAttribute("NeedExp", attribute->XFEXP);
			XinFa->SetAttribute("CharAttrType1", attribute->XFAttrType1);
			XinFa->SetAttribute("CharAttrValue1", attribute->XFAttrValue1);
			XinFa->SetAttribute("CharAttrType2", attribute->XFAttrType2);
			XinFa->SetAttribute("CharAttrValue2", attribute->XFAttrValue2);
		
			MeXmlElement *Skill = XinFa->InsertEndChild("Skill")->ToElement();
			{
				// Append Sillk
				Skill->SetAttribute("ID", attribute->SKID);
				Skill->SetAttribute("Level",attribute->SKLevel);
				Skill->SetAttribute("AttrType1",attribute->SKAttrType1);
				Skill->SetAttribute("AttrValue1",attribute->SKAttrValue1);
				Skill->SetAttribute("AttrType2",attribute->SKAttrType2);
				Skill->SetAttribute("AttrValue2",attribute->SKAttrValue2);	
			}	


			MeXmlElement *Skill1 = XinFa->InsertEndChild("Skill")->ToElement();
			{
				// Append Sillk
				Skill1->SetAttribute("ID", attribute->SKID1);
				Skill1->SetAttribute("Level",attribute->SKLevel1);
				Skill1->SetAttribute("AttrType1",attribute->SKAttrType1_1);
				Skill1->SetAttribute("AttrValue1",attribute->SKAttrValue1_1);
				Skill1->SetAttribute("AttrType2",attribute->SKAttrType2_1);
				Skill1->SetAttribute("AttrValue2",attribute->SKAttrValue2_1);	
			}	


			MeXmlElement *Skill2 = XinFa->InsertEndChild("Skill")->ToElement();
			{
				// Append Sillk
				Skill2->SetAttribute("ID", attribute->SKID2);
				Skill2->SetAttribute("Level",attribute->SKLevel2);
				Skill2->SetAttribute("AttrType1",attribute->SKAttrType1_2);
				Skill2->SetAttribute("AttrValue1",attribute->SKAttrValue1_2);
				Skill2->SetAttribute("AttrType2",attribute->SKAttrType2_2);
				Skill2->SetAttribute("AttrValue2",attribute->SKAttrValue2_2);	
			}	


			MeXmlElement *Skill3 = XinFa->InsertEndChild("Skill")->ToElement();
			{
				// Append Sillk
				Skill3->SetAttribute("ID", attribute->SKID3);
				Skill3->SetAttribute("Level",attribute->SKLevel3);
				Skill3->SetAttribute("AttrType1",attribute->SKAttrType1_3);
				Skill3->SetAttribute("AttrValue1",attribute->SKAttrValue1_3);
				Skill3->SetAttribute("AttrType2",attribute->SKAttrType2_3);
				Skill3->SetAttribute("AttrValue2",attribute->SKAttrValue2_3);	
			}	

		}
	}

	TString resultFileName;
	if(!GetResultFileName(fileName_, resultFileName))
	return false;
	name = ToAnsi(resultFileName);
	return doc.SaveFile(name.c_str());

}


bool CXinfaConverter::LoadSlkFile(const TString &fileName_, TXmlElementValues &_elementValues)
{
	CMySlkReader reader;
	std::string name = ToAnsi(fileName_);
	if( !reader.ReadFromFile(name.c_str()) )
	{        
		Log_outputLine(_T("�Ҳ���%s�ļ�\r\n"), fileName_.c_str());
		return false;
	}

	SXinFaInfo xinFaIndexInfo;

	mBaseSecondAttrs.clear();
	for (int row = 3; row < 10000000; ++row)
	{
		if (reader.GotoNextLine(row) != CMySlkReader::ret_succ)
			break;

		BaseSecondAttribute attr;
		int temp0, temp1;
		temp0 = temp1 = 0;
		for(int col = 1; col <= reader.GetFieldNumOfLine(); ++col)
		{
			TString temp;
			reader.GetStringField(col, temp);
			TrimString(temp);			
			switch (col)
			{
			case TypeIDCol:
				attr.TypeID = atoi(temp.c_str());
				break;

			case ClassNameCol:
				strcpy_s(attr.ClassName, 32 - 1, temp.c_str());
				break;

			case LevelCol:
				attr.Level = atoi(temp.c_str());
				break;

			case BaseAttrsCol:
				attr.baseAttrs[temp0++] = atoi(temp.c_str());
				break;

			case SecondAttrsCol:
				attr.secondAttrs[temp1++] = atoi(temp.c_str());
				break;

			default:
				{
					if (temp0 > 0 && temp0 <= 3)
					{
						attr.baseAttrs[temp0++] = atoi(temp.c_str());	
					}

					if (temp1 > 0 && temp1 <= 11)
					{
						attr.secondAttrs[temp1++] = atoi(temp.c_str());
					}
				}
			}
		}

		mBaseSecondAttrs.push_back(attr);
	}

	// ����XML
	MeXmlDocument doc;

	MeXmlDeclaration *decl = new MeXmlDeclaration("1.0", "utf-8", "yes");
	doc.InsertEndChild(*decl);

	// root
	MeXmlElement *root = doc.InsertEndChild("root")->ToElement();

	std::vector<BaseSecondAttribute> attrs;
	for (int classID = 0; classID < 5; ++classID)//zhuxincong 2012.7.18 5����ְҵ�ĸ���
	{
		// ����ְҵId�ҳ����е�����
		FindAttributeForClass(classID, attrs);
		
		// Arms
		MeXmlElement *arms = root->InsertEndChild("Arms")->ToElement();
		arms->SetAttribute("TypeId", classID);
		arms->SetAttribute("Name", XINFA_CLASS_NAMES[classID]);

		// BaseAttributes
		MeXmlElement *baseAttrs = arms->InsertEndChild("BaseAttributes")->ToElement();

		// SecondAttributes
		MeXmlElement *secondAttrs = arms->InsertEndChild("SecondAttributes")->ToElement();
		for (int a = 0; a < attrs.size(); ++a)
		{
			BaseSecondAttribute *attribute = &attrs[a];
			
			// Append BaseAttribute
			{
				MeXmlElement *attr = baseAttrs->InsertEndChild("LevelAttribute ")->ToElement();
				attr->SetAttribute("Level", attribute->Level);

				for (int i = 0; i < 4; ++i)
				{
					char temp[32] = {0};
					sprintf_s(temp, 32 - 1, "baseValue%d", i);
					attr->SetAttribute(temp, attribute->baseAttrs[i]);
				}
			}

			// Append SecondAttribute
			{
				MeXmlElement *attr = secondAttrs->InsertEndChild("LevelSecondAttributeCorrect")->ToElement();
				attr->SetAttribute("Level", attribute->Level);

				for (int i = 0; i < 12; ++i)
				{
					char temp[32] = {0};
					sprintf_s(temp, 32 - 1, "secondValue%d", i);
					attr->SetAttribute(temp, attribute->secondAttrs[i]);
				}
			}
		}
	}
	
	TString resultFileName;
	if(!GetResultFileName(fileName_, resultFileName))
		return false;
	name = ToAnsi(resultFileName);
	 return doc.SaveFile(name.c_str());
	//doc.SaveFile("D:\\CharacterBaseSecondAttribute.config.config");//config����·��

	//return true;
}

void CXinfaConverter::FindAttributeForClass(int classID, std::vector<BaseSecondAttribute> &attrs)
{
	attrs.clear();
	for (int i = 0; i < mBaseSecondAttrs.size(); ++i)
	{
		if (mBaseSecondAttrs[i].TypeID == classID)
			attrs.push_back(mBaseSecondAttrs[i]);
	}
}

void CXinfaConverter::FindAttributeForXinFa(std::string name,std::vector<XinFaAttribute> &attrs)
{
	attrs.clear();
	for (int i = 0;i < mXinFaAttrs.size();++i)
	{
		if (mXinFaAttrs[i].XFProfession == name)
		{
			attrs.push_back(mXinFaAttrs[i]);
		}
	}
}




//----------------------
namespace 
{
	IConverter *CreateXinfaConverter(void)

	{
		return new CXinfaConverter;



	}


	const bool ret_xinfaConverter = TheConverterFactory.Register(_T("xinfaConverter"), CreateXinfaConverter);
}

//
//IConverter *CreateXinfaConverter(void)
//{
//	return new CXinfaConverter;
//}
//
//const bool ret_xinfaConverter = TheConverterFactory.Register(_T("xinfaConverter"), CreateXinfaConverter);