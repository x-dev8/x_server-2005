#pragma once
#include "Pack.h"
#include "bag\ItemBag2.h"
#include "SuitOperateConfig.h"
#include "MeUi/Animation/SlideAnimation.h"

class CFiveXingBase
{
public:
    CFiveXingBase(void);
    ~CFiveXingBase(void);


    enum eFiveXing
    {
        enum_FiveXingItem,       //���е���
        enum_FiveXingElement,    //��������
        enum_FiveXingMaterial,   //���в���
        enum_FiveXingExploit,    //��ѫ��������

        enum_FiveXingMax     //���ֵ
    };

    enum eFiveXingTrans
    {
        enum_FiveXingTransItem,     //����ת�Ƶ���
        enum_FiveXingTransAimItem,  //����ת��Ŀ�����
        enum_FiveXingTransStone,    //����ת��ת��ʯ
        enum_FiveXingTransHelper,   //����ת��ף��ʯ

        enum_FiveXingTransMax      //����ת�����ֵ
    };

    //���ڼ�¼�����ڽ����ϵĵ���
    struct FiveXingItem
    {
        int m_nIndex;        //��������
        int m_eBagType;      //��������
        __int64 m_nGuid;     //���ߵ�GUID

        FiveXingItem()
        {
            m_nIndex = -1;
            m_eBagType = -1;
            m_nGuid    = 0;
        }
    };

    bool IsFiveXingItem(unsigned short usItemID,unsigned char  ucItemType,unsigned char ucItemTypeSecond,unsigned char ucItemTypeThrid,char* pszTip);
    void UpdatePackItemEnable(CItemBag2 &bag,int nOldIndex,int nNewIndex,int bagType); //���±��������Ƿ����ʹ��

    virtual void Init()  = 0;        //��ʼ������
    virtual void Clear() = 0;        //�������

    void UpdateMoneyByItem(SCharItem* pItem,std::string &strText,bool bLevelUp);       //ͨ�����߸���Ǯ��
    void UpdateMoney(DWORD dwMoney,std::string& strText); //��������Ҫ��Ǯ��
    void UpdataItem(ControlListImage* pImg,ControlIconDrag::S_ListImg*  pListImg,int nCount = 1);  //������Ҫ���ǵĵ���
    bool IsMoneyEnough(SCharItem* pItem,bool bLevelUp);

    void SetVisiblePosition(const Vector &vPos);  //���ÿ��������������
    bool IsOverDistance(const Vector& vCurPos);   //�Ƿ���Ҫ�رս���

    void SetFiveXingItem(ControlIconDrag::S_ListImg* pItemDrag,int nBagType,eFiveXing nIndex); //�������е���

    void ClearFiveXingItemByIndex(eFiveXing nIndex);

    bool IsFiveXingReputationItem(ControlIconDrag::S_ListImg* pItem);
    const ElementSuitLevelUp* GetChangeCostInfo();

    //------����-----------------------
    void InitAnim(RECT rc);  //��ʼ������
    void UpdateAnim(RECT rc);  //���¶���
    void PlayAnim();  //���Ŷ���
    void EndAnim();   //��������
    bool IsAnimOver(){return m_slideAnim.IsInAnimation();}

    void AnimationBegin(){m_isPlaying = true;}
    void AnimationEnd(){m_isPlaying = false;}
    bool IsAnimPlaying(){return m_isPlaying;}

    void BeginShowResult(){m_bCanShow = true;}
    void EndShowResult(){m_bCanShow = false;}
    bool IsCanShowResult(){return m_bCanShow;}
#ifdef _DEBUG
    void DebugInfo();
#endif
protected:
    Vector  m_vVisualPos;

    FiveXingItem   m_FiveXing[enum_FiveXingMax];

    CSlideAnimation m_slideAnim; //����֡����
    bool            m_isPlaying;   //�����Ƿ������
    bool            m_bCanShow;    //�Ƿ�����ʾ���н��
};
