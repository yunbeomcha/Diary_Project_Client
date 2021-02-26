// CSchedule.cpp: 구현 파일
//

#include "pch.h"
#include "project.h"
#include "CSchedule.h"
#include "afxdialogex.h"
#include "projectDlg.h"
#include "CAddDiary.h"
#include "CViewAllDiary.h"
#include <ctime>
// CSchedule 대화 상자

IMPLEMENT_DYNAMIC(CSchedule, CDialogEx)

CSchedule::CSchedule(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCHEDULE, pParent)
	, m_title(_T("제목 : "))
	, m_contents(_T(""))
{
	m_strIP = _T("127.0.0.1");
	m_strSend = _T("");
	m_selectDate = _T("");
}

CSchedule::~CSchedule()
{
}

void CSchedule::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CALENDER, m_calender);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_title);
	DDX_Text(pDX, IDC_STATIC_CONTENTS, m_contents);
}


BEGIN_MESSAGE_MAP(CSchedule, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSchedule::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CSchedule::OnBnClickedButtonAdd)
	ON_NOTIFY(MCN_SELCHANGE, IDC_CALENDER, &CSchedule::OnMcnSelchangeCalender)
	ON_BN_CLICKED(IDC_BUTTON_VIEW, &CSchedule::OnBnClickedButtonView)
	ON_BN_CLICKED(IDC_SERVER_CON, &CSchedule::OnBnClickedServerCon)
END_MESSAGE_MAP()


// CSchedule 메시지 처리기


void CSchedule::OnBnClickedButton1() //로그 아웃 버튼
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->EndDialog(IDOK);	//다이어리 창 닫기
	CprojectDlg dlg = new CprojectDlg;	//로그인 창 생성
	dlg.DoModal();	//로그인 창 실행
}


BOOL CSchedule::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SYSTEMTIME today;
	::ZeroMemory(reinterpret_cast<void*>(&today), sizeof(today));
	::GetLocalTime(&today);
	m_selectDate.Format(_T("%04d-%02d-%02d"),          //현재 시간을 얻어옴      
		today.wYear,
		today.wMonth,
		today.wDay
	);
	ResetDiary();
	m_socCom.Create();
	// IP 주소와 포트 번호를 지정
	m_socCom.Connect(m_strIP, 5000);
	m_socCom.Init(this->m_hWnd);

	return TRUE;
}



void CSchedule::OnBnClickedButtonAdd()
{
	//일정추가 모듈 생성
	CAddDiary dlg = new CAddDiary;
	//모듈 멤버변수들 초기화
	dlg.m_selectedDate = m_selectDate;		
	dlg.m_calenderData = m_calenderData;	
	dlg.m_calenderID = m_calenderID;
	//iswritten함수를 통해 해당 데이터베이스가 있는지 검사
	dlg.m_written = isWritten();
	//odbc값 전달
	dlg.setODBC(this->mh_odbc);
	dlg.setSchedule(this);
	//다이알로그 실행
	dlg.DoModal();
}

void CSchedule::setODBC(SQLHDBC mh_odbc)
{
	this->mh_odbc = mh_odbc;	//odbc 함수 사용을 위한 정보값 설정
}

void CSchedule::OnMcnSelchangeCalender(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTime tSelected;
	m_calender.GetCurSel(tSelected);
	//선택한 값의 날짜정보 저장
	m_selectDate.Format(_T("%d-%d-%d"),
		tSelected.GetYear(),
		tSelected.GetMonth(),
		tSelected.GetDay()
	);
	//날짜정보를 토대로 스케쥴 모듈 리셋
	ResetDiary();

	*pResult = 0;
}

void CSchedule::OnBnClickedButtonView()	//최근 일기보기 버튼 클릭 시
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CViewAllDiary dlg = new CViewAllDiary;	//일기보기 다이얼로그 생성
	dlg.setODBC(mh_odbc);	//odbc 정보값 전달
	dlg.m_calenderID = m_calenderID; //사용자 ID 전달
	dlg.DoModal();		//다이얼로그 실행
}

void CSchedule::ResetDiary()
{
	//아이디와 날짜에 맞는값을 db에서 조회하는 쿼리 설정
	CString queryStr;
	queryStr.Format
	(L"select id, title, contents from diaryinfo where id = '%s' and date = '%s';",
		m_calenderID, m_selectDate);

	unsigned short record_state[10];
	CString s;

	HSTMT h_statement;
	RETCODE ret_code;

	if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_STMT, mh_odbc, &h_statement)) {
		unsigned long record_num = 0;
		SQLSetStmtAttr(h_statement, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)15, SQL_IS_UINTEGER);
		SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)sizeof(m_calenderData), 0);
		SQLSetStmtAttr(h_statement, SQL_ATTR_CONCURRENCY, (SQLPOINTER)SQL_CONCUR_ROWVER, SQL_IS_UINTEGER);
		SQLSetStmtAttr(h_statement, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER)SQL_CURSOR_KEYSET_DRIVEN, SQL_IS_UINTEGER);
		SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_NUMBER, (SQLPOINTER)10, SQL_IS_UINTEGER);
		SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_STATUS_PTR, record_state, 0);
		//구조체 멤버변수에 쿼리 결과를 할당하겠다고 지정
		SQLBindCol(h_statement, 1, SQL_WCHAR, &m_calenderData.id, sizeof(wchar_t) * 20, NULL);
		SQLBindCol(h_statement, 2, SQL_WCHAR, &m_calenderData.title, sizeof(wchar_t) * 100, NULL);
		SQLBindCol(h_statement, 3, SQL_WCHAR, &m_calenderData.contents, sizeof(wchar_t) * 1000, NULL);
		//쿼리 실행
		ret_code = SQLExecDirect(h_statement, (SQLWCHAR*)(const wchar_t*)queryStr, SQL_NTS);
		ret_code = SQLFetchScroll(h_statement, SQL_FETCH_NEXT, 0);
		if (ret_code != SQL_NO_DATA)//불러오는 데이터가 있을시
		{
			m_title = "제목 : ";
			m_title += m_calenderData.title; //불러온 값으로 변경
			m_contents = m_calenderData.contents;
		}
		else// 없을시
		{
			m_title = "제목 : ";
			m_contents = "";
			StrCpyW(m_calenderData.title , L"");
			StrCpyW(m_calenderData.contents, L"");
		}
		//컨트롤 정보 갱신
		UpdateData(FALSE);
		SQLFreeHandle(SQL_HANDLE_STMT, h_statement);
	}
}


bool CSchedule::isWritten()
{
	// 가져올 데이터가 있는지를 확인하기 위한 함수
	CString queryStr;
	queryStr.Format
	(L"select id, title, contents from diaryinfo where id = '%s' and date = '%s';",
		m_calenderID, m_selectDate);

	unsigned short record_state[10];
	CString s;

	HSTMT h_statement;
	RETCODE ret_code;

	if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_STMT, mh_odbc, &h_statement)) {
		unsigned long record_num = 0;
		SQLSetStmtAttr(h_statement, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)15, SQL_IS_UINTEGER);
		SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)sizeof(m_calenderData), 0);
		SQLSetStmtAttr(h_statement, SQL_ATTR_CONCURRENCY, (SQLPOINTER)SQL_CONCUR_ROWVER, SQL_IS_UINTEGER);
		SQLSetStmtAttr(h_statement, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER)SQL_CURSOR_KEYSET_DRIVEN, SQL_IS_UINTEGER);
		SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_NUMBER, (SQLPOINTER)10, SQL_IS_UINTEGER);
		SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_STATUS_PTR, record_state, 0);
		//구조체 멤버변수에 쿼리 결과를 할당하겠다고 지정
		SQLBindCol(h_statement, 1, SQL_WCHAR, &m_calenderData.id, sizeof(wchar_t) * 20, NULL);
		SQLBindCol(h_statement, 2, SQL_WCHAR, &m_calenderData.title, sizeof(wchar_t) * 100, NULL);
		SQLBindCol(h_statement, 3, SQL_WCHAR, &m_calenderData.contents, sizeof(wchar_t) * 1000, NULL);
	
		ret_code = SQLExecDirect(h_statement, (SQLWCHAR*)(const wchar_t*)queryStr, SQL_NTS);
		ret_code = SQLFetchScroll(h_statement, SQL_FETCH_NEXT, 0);
		if (ret_code == SQL_NO_DATA)
		{
			return false;//해당날짜에 일기가 없으면
		}
		else
		{
			return true;//해당날짜에 일기가 있으면
		}
		SQLFreeHandle(SQL_HANDLE_STMT, h_statement);
	}
	return false;
}


void CSchedule::OnBnClickedServerCon()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//접속
	UpdateData(TRUE);

	char pTmp[256];

	CString strTmp;
	strTmp.Format(_T("%s,%s"), m_calenderID, m_selectDate);
	m_socCom.Send(strTmp, 256);
}


LPARAM CSchedule::OnReceive(UINT wParam, LPARAM lParam)
{
	// 접속된 곳에서 데이터가 도착했을때

	char pTmp[256];
	CString strTmp;
	memset(pTmp, '\0', 256);

	// 데이터를 pTmp에 받는다.
	m_socCom.Receive(pTmp, 256);
	strTmp.Format(_T("%s"), pTmp);


	return TRUE;
}
