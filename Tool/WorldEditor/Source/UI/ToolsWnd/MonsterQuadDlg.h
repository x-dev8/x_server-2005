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
		MonsQuad_Edit_ZoneName = 0,		// ������
		MonsQuad_Edit_AIStep,			// AIStep
		MonsQuad_Edit_Pk,				// �ܷ�Pk
		MonsQuad_Edit_Stall,			// �ܷ��̯
        MonsQuad_Edit_PosX,				// λ��x
        MonsQuad_Edit_PosY,				// λ��y
        MonsQuad_Edit_W,				// ��
        MonsQuad_Edit_H,				// ��
		MonsQuad_Edit_EnterScript,		// ����ű�
		MonsQuad_Edit_LeaveScript,		// �뿪�ű�

		MonsQuad_Edit_Monster,			// ����
		MonsQuad_Edit_Relife,			// ˢ��ʱ��
		MonsQuad_Edit_Number,			// ����
		MonsQuad_Edit_Dir,				// ����
		MonsQuad_Edit_AIValue,			// (��)˼��(��Ӧ)ʱ��
		MonsQuad_Edit_DeadScript,		// �����ű�
		MonsQuad_Edit_AIScript,			// AI�ű�
		MonsQuad_Edit_AICounty,          //����
		MonsQuad_Edit_Duel,           //�д�

    };

public:
    DECLARE_DYNAMIC(CToolMonsterQuadDlg)

    CToolMonsterQuadDlg(CToolMonsterQuadDlg *pParent = NULL);   // standard constructor
    virtual ~CToolMonsterQuadDlg();

public:
	/*
	 * ����
	 */
    void SetActive(bool isModify = false);

	/*
	 * ����Monster����
	 */
    CToolMonsterQuad * GetToolMonsterQuad();

	/*
	 * ˢ�½�������
	 */
    void Update(CMonsterQuadRes *res);

	/*
	 * ���ع���idĬ��ֵ
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
	 * ��д�����麯��
	 */
    virtual void DoDataExchange(CDataExchange *pDX);	// DDX/DDV support
    virtual BOOL OnInitDialog();

	//{{AFX_MSG(CToolMonsterQuadDlg)
	/*
	 * ComboBox�¼�����
	 */
	afx_msg void OnCbnSelchangeComboZoneCanStall();
	afx_msg void OnCbnSelchangeComboZonePKMode();
	afx_msg void OnCbnSelchangeComboMonster();
	afx_msg void OnCbnSelchangeComboZoneCanDuel();

	/*
	 * Edit�¼�����
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
	 * Spin�¼�����
	 */
	afx_msg void OnDeltaposSpinZoneX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinZoneY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinZoneXScale(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinZoneYScale(NMHDR *pNMHDR, LRESULT *pResult);

	/*
	 * RadioButton�¼�����
	 */
	afx_msg void OnBnClickedRadioZoneAdd();
	afx_msg void OnBnClickedRadioZonePick();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	/*
	 * ���ݴ���
	 */
    void DataEditHandler(int flag);

	/*
	 * Spin�¼�ͳһ����
	 */
	void SpinUpDownHandler(CEdit &edit, LPNMUPDOWN pNMUpDown, LRESULT *pResult);

	/*
	 * ���ñ༭ģʽ
	 */
	void SetOperationModeHandler(int mode);

protected:
    /// �༭��
    CButton mBtnEditMonster;

    /// ��ӹ�
    CButton mBtnAddMonster;

/// ����༭
protected:
	/// ������
	CEdit mEditZoneName;

    /// AIStep
    CEdit mEditAIStep;

    /// �ܷ�PK
    CComboBox mComboPK;

    /// �ܷ��̯
    CComboBox mComboStall;

	/// �ܷ����д�
	CComboBox mComboDuel;

    /// ��������x
    CEdit mEditWorldPosX;
    CSpinButtonCtrl mSpinWorldPosX;

    /// ��������y
    CEdit mEditWorldPosY;
    CSpinButtonCtrl mSpinWorldPosY;

    /// �༭����x
    CEdit mEditScaleX;
    CSpinButtonCtrl mSpinScaleX;

	/// �༭����y
    CEdit mEditScaleY;
    CSpinButtonCtrl mSpinScaleY;

    /// �ű��༭
    CEdit mEditEnterScript;
    CEdit mEditLeaveScript;

// ����༭
protected:
	CComboBox mComboMonster;

protected:
    typedef std::vector<CItemDetail::SMonster *> MonsterInfo;

	/// ����id
    typedef std::vector<int> MonsterIds;
    typedef MonsterIds::iterator MonsterIdsIter;

protected:
    MonsterInfo mMonsterInfo;
	MonsterIds mMonsterIds;
};

#endif //__MONSTER_QUAD_DLG_H__