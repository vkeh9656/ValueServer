
// ValueServerDlg.h: 헤더 파일
//

#pragma once
#include "MyServer.h"

// CValueServerDlg 대화 상자
class CValueServerDlg : public CDialogEx
{
private:
	MyServer m_server;
// 생성입니다.
public:
	CValueServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	void AddEventString(const wchar_t* ap_string) // CString이 const wchar_t로 캐스팅되어있음
	{
		int index = m_event_list.InsertString(-1, ap_string); // 가장 끝에다가 ap_string을 추가하고, 그 맨끝의 인덱스를 받아옴.
		m_event_list.SetCurSel(index);
	}
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VALUESERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_event_list;
};
