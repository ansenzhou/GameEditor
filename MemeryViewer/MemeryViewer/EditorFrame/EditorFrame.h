#ifndef _EDITOR_FRAME_H_
#define _EDITOR_FRAME_H_

#include "EditorUtility.h"

class MemeryViewer;
class MemeryDetailWindow;
class MemeryTypeStatisticsWindow;
class EditorFrame : public wxFrame
{
public:
	EditorFrame(wxString title, wxSize size);
	void init();
	void destroy();
	void setup();
	virtual ~EditorFrame();
	// 刷新全部的可选中菜单和可选中工具按钮的选中状态
	void RefreshAllMenuToolCheckState();
	void Update(float elapsedTime);
	void Render();
	void KeyProcess();
	
	DECLARE_EVENT_TABLE()
	void OnTimer(wxTimerEvent& event);
	void OnExit(wxCommandEvent& event); // 响应菜单的退出事件
	void OnCloseWindow(wxCloseEvent& event);	// 响应程序发出的关闭事件
	
protected:
	void CreateMenu();
	void CreateToolBar();
	void CreateWindows();
	void CreateStatuBar();
	void UpdateStatus();
	void CreateEditorCore();
	void RefreshAllResource();

protected:
	wxTimer* mTimer;
	wxMenu* mFileMenu;
	wxAuiManager mAuiManager;
	MemeryDetailWindow* mMemeryDetailWindow;
	MemeryTypeStatisticsWindow* mMemeryTypeStatisticsWindow;
	MemeryViewer* mMemeryViewer;
};

#endif