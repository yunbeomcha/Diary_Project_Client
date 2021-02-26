#pragma once


// CSchedule 대화 상자

class CSchedule : public CDialogEx
{
	DECLARE_DYNAMIC(CSchedule)

public:
	CSchedule(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSchedule();

	CSocCom m_socCom;
	CString	m_strIP;
	CString	m_strSend;
	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCHEDULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	HICON m_hIcon;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();	//로그아웃 버튼 클릭 시
	BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();	//글쓰기 버튼 클릭 시
	afx_msg void OnBnClickedButtonView();	//최근 모아보기버튼 클릭시
	afx_msg void OnMcnSelchangeCalender(NMHDR* pNMHDR, LRESULT* pResult);
	void setODBC(SQLHDBC mh_odbc);	//ODBC함수를 사용하기 위한 정보 세팅
	CString m_calenderID;	//사용자 아이디
	CMonthCalCtrl m_calender;	//달력 컨트롤
	SQLHDBC mh_odbc;	//odbc함수를 사용하기 위한 정보
	CString m_title;	//제목
	CString m_contents;	//내용
	CString m_selectDate;	//선택된 날짜
	UserData m_calenderData;	//날짜, 제목, 내용을 포함한 구조체
	void ResetDiary();	
	bool isWritten();
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM lParam);
	afx_msg void OnBnClickedServerCon();	//올리기버튼 클릭시

};
