
// projectDlg.h: 헤더 파일
//

#pragma once



// CprojectDlg 대화 상자
class CprojectDlg : public CDialogEx
{
// 생성입니다.
public:
	CprojectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
private:
	SQLHANDLE mh_environment;	
	SQLHDBC mh_odbc;
	char m_connect_flag = 0;	//서버 접속 성공여부

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnlogin();	//로그인 버튼을 누르는 경우
	afx_msg void OnDestroy();
	CString m_strID;	//아이디
	CString m_strPwd;	//비밀번호
	afx_msg void OnBnClickedBtnjoin();	//회원가입버튼을 누르는 경우
};
