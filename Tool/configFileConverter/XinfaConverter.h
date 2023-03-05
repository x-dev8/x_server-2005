/*------------------------------------------------------------------------
Desc		: 心法文件转换器。
Author		: zilong
Version		: 1.0
Date		: 2011-03-08
Revision	:
-------------------------------------------------------------------------*/
#ifndef _XINFA_CONVERTER_
#define _XINFA_CONVERTER_

#include <vector>

#include "IConverter.h"

struct BaseSecondAttribute
{
	int TypeID;
	char ClassName[32];
	int Level;
	int baseAttrs[5];
	int secondAttrs[12];
};


struct XinFaAttribute
{
	int	 XFID;
	int	 XFLevel;
	int	 XFIconID;
	char XFName[32];
	char XFDesc[1024];
	int	 XFPrev;
	char XFProfession[32];
	int  XFNeedLevel;
	int	 XFMoney;
	int  XFEXP;
	char XFAttrType1[32];
	int  XFAttrValue1;
	char XFAttrType2[32];
	int	 XFAttrValue2;
	int	 SKID;
	int  SKLevel;
	char SKAttrType1[32];
	int  SKAttrValue1;
	char SKAttrType2[32];
	int  SKAttrValue2;

	int	 SKID1;
	int  SKLevel1;
	char SKAttrType1_1[32];
	int  SKAttrValue1_1;
	char SKAttrType2_1[32];
	int  SKAttrValue2_1;

	int	 SKID2;
	int  SKLevel2;
	char SKAttrType1_2[32];
	int  SKAttrValue1_2;
	char SKAttrType2_2[32];
	int  SKAttrValue2_2;

	int	 SKID3;
	int  SKLevel3;
	char SKAttrType1_3[32];
	int  SKAttrValue1_3;
	char SKAttrType2_3[32];
	int  SKAttrValue2_3;
};

enum BaseSecondAttrCol
{
	TypeIDCol = 1,
	ClassNameCol,
	LevelCol,
	BaseAttrsCol,
	SecondAttrsCol = 8
};

enum XinFaAttrCol
{
	XinFaID = 1,
	XFLearningLevels,
	IconID,
	XinFaName,
	XinFaDesc,
	XinFaPrev,
	XinFaNeedProfession,
	XinFaNeedLevel,
	XinFaNeedMoney,
	XinFaNeedExp,
	CharAttrType1,
	CharAttrValue1,
	CharAttrType2,
	CharAttrValue2,
	SillkID,
	SillkLevel,
	AttrType1,
	AttrValue1,
	AttrType2,
	AttrValue2,
	SillkID1,
	SillkLevel1,
	AttrType1_1,
	AttrValue1_1,
	AttrType2_1,
	AttrValue2_1,
	SillkID2,
	SillkLevel2,
	AttrType1_2,
	AttrValue1_2,
	AttrType2_2,
	AttrValue2_2,
	SillkID3,
	SillkLevel3,
	AttrType1_3,
	AttrValue1_3,
	AttrType2_3,
	AttrValue2_3
};

static const char *XINFA_CLASS_NAMES[] =
{
	"Warrior", "Mage", "Taoist", "Assassin", "Hunter", "Sniper"
};

class CXinfaConverter: public IConverter
{
public:
	CXinfaConverter(void);
	virtual ~CXinfaConverter(void);

	virtual bool InitElementInfo(const TCHAR *fileName_ = NULL);

protected:
	virtual bool LoadFile(const TString &fileName_, TXmlElementValues &_elementValues);
	virtual bool LoadSlkFile(const TString &fileName_, TXmlElementValues &_elementValues);
	virtual bool LoadXinFile(const TString &fileName_,TXmlElementValues &_elementValues);

protected:
	void FindAttributeForClass(int classID, std::vector<BaseSecondAttribute> &attrs);
	void FindAttributeForXinFa(std::string name,std::vector<XinFaAttribute> &attrs);

private:
	std::vector<BaseSecondAttribute> mBaseSecondAttrs;
	std::vector<XinFaAttribute> mXinFaAttrs;
};

#endif