#pragma once


// CSignUpDlg 대화 상자

class CSignUpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSignUpDlg)

public:
	CSignUpDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSignUpDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SIGN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strNewID;		//새 아이디
	CString m_strNewPwd;	//새 비밀번호
	CString m_strPwdCheck;	//비밀번호 확인

	SQLHDBC mh_odbc;	//odbc함수에 사용될 정보

	void setODBC(SQLHDBC mh_odbc);	//mh_odbc 설정
	BOOL m_bIDChecked;		//아이디 중복확인 여부
	CString m_checkedID;	//중복 확인 완료된 아이디
	afx_msg void OnClickedButtonOk();			//완료 버튼 누를 경우
	afx_msg void OnBnClickedButtonIdCheck();	//중복확인 버튼 누를 경우
};
