#pragma once
#include "CSchedule.h"

// CAddSchedule 대화 상자
class CAddDiary : public CDialogEx
{
	DECLARE_DYNAMIC(CAddDiary)

public:
	CAddDiary(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAddDiary();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_DIARY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_selectedDate;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	SQLHDBC mh_odbc;
	CString m_title;
	CString m_contents;
	UserData m_calenderData;
	CString m_selectDateStatic;
	BOOL m_written;
	void UpdateDiary();
	void InsertDiary();
	void setODBC(SQLHDBC mh_odbc);
	CSchedule* m_schedule;
	void setSchedule(CSchedule* ptr);
	CString m_calenderID;
};
