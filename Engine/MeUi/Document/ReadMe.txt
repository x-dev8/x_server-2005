
使用方法

	初始化
	CHR_UI_Mgr theHRUIMgr;
	的如下接口既可(与D3D框架接口一样)
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
	
可用的控制
	CHR_UI_Button		按钮
	CHR_UI_CheckBox		单选框
	CHR_UI_ComboBox		下拉框
	CHR_UI_Edit			编辑框
	CHR_UI_List			列表框
	CHR_UI_ListEx		列表框扩展
	CHR_UI_ListImg		图像列表框
	CHR_UI_Picture		图像
	CHR_UI_Progress		进度条
	CHR_UI_ScrollBar	滚动条
	CHR_UI_Tab			属性页
	CHR_UI_Text			文本框
	
	