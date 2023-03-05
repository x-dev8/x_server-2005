#ifndef __MONSTER_QUAD_DLG_H__
#define __MONSTER_QUAD_DLG_H__

#include <afxwin.h>
#include <afxcmn.h>

#include <vector>
#include <algorithm>

#include "ItemDetail.h"

#define DECIMAL_STR_FORMAT		"%6.2f"

class CToolMonsterQuad;
class CToolMonsterQuadDlg : public CDialog
{
public:
    enum { IDD = IDD_DLG_MONSTERQUAD };
    enum EditFlags
    {
		MonsQuad_Edit_ZoneName = 0,		// 区域名
		MonsQuad_Edit_AIStep,			// AIStep
		MonsQuad_Edit_Pk,				// 能否Pk
		MonsQuad_Edit_Stall,			// 能否摆摊
        MonsQuad_Edit_PosX,				// 位置x
        MonsQuad_Edit_PosY,				// 位置y
        MonsQuad_Edit_W,				// 宽
        MonsQuad_Edit_H,				// 高
		MonsQuad_Edit_EnterScript,		// 进入脚本
		MonsQuad_Edit_LeaveScript,		// 离开脚本

		MonsQuad_Edit_Monster,			// 怪物
		MonsQuad_Edit_Relife,			// 刷新时间
		MonsQuad_Edit_Number,			// 数量
		MonsQuad_Edit_Dir,				// 朝向
		MonsQuad_Edit_AIValue,			// (怪)思考(反应)时间
		MonsQuad_Edit_DeadScript,		// 死亡脚本
		MonsQuad_Edit_AIScript,			// AI脚本
		MonsQuad_Edit_AICounty,          //国家
		MonsQuad_Edit_Duel,           //切磋

    };

public:
    DECLARE_DYNAMIC(CToolMonsterQuadDlg)

    CToolMonsterQuadDlg(CToolMonsterQuadDlg *pParent = NULL);   // standard constructor
    virtual ~CToolMonsterQuadDlg();

public:
	/*
	 * 激活
	 */
    void SetActive(bool isModify = false);

	/*
	 * 返回Monster工具
	 */
    CToolMonsterQuad * GetToolMonsterQuad();

	/*
	 * 刷新界面数据
	 */
    void Update(CMonsterQuadRes *res);

	/*
	 * 返回怪物id默认值
	 */
	int GetDefaultMonsterId()
	{
		if (mMonsterIds.size() > 0)
			return mMonsterIds[0];
		else
			return 0;
	}

protected:
    //}}AFX_VIRTUAL
	/*
	 * 重写基类虚函数
	 */
    virtual void DoDataExchange(CDataExchange *pDX);	// DDX/DDV support
    virtual BOOL OnInitDialog();

	//{{AFX_MSG(CToolMonsterQuadDlg)
	/*
	 * ComboBox事件处理
	 */
	afx_msg void OnCbnSelchangeComboZoneCanStall();
	afx_msg void OnCbnSelchangeComboZonePKMode();
	afx_msg void OnCbnSelchangeComboMonster();
	afx_msg void OnCbnSelchangeComboZoneCanDuel();

	/*
	 * Edit事件处理
	 */
	afx_msg void OnEnKillfocusEditZoneName();
	afx_msg void OnEnKillfocusEditZoneAIStep();
	afx_msg void OnEnKillfocusEditZoneX();
	afx_msg void OnEnKillfocusEditZoneY();
	afx_msg void OnEnKillfocusEditZoneXScale();
	afx_msg void OnEnKillfocusEditZoneYScale();
	afx_msg void OnEnKillfocusEditZoneEnterScript();
	afx_msg void OnEnKillfocusEditZoneLeaveScript();

	afx_msg void OnEnKillfocusEdtMonsterquadRelife();
	afx_msg void OnEnKillfocusEdtMonsterquadNum();
	afx_msg void OnEnKillfocusEdtMonsterquadDir();
	afx_msg void OnEnKillfocusEdtMonsterquadAivalue();
	afx_msg void OnEnKillfocusEdtMonsterquadDeadscript();
	afx_msg void OnEnKillfocusEdtMonsterquadAiscript();	
	afx_msg void OnEnKillfocusEdtMonsterquadAiCounty();	

	/*
	 * Spin事件处理
	 */
	afx_msg void OnDeltaposSpinZoneX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinZoneY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinZoneXScale(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinZoneYScale(NMHDR *pNMHDR, LRESULT *pResult);

	/*
	 * RadioButton事件处理
	 */
	afx_msg void OnBnClickedRadioZoneAdd();
	afx_msg void OnBnClickedRadioZonePick();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	/*
	 * 数据处理
	 */
    void DataEditHandler(int flag);

	/*
	 * Spin事件统一处理
	 */
	void SpinUpDownHandler(CEdit &edit, LPNMUPDOWN pNMUpDown, LRESULT *pResult);

	/*
	 * 设置编辑模式
	 */
	void SetOperationModeHandler(int mode);

protected:
    /// 编辑怪
    CButton mBtnEditMonster;

    /// 添加怪
    CButton mBtnAddMonster;

/// 区域编辑
protected:
	/// 区域名
	CEdit mEditZoneName;

    /// AIStep
    CEdit mEditAIStep;

    /// 能否PK
    CComboBox mComboPK;

    /// 能否摆摊
    CComboBox mComboStall;

	/// 能否能切磋
	CComboBox mComboDuel;

    /// 世界坐标x
    CEdit mEditWorldPosX;
    CSpinButtonCtrl mSpinWorldPosX;

    /// 世界坐标y
    CEdit mEditWorldPosY;
    CSpinButtonCtrl mSpinWorldPosY;

    /// 编辑缩放x
    CEdit mEditScaleX;
    CSpinButtonCtrl mSpinScaleX;

	/// 编辑缩放y
    CEdit mEditScaleY;
    CSpinButtonCtrl mSpinScaleY;

    /// 脚本编辑
    CEdit mEditEnterScript;
    CEdit mEditLeaveScript;

// 怪物编辑
protected:
	CComboBox mComboMonster;

protected:
    typedef std::vector<CItemDetail::SMonster *> MonsterInfo;

	/// 怪物id
    typedef std::vector<int> MonsterIds;
    typedef MonsterIds::iterator MonsterIdsIter;

protected:
    MonsterInfo mMonsterInfo;
	MonsterIds mMonsterIds;
};

#endif //__MONSTER_QUAD_DLG_H__