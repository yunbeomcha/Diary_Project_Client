
// projectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "project.h"
#include "projectDlg.h"
#include "afxdialogex.h"
#include "CSchedule.h"
#include "CSignUpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CprojectDlg 대화 상자



CprojectDlg::CprojectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
	, m_strID(_T(""))
	, m_strPwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CprojectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
}

BEGIN_MESSAGE_MAP(CprojectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNLOGIN, &CprojectDlg::OnBnClickedBtnlogin)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTNJOIN, &CprojectDlg::OnBnClickedBtnjoin)
END_MESSAGE_MAP()


// CprojectDlg 메시지 처리기

BOOL CprojectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SQLSetEnvAttr(NULL, SQL_ATTR_CONNECTION_POOLING, (SQLPOINTER)SQL_CP_ONE_PER_DRIVER, SQL_IS_INTEGER);
	
	//ODBC 기술을 사용하기 위한 환경 구성. 구성된 환경 정보에 대한 핸들 값은 mh_environment
	if (SQL_ERROR != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &mh_environment))
	{
		//사용할 ODBC 버전 정보를 설정
		SQLSetEnvAttr(mh_environment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
		SQLSetEnvAttr(mh_environment, SQL_ATTR_CP_MATCH, (SQLPOINTER)SQL_CP_RELAXED_MATCH, SQL_IS_INTEGER);

		//ODBC 함수를 사용하기 위한 정보 구성. 정보에 대한 핸들 값 mh_odbc에 저장
		if (SQL_ERROR != SQLAllocHandle(SQL_HANDLE_DBC, mh_environment, &mh_odbc))
		{
			RETCODE ret_code = SQLConnect(mh_odbc, 
				(SQLWCHAR *)L"dsnTest", SQL_NTS,		// 접속할 DSN 설정
				(SQLWCHAR *)L"root", SQL_NTS,				// 접속에 사용할 ID
				(SQLWCHAR *)L"0000", SQL_NTS);	// 접속에 사용할 Password
			if (ret_code == SQL_SUCCESS || ret_code == SQL_SUCCESS_WITH_INFO)
			{
				//ODBC를 사용하여 DB접속에 성공한 경우
				m_connect_flag = 1;
				return 1;
			}
			else {
				//접속에 실패한 경우, 구성했던 메모리 제거
				if (mh_odbc != SQL_NULL_HDBC)
					SQLFreeHandle(SQL_HANDLE_DBC, mh_odbc);
				if (mh_environment != SQL_NULL_HENV)
					SQLFreeHandle(SQL_HANDLE_ENV, mh_environment);
			}
		
		}
		if (!m_connect_flag)
		{
			//연결에 실패한 경우 메세지 박스 출력 및 로그인 창 종료
			MessageBox(L"Server Connect Error");
			this->EndDialog(IDOK);
		}
	}
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CprojectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CprojectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CprojectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CprojectDlg::OnBnClickedBtnlogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (!m_strID.IsEmpty() && !m_strPwd.IsEmpty())	
	{	//아이디와 비밀번호가 입력된 경우
		
		//DB에 해당 아이디와 비밀번호가 있는지에 대한 데이터를 읽을 SQL 명령문
		CString queryStr;
		queryStr.Format(L"select count(*) from idinfo where id = '%s' and pwd = '%s'",
			m_strID, m_strPwd);

		unsigned int raw_data;	//데이터를 저장할 변수
		HSTMT h_statement;
		RETCODE ret_code;
		unsigned short record_state[10];

		//qeury문을 위한 메모리 할당
		if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_STMT, mh_odbc, &h_statement)) {

			SQLSetStmtAttr(h_statement, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)15, SQL_IS_UINTEGER);	//query문 실행시 타임아웃 설정
			SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)sizeof(raw_data), 0);	//가져온 데이터 저장할 메모리 크기 설정
			SQLSetStmtAttr(h_statement, SQL_ATTR_CONCURRENCY, (SQLPOINTER)SQL_CONCUR_ROWVER, SQL_IS_UINTEGER);	//데이터 가져올 때 동시성에 대한 방식 설정
			SQLSetStmtAttr(h_statement, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER)SQL_CURSOR_KEYSET_DRIVEN, SQL_IS_UINTEGER);	//검색된 데이터의 위치를 기억하는 방식 설정
			SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_NUMBER, (SQLPOINTER)10, SQL_IS_UINTEGER);	//데이터를 가져오는 최대 단위를 설정
			SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_STATUS_PTR, record_state, 0);	//읽을 데이터의 상태를 저장할 변수의 주소를 전달

			//테이블에서 가져온 데이터를 저장할 메모리 위치 설정
			SQLBindCol(h_statement, 1, SQL_INTEGER, &raw_data, sizeof(unsigned int), NULL);

			//SQL 명령문 실행
			ret_code = SQLExecDirect(h_statement, (SQLWCHAR *)(const wchar_t *)queryStr, SQL_NTS);
			ret_code = SQLFetchScroll(h_statement, SQL_FETCH_NEXT, 0);
			
			if (ret_code != SQL_NO_DATA && raw_data == 1)
			{	//아이디, 비밀번호가 일치하는 경우

				//로그인 창 종료 및 다이어리 창 실행
				this->EndDialog(IDOK);	
				CSchedule dlg;
				dlg.m_calenderID = m_strID;
				dlg.setODBC(this->mh_odbc);
				dlg.DoModal();
			}
			else
				//일치하지 않는 경우
				MessageBox(L"잘못된 비밀번호 혹은 아이디 입니다.");
			SQLFreeHandle(SQL_HANDLE_STMT, h_statement);
		}
	}
	else
		//아이디와 비밀번호가 비워져 있는 경우
		MessageBox(_T("빈칸을 채워주세요."));
	
}


void CprojectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	//서버가 연결된 경우 프로그램이 종료되면 서버연결 정보 제거
	if (m_connect_flag == 1) {
		if (mh_odbc != SQL_NULL_HDBC)
			SQLFreeHandle(SQL_HANDLE_DBC, mh_odbc);
		if (mh_environment != SQL_NULL_HENV)
			SQLFreeHandle(SQL_HANDLE_ENV, mh_environment);
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CprojectDlg::OnBnClickedBtnjoin()	//회원가입 버튼을 누른 경우
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//회원 가입 다이얼로그 생성후 실행
	CSignUpDlg dlg = new CSignUpDlg;	
	dlg.setODBC(this->mh_odbc);
	dlg.DoModal();
}
