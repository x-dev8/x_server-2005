
ʹ�÷���

	��ʼ��
	CHR_UI_Mgr theHRUIMgr;
	�����½ӿڼȿ�(��D3D��ܽӿ�һ��)
	void	FrameMove();
	void	Render();
	void	InitDeviceObjects( UI_Drawer::funRegisterTexture pRegisterTexture,
								UI_Drawer::funUnregisterTexture pUnregisterTexture,
								UI_Drawer::funBlt pBlt,
								UI_Drawer::funDrawRect2D pDrawRect2D,
								UI_Drawer::funFillRect2D pFillRect2D  );
	void	InvalidateDeviceObjects();
	void	RestoreDeviceObjects();
	bool	MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	
���õĿ���
	CHR_UI_Button		��ť
	CHR_UI_CheckBox		��ѡ��
	CHR_UI_ComboBox		������
	CHR_UI_Edit			�༭��
	CHR_UI_List			�б��
	CHR_UI_ListEx		�б����չ
	CHR_UI_ListImg		ͼ���б��
	CHR_UI_Picture		ͼ��
	CHR_UI_Progress		������
	CHR_UI_ScrollBar	������
	CHR_UI_Tab			����ҳ
	CHR_UI_Text			�ı���
	
	