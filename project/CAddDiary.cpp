// CAddSchedule.cpp: 구현 파일
//

#include "pch.h"
#include "project.h"
#include "CAddDiary.h"
#include "afxdialogex.h"
#include "CSignUpDlg.h"


// CAddSchedule 대화 상자

IMPLEMENT_DYNAMIC(CAddDiary, CDialogEx)

CAddDiary::CAddDiary(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_DIARY, pParent)
	, m_title(_T(""))
	, m_contents(_T(""))
	, m_selectDateStatic(_T(""))
{

	m_selectedDate = _T("");
	//  m_calenderID = _T("");
	m_calenderID = _T("");
}

CAddDiary::~CAddDiary()
{
}

void CAddDiary::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_title);
	DDX_Text(pDX, IDC_EDIT_CONTENTS, m_contents);
	DDX_Text(pDX, IDC_STATIC_DATE, m_selectDateStatic);
}


BEGIN_MESSAGE_MAP(CAddDiary, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddDiary::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddSchedule 메시지 처리기


BOOL CAddDiary::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//글을 수정할때 이미 쓴글을 수정하는것이 편하기때문에
	//프로그램 시작할때 받아온 값을 토대로 컨트롤 값들을 갱신해줌	
	m_title = m_calenderData.title;
	m_contents = m_calenderData.contents;	
	m_selectDateStatic = m_selectedDate;
	//컨트롤값 갱신
	UpdateData(FALSE);
	return TRUE;
}


void CAddDiary::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (m_written == TRUE)//해당 날짜에 일기가 있을때는 update
	{
		UpdateDiary();
	}
	else// 없을땐 insert
	{
		InsertDiary();
	}
	//스케쥴모듈 갱신
	m_schedule->ResetDiary();
	//실행중인 글쓰기 모듈도 갱신
	UpdateData(FALSE);
}


void CAddDiary::UpdateDiary()
{
	// db 수정쿼리 작성
	CString queryStr;
	queryStr.Format
	(L"UPDATE DiaryInfo SET title = '%s', contents = '%s' WHERE id = '%s' and date = '%s'; ",
		m_title, m_contents, m_calenderID, m_selectedDate);

	HSTMT h_statement;
	RETCODE ret_code;

	if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_STMT, mh_odbc, &h_statement)) {
		SQLSetStmtAttr(h_statement, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)15, SQL_IS_UINTEGER);
		//쿼리 실행
		ret_code = SQLExecDirect(h_statement, (SQLWCHAR*)(const wchar_t*)queryStr, SQL_NTS);

		if (ret_code == SQL_SUCCESS || ret_code == SQL_SUCCESS_WITH_INFO)
		{
			//실행 성공시 메시지 띄움
			MessageBox(_T("수정하였습니다."));
			//멤버 변수의 값도 바꿔줌
			StrCpyW(m_calenderData.title, m_title);
			StrCpyW(m_calenderData.contents, m_contents);
		}
		else
		{
			//실행 실패시
			AfxMessageBox(_T("수정 실패"));
		}
		SQLFreeHandle(SQL_HANDLE_STMT, h_statement);
	}
}


void CAddDiary::InsertDiary()
{
	//insert 쿼리문 작성
	CString queryStr;
	queryStr.Format
	(L"insert into DiaryInfo values( '%s', '%s' ,'%s' , '%s'); ",
		 m_calenderID, m_selectedDate, m_title, m_contents);

	HSTMT h_statement;
	RETCODE ret_code;

	if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_STMT, mh_odbc, &h_statement)) {
		SQLSetStmtAttr(h_statement, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)15, SQL_IS_UINTEGER);
		//쿼리 실행
		ret_code = SQLExecDirect(h_statement, (SQLWCHAR*)(const wchar_t*)queryStr, SQL_NTS);

		if (ret_code == SQL_SUCCESS || ret_code == SQL_SUCCESS_WITH_INFO)
		{
			//실행 성공시 메시지 띄움
			MessageBox(_T("새로운 글을 작성하였습니다."));
			//멤버 변수의 값도 바꿔줌
			StrCpyW(m_calenderData.title, m_title);
			StrCpyW(m_calenderData.contents, m_contents);
		}
		else
		{
			//실행 실패시
			AfxMessageBox(_T("작성 실패"));
		}
		SQLFreeHandle(SQL_HANDLE_STMT, h_statement);
	}
}


void CAddDiary::setODBC(SQLHDBC mh_odbc)
{
	this->mh_odbc = mh_odbc;      //odbc 핸들러 얻음
}


void CAddDiary::setSchedule(CSchedule* ptr)
{
	this->m_schedule = ptr;
}
