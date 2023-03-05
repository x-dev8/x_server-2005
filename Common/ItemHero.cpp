#include "ItemHero.h"
#include "SlkReader.h"
#include "ErrorLog.h"
#include "ItemDetail.h"
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"

#ifdef _CLIENT_
#include "Me3d/Global.h"
#endif

bool CItemHeroString::LoadHeroString(const char* filename)
{
	if (filename == NULL || *filename == 0)
	{
		return false;
	}
	
	MeXmlDocument xMeXmlDoc;
	if (!xMeXmlDoc.LoadFile(filename))
	{
		return false;
	}

	MeXmlElement *pRoot = xMeXmlDoc.FirstChildElement("Project");
	if (pRoot)
	{
		pRoot = pRoot->FirstChildElement("Strings");
	}
	else
	{
		pRoot = xMeXmlDoc.FirstChildElement("Strings");
	}

	if (pRoot == NULL)
	{
		return false;
	}

	MeXmlElement *pElement = pRoot->FirstChildElement("String");
	int nId = 1;
	string strHero = "";
	while(pElement != NULL)
	{
		pElement->Attribute("ID",&nId);

		Common::_tstring strValue;
		strValue.fromUTF8(pElement->Attribute("Value"));
		strHero = strValue;
		
		m__mapHeroString.insert(make_pair(nId,strHero));
		
		pElement = pElement->NextSiblingElement();

	}

	return true;
}

const char* CItemHeroString::GetStringById(int32 id)
{
	_mapHeroString::iterator itr = m__mapHeroString.find(id);
	if (itr != m__mapHeroString.end())
		return itr->second.c_str();	
	return "";
}

CItemHeroString::CItemHeroString()
{
	m__mapHeroString.clear();
}

CItemHeroString::~CItemHeroString()
{
	m__mapHeroString.clear();
}

CItemHero::CItemHero()
{

}

CItemHero::~CItemHero()
{
	_mapItemHeroHeroId.clear();
	_mapItemHeroItemId.clear();
	mZhujiangExtraInfos.clear();
}

CItemHero::SItemHero* CItemHero::FindHeroByItemID(unsigned short item_id)
{
	if (item_id == INVALID_HERO_ID)
	{
		return  NULL;
	}

	mapItemHero::iterator itr = _mapItemHeroItemId.find(item_id);
	if (itr == _mapItemHeroItemId.end())
	{
		return NULL;
	}

	return &(itr->second);
}

CItemHero::SItemHero* CItemHero::FindHeroByHeroID(unsigned short hero_id)
{
	if (hero_id == INVALID_HERO_ID)
	{
		return  NULL;
	}

	mapItemHero::iterator itr = _mapItemHeroHeroId.find(hero_id);
	if (itr == _mapItemHeroHeroId.end())
	{
		return NULL;
	}

	return &(itr->second);
}

CItemHero::ZhujiangExtraInfo * CItemHero::FindZhujiangExtraInfo(unsigned char profession, unsigned sex)
{
	size_t len = mZhujiangExtraInfos.size();
	for (size_t i = 0; i < len; ++i)
	{
		CItemHero::ZhujiangExtraInfo *ei = &mZhujiangExtraInfos[i];
		if (ei->Class == profession && ei->Gender == sex)
			return ei;
	}
	return NULL;
}

bool CItemHero::LoadHeroItemSlk(const char *szFileName)
{
	CSlkReader pReader;
	if (!pReader.ReadFromFile(szFileName))
	{
		return false;
	}

	int iRow = 3;
	int iCol = 0;
	int iRet = 0;
	int iValve = 0;
	float fValue = 0.0f;
	

	Common::_tstring strheroname;
	Common::_tstring strheronamePic;
	//Common::_tstring strheadmalepic;
	//Common::_tstring strheadmfemalepic;
	Common::_tstring strHeadaddr;
	Common::_tstring strBSaddr;
	Common::_tstring strTJaddr;
	Common::_tstring strBPaddr;
	Common::_tstring striconaddr;
	Common::_tstring strexplain;
	Common::_tstring strproperty;
	Common::_tstring strpropertyPic;
	Common::_tstring strfuse;

	while ( CSlkReader::ret_readover != (iRet = pReader.GotoNextLine(iRow++) ) )
	{
		if ( CSlkReader::ret_nothisline == iRet)
			continue;
		
		
		/*SItemHero* pHero = (SItemHero*)GettheItemDetail().AllocItem(0,sizeof(SItemHero));
		if( !pHero)
		{
			OutputSlkLoadingMessage("Error:����Hero��Ҫ���ڴ���� [%d]\r\n", iRow );
			return false;
		}*/
		SItemHero pHero;
		int iCol = 1;

		//hero_id
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage("\t��������ID ����!\r\n");
			GetErrorLog()->logString("SanGuoLord.slk ��%d������hero_id����", iRow);
			goto load_error;
		}
		pHero.hero_id = iValve;
		iCol++;

		//hero_name
		if (!pReader.GetStringFieldByName("Name",strheroname))
		{
			OutputSlkLoadingMessage("\t ����-�������� [%s]-����!\r\n",strheroname);
			goto load_error;
		}
		pHero.hero_name = strheroname.toUTF8().c_str();
		iCol++;

		//NamePicAddr
		if (!pReader.GetStringFieldByName("NamePicAddr",strheronamePic))
		{
			OutputSlkLoadingMessage("\t ����-��������ͼƬ [%s]-����!\r\n",strheronamePic);
			goto load_error;
		}
		pHero.namePicAddr = strheronamePic.toUTF8().c_str();
		iCol++;

		//hero_sex
		if (!pReader.GetIntField(iCol,iValve))
		{

			OutputSlkLoadingMessage("\t ����-�����Ա� [%s]-����!\r\n",iValve);
			goto load_error;
		}
		//pHero.hero_sex = cherosex;
		pHero.hero_sex = iValve;
		iCol++;

		//itemd_id
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage("\t�����Ӧ����ID ����!\r\n");
			GetErrorLog()->logString("SanGuoLord.slk ��%d������itemd_id����", iRow);
			goto load_error;
		}
		pHero.itemd_id = iValve;
		iCol++;

		//need_lv
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage("\t������Ʒ����ʹ�õȼ� ����!\r\n");
			GetErrorLog()->logString("SanGuoLord.slk ��%d������itemd_id����", iRow);
			goto load_error;
		}
		pHero.need_lv = iValve;
		iCol++;

		//material_id
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage("\t������Ʒ�������ID ����!\r\n");
			GetErrorLog()->logString("SanGuoLord.slk ��%d������material_id����", iRow);
			goto load_error;
		}
		pHero.material_id = iValve;
		iCol++;

		//material_count
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage("\t������Ʒ����������� ����!\r\n");
			GetErrorLog()->logString("SanGuoLord.slk ��%d������material_count����", iRow);
			goto load_error;
		}
		pHero.material_count = iValve;
		iCol++;
		

		//need_money
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t ���� �����Ǯ ����!\r\n" );
			goto load_error;
		}
		pHero.need_money = iValve;
		iCol++;

		////head_malepic
		//if (!pReader.GetStringFieldByName("headmalepic",strheadmalepic))
		//{
		//	OutputSlkLoadingMessage( "\t ����-������ͷ�� [%s]-����!\r\n", strheadmalepic );
		//	goto load_error;
		//}
		//pHero.head_malepic =strheadmalepic.toUTF8().c_str();
		//iCol++;

		////head_femalepic
		//if (!pReader.GetStringFieldByName("headfemalepic",strheadmfemalepic))
		//{
		//	OutputSlkLoadingMessage( "\t ����-Ů����ͷ�� [%s]-����!\r\n", strheadmfemalepic );
		//	goto load_error;
		//}
		//pHero.head_femalepic =strheadmfemalepic.toUTF8().c_str();
		//iCol++;
		
		//Pic_Head
		if (!pReader.GetStringFieldByName("HeadPic",strHeadaddr))
		{
			OutputSlkLoadingMessage("\t ����-����ͷ����Դ [%s]-����!\r\n",strHeadaddr);
			goto load_error;
		}
		pHero.Pic_Head = strHeadaddr.toUTF8().c_str();
		iCol++;

		//Pic_BianShenUI
		if (!pReader.GetStringFieldByName("BianShenUIPic",strBSaddr))
		{
			OutputSlkLoadingMessage("\t ����-��������ͼ�� [%s]-����!\r\n",strBSaddr);
			goto load_error;
		}
		pHero.Pic_BianShenUI = strBSaddr.toUTF8().c_str();
		iCol++;

		//Pic_TuJianUI
		if (!pReader.GetStringFieldByName("TuJianUIPic",strTJaddr))
		{
			OutputSlkLoadingMessage("\t ����-����ͼ��ͷ�� [%s]-����!\r\n",strTJaddr);
			goto load_error;
		}
		pHero.Pic_TuJianUI = strTJaddr.toUTF8().c_str();
		iCol++;

		//Pic_BasePro
		if (!pReader.GetStringFieldByName("BaseProUIPic",strBPaddr))
		{
			OutputSlkLoadingMessage("\t ����-������������ͷ�� [%s]-����!\r\n",strBPaddr);
			goto load_error;
		}
		pHero.Pic_BasePro = strBPaddr.toUTF8().c_str();
		iCol++;

		//icon_addr
		if (!pReader.GetStringFieldByName("iconaddr",striconaddr))
		{
			OutputSlkLoadingMessage("\t ����-����������άͼ [%s]-����!\r\n",striconaddr);
			goto load_error;
		}
		pHero.icon_addr = striconaddr.toUTF8().c_str();
		iCol++;

		//explain_hero
		if (!pReader.GetStringFieldByName("Explain",strexplain))
		{
			OutputSlkLoadingMessage("\t ����-�������Ǽ�� [%s]-����!\r\n",strexplain);
			goto load_error;
		}
		pHero.explain_hero = strexplain.toUTF8().c_str();
		iCol++;

		//property_hero
		if (!pReader.GetStringFieldByName("Property",strproperty))
		{
			OutputSlkLoadingMessage("\t ����-������������ [%s]-����!\r\n",strproperty);
			goto load_error;
		}
		pHero.property_hero = strproperty.toUTF8().c_str();
		iCol++;

		//proPicAddr
		if (!pReader.GetStringFieldByName("ProPicAddr",strpropertyPic))
		{
			OutputSlkLoadingMessage("\t ����-������������ͼƬ [%s]-����!\r\n",strpropertyPic);
			goto load_error;
		}
		pHero.proPicAddr = strpropertyPic.toUTF8().c_str();
		iCol++;

		//hero_skill1
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t ������������1����!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d��������������1����", iRow );
			goto load_error;
		}
		pHero.hero_skill1 = iValve;
		iCol++;

		//hero_skill2
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t ������������2����!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d��������������2����", iRow );
			goto load_error;
		}
		pHero.hero_skill2 = iValve;
		iCol++;

		//hero_skill3
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t ������������3����!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d��������������3����", iRow );
			goto load_error;
		}
		pHero.hero_skill3 = iValve;
		iCol++;

		//skill1_lv
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t ������������1�ȼ�����!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d��������������1�ȼ�����", iRow );
			goto load_error;
		}
		pHero.skill1_lv = iValve;
		iCol++;
		
		//skill2_lv
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t ������������2�ȼ�����!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d��������������2�ȼ�����", iRow );
			goto load_error;
		}
		pHero.skill2_lv = iValve;
		iCol++;

		//skill3_lv
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t ������������3�ȼ�����!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d��������������3�ȼ�����", iRow );
			goto load_error;
		}
		pHero.skill3_lv = iValve;
		iCol++;

		//hero_wuli
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t �������������츳���ٷֱȳ���!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d���������������츳�ٷֱȳ���", iRow );
			goto load_error;
		}
		pHero.heroAttrPer[EBaseAttr_Strength] = iValve;
		iCol++;

		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t �������������츳������!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d���������������츳����", iRow );
			goto load_error;
		}
		pHero.heroAttr[EBaseAttr_Strength] = iValve;
		iCol++;

		//hero_zhili
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t �������������츳���ٷֱȳ���!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d���������������츳�ٷֱȳ���", iRow );
			goto load_error;
		}
		pHero.heroAttrPer[EBaseAttr_Intelligence] = iValve;
		iCol++;

		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t �������������츳������!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d���������������츳����", iRow );
			goto load_error;
		}
		pHero.heroAttr[EBaseAttr_Intelligence] = iValve;
		iCol++;
	
		//hero_tongyuli
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t ��������ͳ�����츳���ٷֱȳ���!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d����������ͳ�����츳�ٷֱȳ���", iRow );
			goto load_error;
		}
		pHero.heroAttrPer[EBaseAttr_Stamina] = iValve;
		iCol++;

		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t ��������ͳ�����츳������!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d����������ͳ�����츳����", iRow );
			goto load_error;
		}
		pHero.heroAttr[EBaseAttr_Stamina] = iValve;
		iCol++;

		//hero_shenfa
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t �����������츳���ٷֱȳ���!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d�������������츳�ٷֱȳ���", iRow );
			goto load_error;
		}
		pHero.heroAttrPer[EBaseAttr_Agility] = iValve;
		iCol++;

		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t �����������츳������!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d�������������츳����", iRow );
			goto load_error;
		}
		pHero.heroAttr[EBaseAttr_Agility] = iValve;
		iCol++;

		//hero_lianxing
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t �����������ͳ���!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d�������������ͳ���", iRow );
			goto load_error;
		}
		pHero.hero_lianxing = iValve;
		iCol++;

		//hero_faxing
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t �����������ͳ���!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d�������������ͳ���", iRow );
			goto load_error;
		}
		pHero.hero_faxing = iValve;
		iCol++;

		//hero_fuse
		if (!pReader.GetStringFieldByName("BianshenFuse",strfuse))
		{
			OutputSlkLoadingMessage("\t ����-������ɫ [%s]-����!\r\n",strfuse);
			goto load_error;
			
		}
		pHero.hero_fuse = strfuse;
		iCol++;

		//hero_rate
		if (!pReader.GetFloatField(iCol,fValue))
		{
			OutputSlkLoadingMessage( "\t �������������츳������!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d������������ɫ����", iRow );
			goto load_error;
		}
		pHero.hero_rate = fValue;
		iCol++;	

		//TellOther
		if (!pReader.GetIntField(iCol,iValve))
		{
			OutputSlkLoadingMessage( "\t ����㲥��־����!\r\n" );
			GetErrorLog()->logString( " SanguoLord.slk ��%d������㲥��־����", iRow );
			goto load_error;
		}
		pHero.TellOther = iValve;
		iCol++;

		_mapItemHeroHeroId.insert(mapItemHero::value_type(pHero.hero_id,pHero));
		continue;
load_error:
		OutputSlkLoadingMessage( "\t SanguoLord.slk �� %d ������ʧ��!\r\n",iRow-1 );
		return false;
	}

	return true;
}


bool CItemHero::SaveHeroConfig(const char* szFileName,const char* szStringName)
{
	if (szFileName == NULL || *szFileName == 0)
	{
		return false;
	}

	MeXmlDocument saveHeroMeXml;
	MeXmlDocument saveHeroString;
	saveHeroString.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));
	saveHeroMeXml.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));


	MeXmlElement* pStrRoot = saveHeroString.InsertEndChild(("Strings"))->ToElement();
	if (pStrRoot == NULL)
	{
		return false;
	}

	mapItemHero::iterator strBegin = _mapItemHeroHeroId.begin();
	mapItemHero::iterator strEnd = _mapItemHeroHeroId.end();


	for (;strBegin != strEnd;++strBegin)
	{
		/*if ((*strBegin).second == NULL)
		{
			continue;
		}*/

		SItemHero *pHerostr = &(strBegin->second);
		MeXmlElement *pHeroName = pStrRoot->InsertEndChild(("String"))->ToElement();
		if (pHeroName == NULL)
		{
			continue;
		}
		
	
		pHeroName->SetAttribute("ID",(pHerostr->hero_id+10000));
		pHeroName->SetAttribute("Value",pHerostr->hero_name.c_str());
		if ((pHerostr->hero_id+10000) >= 20000)
		{
			return false;
		}
		


		MeXmlElement *pHeroExplain = pStrRoot->InsertEndChild(("String"))->ToElement();
		if (pHeroExplain == NULL)
		{
			continue;
		}

		
		
		pHeroExplain->SetAttribute("ID",(pHerostr->hero_id+20000));
		pHeroExplain->SetAttribute("Value",pHerostr->explain_hero.c_str());
		if ((pHerostr->hero_id+20000) >= 30000)
		{
			return false;
		}
		
	
		MeXmlElement *pHeroProperty= pStrRoot->InsertEndChild(("String"))->ToElement();
		if (pHeroProperty == NULL)
		{
			continue;
		}

		pHeroProperty->SetAttribute("ID",(pHerostr->hero_id+30000));
		pHeroProperty->SetAttribute("Value",pHerostr->property_hero.c_str());
	
		if ((pHerostr->hero_id+30000) >= 40000)
		{
			return false;
		}
	 
	}
	//string FileName = szFileName + "string";
	saveHeroString.SaveFile(szStringName);

	MeXmlElement* pRoot = saveHeroMeXml.InsertEndChild(("Project"))->ToElement();
	if (pRoot == NULL)
	{
		return false;
	}


	mapItemHero::iterator iterBegin = _mapItemHeroHeroId.begin();
	mapItemHero::iterator iterEnd = _mapItemHeroHeroId.end();

	for (;iterBegin != iterEnd; ++iterBegin)
	{
		/*if ((*iterBegin).second == NULL)
		{
			continue;
		}*/
		
		SItemHero *pHeroIter = &(iterBegin->second);

		MeXmlElement *pHero = pRoot->InsertEndChild(("Hero"))->ToElement();
		if (pHero == NULL)
		{
			continue;
		}

		pHero->SetAttribute("ID",pHeroIter->hero_id);

		pHero->SetAttribute("Name",(pHeroIter->hero_id+10000));

		pHero->SetAttribute("NamePicAddr",pHeroIter->namePicAddr.c_str());

		pHero->SetAttribute("Sex",pHeroIter->hero_sex);

		pHero->SetAttribute("ItemdID",pHeroIter->itemd_id);

		pHero->SetAttribute("needlevel",pHeroIter->need_lv);

		pHero->SetAttribute("MaterialID",pHeroIter->material_id);

		pHero->SetAttribute("count",pHeroIter->material_count);

		pHero->SetAttribute("Money",pHeroIter->need_money);

		//pHero->SetAttribute("headmalepic",pHeroIter->head_malepic.c_str());

		//pHero->SetAttribute("headfemalepic",pHeroIter->head_femalepic.c_str());

		pHero->SetAttribute("HeadPic",pHeroIter->Pic_Head.c_str());
		pHero->SetAttribute("BianShenUIPic",pHeroIter->Pic_BianShenUI.c_str());
		pHero->SetAttribute("TuJianUIPic",pHeroIter->Pic_TuJianUI.c_str());
		pHero->SetAttribute("BaseProUIPic",pHeroIter->Pic_BasePro.c_str());

		pHero->SetAttribute("iconaddr",pHeroIter->icon_addr.c_str());

		pHero->SetAttribute("Explain",(pHeroIter->hero_id+20000));

		pHero->SetAttribute("Property",(pHeroIter->hero_id+30000));

		pHero->SetAttribute("ProPicAddr",pHeroIter->proPicAddr.c_str());

		pHero->SetAttribute("Skill1",pHeroIter->hero_skill1);

		pHero->SetAttribute("Skill2",pHeroIter->hero_skill2);

		pHero->SetAttribute("Skill3",pHeroIter->hero_skill3);

		pHero->SetAttribute("Skilllv1",pHeroIter->skill1_lv);

		pHero->SetAttribute("Skilllv2",pHeroIter->skill2_lv);

		pHero->SetAttribute("Skilllv3",pHeroIter->skill3_lv);

		pHero->SetAttribute("WuliPer",pHeroIter->heroAttrPer[EBaseAttr_Strength]);

		pHero->SetAttribute("Wuli",pHeroIter->heroAttr[EBaseAttr_Strength]);

		pHero->SetAttribute("ZhiliPer",pHeroIter->heroAttrPer[EBaseAttr_Intelligence]);

		pHero->SetAttribute("Zhili",pHeroIter->heroAttr[EBaseAttr_Intelligence]);

		pHero->SetAttribute("TongyuPer",pHeroIter->heroAttrPer[EBaseAttr_Stamina]);
		
		pHero->SetAttribute("Tongyu",pHeroIter->heroAttr[EBaseAttr_Stamina]);

		pHero->SetAttribute("ShenfaPer",pHeroIter->heroAttrPer[EBaseAttr_Agility]);

		pHero->SetAttribute("Shenfa",pHeroIter->heroAttr[EBaseAttr_Agility]);

		pHero->SetAttribute("BianshenLianxing",pHeroIter->hero_lianxing);
	
		pHero->SetAttribute("BianshenFaxing",pHeroIter->hero_faxing);

		pHero->SetAttribute("BianshenFuse",pHeroIter->hero_fuse.c_str());

		pHero->SetDoubleAttribute("rate",pHeroIter->hero_rate);

		pHero->SetAttribute("TellOther",pHeroIter->TellOther);
	}
	
	return  saveHeroMeXml.SaveFile(szFileName);
}


bool CItemHero::LoadHeroConfig(const char* szFileName,const char* stringName)
{
	if (!TheHeroString.LoadHeroString(stringName))
	{
		return false;
	}
	
	if (szFileName == NULL)
	{
		return false;
	}

	MeXmlDocument mHeroXmlDoc;
	if (!mHeroXmlDoc.LoadFile(szFileName))
	{
		return false;
	}

	MeXmlElement* pRoot = mHeroXmlDoc.FirstChildElement("Project");
	if (pRoot == NULL)
	{
		return false;
	}

	MeXmlElement* pItemHero = pRoot->FirstChildElement("Hero");

	int iValue = 0;
	double dValue = 0.000000;
	while (pItemHero != NULL)
	{
		//SItemHero *pHero = (SItemHero*)GettheItemDetail().AllocItem(0,sizeof(SItemHero));
		SItemHero pHero;
		if (pItemHero->Attribute("ID",&iValue) == NULL)
		{
			return false;
		}
		pHero.hero_id = iValue;
		
		/*Common::_tstring strHeroname;
		strHeroname.fromUTF8(pItemHero->Attribute("Name"));*/
		pHero.hero_name = TheHeroString.GetStringById(pHero.hero_id+10000);

		Common::_tstring strNamepic;
		strNamepic.fromUTF8(pItemHero->Attribute("NamePicAddr"));
		pHero.namePicAddr = strNamepic.c_str();

		pItemHero->Attribute("Sex",&iValue);
		pHero.hero_sex = iValue;

		pItemHero->Attribute("ItemdID",&iValue);
		pHero.itemd_id = iValue;

		pItemHero->Attribute("needlevel",&iValue);
		pHero.need_lv = iValue;

		pItemHero->Attribute("MaterialID",&iValue);
		pHero.material_id = iValue;

		pItemHero->Attribute("count",&iValue);
		pHero.material_count = iValue;

		pItemHero->Attribute("Money",&iValue);
		pHero.need_money = iValue;

		/*Common::_tstring strHeromalepic;
		strHeromalepic.fromUTF8(pItemHero->Attribute("headmalepic"));
		pHero.head_malepic = strHeromalepic.c_str();

		Common::_tstring strHerofemalepic;
		strHerofemalepic.fromUTF8(pItemHero->Attribute("headfemalepic"));
		pHero.head_femalepic = strHerofemalepic.c_str();*/

		Common::_tstring strHeadaddr;
		strHeadaddr.fromUTF8(pItemHero->Attribute("HeadPic"));
		pHero.Pic_Head = strHeadaddr.c_str();

		Common::_tstring strBSaddr;
		strBSaddr.fromUTF8(pItemHero->Attribute("BianShenUIPic"));
		pHero.Pic_BianShenUI = strBSaddr.c_str();

		Common::_tstring strTJaddr;
		strTJaddr.fromUTF8(pItemHero->Attribute("TuJianUIPic"));
		pHero.Pic_TuJianUI = strTJaddr.c_str();

		Common::_tstring strBPaddr;
		strBPaddr.fromUTF8(pItemHero->Attribute("BaseProUIPic"));
		pHero.Pic_BasePro = strBPaddr.c_str();

		Common::_tstring striConaddr;
		striConaddr.fromUTF8(pItemHero->Attribute("iconaddr"));
		pHero.icon_addr = striConaddr.c_str();

		/*Common::_tstring strExplain;
		strExplain.fromUTF8(pItemHero->Attribute("Explain"));*/
		pHero.explain_hero =TheHeroString.GetStringById(pHero.hero_id+20000);

	/*	Common::_tstring strProperty;
		strProperty.fromUTF8(pItemHero->Attribute("Property"));*/
		pHero.property_hero = TheHeroString.GetStringById(pHero.hero_id+30000);

		Common::_tstring strPropic;
		strPropic.fromUTF8(pItemHero->Attribute("ProPicAddr"));
		pHero.proPicAddr = strPropic.c_str();

		pItemHero->Attribute("Skill1",&iValue);
		pHero.hero_skill1 = iValue;

		pItemHero->Attribute("Skill2",&iValue);
		pHero.hero_skill2 = iValue;

		pItemHero->Attribute("Skill3",&iValue);
		pHero.hero_skill3 = iValue;
			
		pItemHero->Attribute("Skilllv1",&iValue);
		pHero.skill1_lv = iValue;

		pItemHero->Attribute("Skilllv2",&iValue);
		pHero.skill2_lv = iValue;

		pItemHero->Attribute("Skilllv3",&iValue);
		pHero.skill3_lv = iValue;

		pItemHero->Attribute("WuliPer",&iValue);
		pHero.heroAttrPer[EBaseAttr_Strength] = iValue;

		pItemHero->Attribute("Wuli",&iValue);
		pHero.heroAttr[EBaseAttr_Strength] = iValue;

		pItemHero->Attribute("ZhiliPer",&iValue);
		pHero.heroAttrPer[EBaseAttr_Intelligence] = iValue;

		pItemHero->Attribute("Zhili",&iValue);
		pHero.heroAttr[EBaseAttr_Intelligence] = iValue;

		pItemHero->Attribute("TongyuPer",&iValue);
		pHero.heroAttrPer[EBaseAttr_Stamina] = iValue;

		pItemHero->Attribute("Tongyu",&iValue);
		pHero.heroAttr[EBaseAttr_Stamina] = iValue;

		pItemHero->Attribute("ShenfaPer",&iValue);
		pHero.heroAttrPer[EBaseAttr_Agility] = iValue;

		pItemHero->Attribute("Shenfa",&iValue);
		pHero.heroAttr[EBaseAttr_Agility] = iValue;
		
		pItemHero->Attribute("BianshenLianxing",&iValue);
		pHero.hero_lianxing = iValue;

		pItemHero->Attribute("BianshenFaxing",&iValue);
		pHero.hero_faxing = iValue;

		Common::_tstring strFuse;
		strFuse.fromUTF8(pItemHero->Attribute("BianshenFuse"));
		pHero.hero_fuse =strFuse;

		pItemHero->Attribute("rate",&dValue);
		pHero.hero_rate = dValue;

		pItemHero->Attribute("TellOher",&iValue);
		pHero.TellOther = iValue;

		_mapItemHeroItemId.insert(make_pair(pHero.itemd_id,pHero));
		_mapItemHeroHeroId.insert(make_pair(pHero.hero_id,pHero));

		pItemHero = pItemHero->NextSiblingElement();
		
	}
	//TheHeroString.m__mapHeroString.clear();

#ifdef _CLIENT_
	// ��GameSetting�ж�ȡ�����Ķ�����Ϣ
	char szFilename[MAX_PATH] = {0};
	sprintf_s(szFilename, MAX_PATH - 1, "%s/Data/ClientConfig/GameSetting.config", GetRootPath());
	MeXmlDocument doc;
	if (!doc.LoadFile(szFilename))
		return false;

	MeXmlElement *rootElement = doc.RootElement();
	if (rootElement == NULL)
		return false;

	MeXmlElement *zhujiangElement = rootElement->FirstChildElement("ZhujiangConfig");
	if (zhujiangElement != NULL)
	{
		MeXmlElement *zj = zhujiangElement->FirstChildElement("Zhujiang");
		while (zj != NULL)
		{
			ZhujiangExtraInfo ei;

			zj->QueryIntAttribute("Profession", &iValue);
			ei.Class = iValue;

			zj->QueryIntAttribute("Sex", &iValue);
			ei.Gender = iValue;

			ei.Effect = zj->Attribute("Effect");

			zj->QueryIntAttribute("SceneActionID", &iValue);
			ei.SceneActionID = iValue;

			mZhujiangExtraInfos.push_back(ei);
			zj = zj->NextSiblingElement();
		}
	}
#endif

	return true;
}
