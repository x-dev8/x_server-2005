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
        enum_FiveXingItem,       //五行道具
        enum_FiveXingElement,    //五行灵珠
        enum_FiveXingMaterial,   //五行材料
        enum_FiveXingExploit,    //功勋名望道具

        enum_FiveXingMax     //最大值
    };

    enum eFiveXingTrans
    {
        enum_FiveXingTransItem,     //五行转移道具
        enum_FiveXingTransAimItem,  //五行转移目标道具
        enum_FiveXingTransStone,    //五行转移转移石
        enum_FiveXingTransHelper,   //五行转移祝福石

        enum_FiveXingTransMax      //五行转移最大值
    };

    //用于记录放置在界面上的道具
    struct FiveXingItem
    {
        int m_nIndex;        //背包索引
        int m_eBagType;      //背包类型
        __int64 m_nGuid;     //道具的GUID

        FiveXingItem()
        {
            m_nIndex = -1;
            m_eBagType = -1;
            m_nGuid    = 0;
        }
    };

    bool IsFiveXingItem(unsigned short usItemID,unsigned char  ucItemType,unsigned char ucItemTypeSecond,unsigned char ucItemTypeThrid,char* pszTip);
    void UpdatePackItemEnable(CItemBag2 &bag,int nOldIndex,int nNewIndex,int bagType); //更新背包道具是否可以使用

    virtual void Init()  = 0;        //初始化数据
    virtual void Clear() = 0;        //清空数据

    void UpdateMoneyByItem(SCharItem* pItem,std::string &strText,bool bLevelUp);       //通过道具更新钱币
    void UpdateMoney(DWORD dwMoney,std::string& strText); //更新所需要的钱币
    void UpdataItem(ControlListImage* pImg,ControlIconDrag::S_ListImg*  pListImg,int nCount = 1);  //更新需要升星的道具
    bool IsMoneyEnough(SCharItem* pItem,bool bLevelUp);

    void SetVisiblePosition(const Vector &vPos);  //设置开启界面玩家坐标
    bool IsOverDistance(const Vector& vCurPos);   //是否需要关闭界面

    void SetFiveXingItem(ControlIconDrag::S_ListImg* pItemDrag,int nBagType,eFiveXing nIndex); //设置五行道具

    void ClearFiveXingItemByIndex(eFiveXing nIndex);

    bool IsFiveXingReputationItem(ControlIconDrag::S_ListImg* pItem);
    const ElementSuitLevelUp* GetChangeCostInfo();

    //------动画-----------------------
    void InitAnim(RECT rc);  //初始化动画
    void UpdateAnim(RECT rc);  //更新动画
    void PlayAnim();  //播放动画
    void EndAnim();   //结束动画
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

    CSlideAnimation m_slideAnim; //序列帧动画
    bool            m_isPlaying;   //动画是否进行中
    bool            m_bCanShow;    //是否能显示五行结果
};
