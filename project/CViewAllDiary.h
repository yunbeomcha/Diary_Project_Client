#pragma once
#include "CStaticView.h"
#include "CFormResult.h"

// CViewAllDiary 대화 상자
#define MAX_COUNT	10
#define WEEK		7
struct ViewData		//날짜, 제목, 내용을 포함하는 구조체
{
	wchar_t date[30];
	wchar_t title[100];
	wchar_t contents[1000];
};
struct fonts {	//폰트 정보 저장하는 구조체
	CFont fontDate;
	CFont fontTitle;
	CFont fontText;
};

class CViewAllDiary : public CDialogEx
{
	DECLARE_DYNAMIC(CViewAllDiary)

public:
	CViewAllDiary(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CViewAllDiary();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	SQLHDBC mh_odbc;
	fonts m_fonts;	//결과 폰트
	
	DECLARE_MESSAGE_MAP()
public:
	void AllocForm();
	CFormResult *m_pForm;		//폼뷰 포인터
	CStaticView *m_pWndText[7];	//폼뷰 내에 붙일 CStaticView를 생성할 포인터
	CTime m_TimeStart, m_TimeEnd;	//시작 날짜와 끝 날짜
	CString m_calenderID;		//사용자의 아이디
	void InitFont();			//폰트 정보 설정함수
	void setODBC(SQLHDBC mh_odbc);	//odbc정보 설정 함수
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	void SetWeekView();			//일주일치 정보를 나타내는 함수
	afx_msg void OnBnClickedButtonPrev();	// < 버튼을 누르는 경우
	afx_msg void OnBnClickedButtonNext();	// > 버튼을 누르는 경우
};
