#ifndef _EDITOR_FRAME_H_
#define _EDITOR_FRAME_H_

#include <map>

#include "CTEventHandler.h"
#include "txCommandReceiver.h"
#include "EditorUtility.h"

class ConfigToolCore;
class DeviceListPanel;
class SpeedDataPanel;
class HeartRatePanel;
class ConfigDevicePanel;
class ConfigCardPanel;
class CardInfoPanel;
class txCommandSystem;
class EditorFrame : public wxFrame, public CTEventHandler, public txCommandReceiver
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
	virtual WXLRESULT MSWWindowProc(WXUINT message, WXWPARAM wParam, WXLPARAM lParam);
	virtual void registerEditorCoreEventHandler();
	virtual void unregisterEditorCoreEventHandler();
	virtual void onEditorCoreEvent(const CORE_EVENT_TYPE& type, std::vector<std::string>& params);
	void showPanel(wxWindow* panel, bool show);
	std::map<wxWindow*, int>& getWindowIDList() { return mWindowIDList; }
	wxAuiManager& getAuiManager() { return mAuiManager; }
	wxWindow* getWindow(std::string name);
	DeviceListPanel* getDeviceListPanel() { return mDeviceListPanel; }
	SpeedDataPanel* getSpeedDataPanel() { return mSpeedDataPanel; }
	HeartRatePanel* getHeartRatePanel() { return mHeartRatePanel; }
	ConfigDevicePanel* getConfigDevicePanel() { return mConfigDevicePanel; }
	ConfigCardPanel* getConfigCardPanel() { return mConfigCardPanel; }
	CardInfoPanel* getCardInfoPanel() { return mCardInfoPanel; }
	ConfigToolCore* getConfigTool() { return mConfigToolCore; }
	wxAuiToolBar* getWindowToolBar() { return mWindowToolBar; }
	
	DECLARE_EVENT_TABLE()
	void OnTimer(wxTimerEvent& event);
	void OnExit(wxCommandEvent& event);			// 响应菜单的退出事件
	void OnCloseWindow(wxCloseEvent& event);	// 响应程序发出的关闭事件
	void OnSpeedDataPanel(wxCommandEvent& event);
	void OnHeartRatePanel(wxCommandEvent& event);
	void OnConfigDevicePanel(wxCommandEvent& event);
	void OnConfigCardPanel(wxCommandEvent& event);
	void OnDeviceListPanel(wxCommandEvent& event);
	void OnCardInfoPanel(wxCommandEvent& event);
	
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
	wxAuiToolBar* mWindowToolBar;
	wxAuiManager mAuiManager;
	DeviceListPanel* mDeviceListPanel;
	ConfigDevicePanel* mConfigDevicePanel;
	ConfigCardPanel* mConfigCardPanel;
	SpeedDataPanel* mSpeedDataPanel;
	HeartRatePanel* mHeartRatePanel;
	ConfigToolCore* mConfigToolCore;
	CardInfoPanel* mCardInfoPanel;
	txCommandSystem* mCommandSystem;
	std::map<wxWindow*, int> mWindowIDList;
	std::map<std::string, wxWindow*> mWindowList;
};

#endif