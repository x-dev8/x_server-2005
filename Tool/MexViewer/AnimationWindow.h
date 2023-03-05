#pragma once

/* .seq �ļ�ͨ��� */
#define SEQ_FILE_WILDCARD				wxT("SEQ Files (*.seq)|*.seq")

/* ģ����ֻ����: ������ ��ʼ֡ ����֡ HitPoint */
#define SEQ_FILE_LINE_FORMAT			"%s %d %d %d\n"

class AnimationLBClientData : public wxClientData
{
public:
	AnimationLBClientData(bool hlt, wxString n, int s, int e, int hp)
		: HasLightTrack(hlt), Name(n), Start(s), End(e), HitPoint(hp)
	{}
	
public:
	bool HasLightTrack;
	wxString Name;
	int Start;
	int End;
	int HitPoint;
};

/*
 * RightWindow�е��Ӵ���, ���ڱ༭������Ϣ
 */
class AnimationWindow : public wxWindow
{
public:
	AnimationWindow(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
	virtual ~AnimationWindow();

public:
	/*
	 * ˢ�´���Animation�б�
	 */
	void UpdateAnimationList();

protected:
	void OnEventListBox(wxCommandEvent &event);

	void OnButtonAdd(wxCommandEvent &WXUNUSED(event));
	void OnButtonDel(wxCommandEvent &WXUNUSED(event));
	void OnButtonSaveAni(wxCommandEvent &WXUNUSED(event));
	void OnButtonImportAniTemplate(wxCommandEvent &WXUNUSED(event));
	void OnButtonExportAniTemplate(wxCommandEvent &WXUNUSED(event));

	void OnSlider(wxCommandEvent &WXUNUSED(event));
	DECLARE_EVENT_TABLE()

protected:
	int mOneLoopTime;
};