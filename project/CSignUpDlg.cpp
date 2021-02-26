// CSignUpDlg.cpp: 구현 파일
//

#include "pch.h"
#include "project.h"
#include "CSignUpDlg.h"
#include "afxdialogex.h"


// CSignUpDlg 대화 상자

IMPLEMENT_DYNAMIC(CSignUpDlg, CDialogEx)

CSignUpDlg::CSignUpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SIGN, pParent)
	, m_strNewID(_T(""))
	, m_strNewPwd(_T(""))
	, m_strPwdCheck(_T(""))
{

	m_checkedID = _T("");
}

CSignUpDlg::~CSignUpDlg()
{
}

void CSignUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEW_ID, m_strNewID);
	DDX_Text(pDX, IDC_EDIT_NEW_PWD, m_strNewPwd);
	DDX_Text(pDX, IDC_EDIT_PWD_CHECK, m_strPwdCheck);
}


BEGIN_MESSAGE_MAP(CSignUpDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ID_CHECK, &CSignUpDlg::OnBnClickedButtonIdCheck)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CSignUpDlg::OnClickedButtonOk)
END_MESSAGE_MAP()


// CSignUpDlg 메시지 처리기


void CSignUpDlg::OnBnClickedButtonIdCheck()
{
	UpdateData(TRUE);
	m_bIDChecked = FALSE;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_strNewID.IsEmpty())	
	{	//만약 새로 저장할 ID칸이 비어있지 않다면
	
		//DB에 해당 아이디가 있는지에 대한 데이터를 읽을 SQL 명령문
		CString queryStr;
		queryStr.Format(L"select count(*) from idinfo where id = '%s';", m_strNewID); 

		unsigned int raw_data;	//데이터를 저장할 변수
		HSTMT h_statement;
		RETCODE ret_code;
		unsigned short record_state[10];

		//Query문을 위한 메모리 할당
		if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_STMT, mh_odbc, &h_statement)) {

			//SQL관련 정보 설정
			SQLSetStmtAttr(h_statement, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)15, SQL_IS_UINTEGER);
			SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)sizeof(raw_data), 0);
			SQLSetStmtAttr(h_statement, SQL_ATTR_CONCURRENCY, (SQLPOINTER)SQL_CONCUR_ROWVER, SQL_IS_UINTEGER);
			SQLSetStmtAttr(h_statement, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER)SQL_CURSOR_KEYSET_DRIVEN, SQL_IS_UINTEGER);
			SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_NUMBER, (SQLPOINTER)10, SQL_IS_UINTEGER);
			SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_STATUS_PTR, record_state, 0);

			//테이블에서 가져온 데이터를 저장할 메모리 위치 설정
			SQLBindCol(h_statement, 1, SQL_INTEGER, &raw_data, sizeof(unsigned int), NULL);

			//SQL 명령문 실행
			ret_code = SQLExecDirect(h_statement, (SQLWCHAR*)(const wchar_t*)queryStr, SQL_NTS);
			ret_code = SQLFetchScroll(h_statement, SQL_FETCH_NEXT, 0);
			
			if (ret_code != SQL_NO_DATA)
			{
				if (raw_data == 0)	//아이디가 0개라면
				{
					MessageBox(L"사용할 수 있는 아이디입니다.");	//사용 가능한 아이디
					m_bIDChecked = TRUE;
					m_checkedID = m_strNewID;
				}
				else
					MessageBox(L"중복된 아이디입니다.");	//아이디가 존재하면
			}
			else
				MessageBox(L"아이디 조회 오류입니다.");	//SQL 데이터가 없는 경우
			SQLFreeHandle(SQL_HANDLE_STMT, h_statement);
		}
	}
	else
		MessageBox(_T("아이디를 입력해주세요."));	//새로 지정할 ID칸이 비어있다면
}


void CSignUpDlg::setODBC(SQLHDBC mh_odbc)
{
	// TODO: 여기에 구현 코드 추가.
	this->mh_odbc = mh_odbc;	//odbc 핸들러 얻음
}

void CSignUpDlg::OnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bIDChecked || m_checkedID.Compare(m_strNewID) != 0)
		MessageBox(L"아이디 중복 확인을 해야합니다.");	//아이디를 체크하지 않았거나 중복확인 후 아이디를 변경한 경우
	else if (m_strNewPwd.IsEmpty())
		MessageBox(L"비밀번호를 입력해야 합니다.");		//새 비밀번호 칸이 비어있는 경우
	else if (m_strPwdCheck.IsEmpty())
		MessageBox(L"비밀번호 확인을 해야 합니다.");	//비밀번호 확인 칸이 비어있는 경우
	else if (m_strNewPwd.Compare(m_strPwdCheck) != 0)
		MessageBox(L"비밀번호 번호가 다릅니다.");		//새 비밀번호와 비밀번호 확인이 다른 경우
	else
	{
		CString queryStr;
		//DB에 새 아이디와 비밀번호를 저장하기 위한 SQL 명령문
		queryStr.Format(L"insert into idinfo values ('%s', '%s')", m_strNewID, m_strNewPwd);	
		HSTMT h_statement;
		RETCODE retCode;

		//query문을 위한 메모리 할당
		if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_STMT, mh_odbc, &h_statement)) {
			//query문 실행시 타임아웃 설정
			SQLSetStmtAttr(h_statement, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)15, SQL_IS_UINTEGER);

			retCode = SQLExecDirect(h_statement, (SQLWCHAR*)(const wchar_t*)queryStr, SQL_NTS);
			if (retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)	
			{	//DB에 정보 저장이 성공한 경우
				
				MessageBox(L"회원 가입 되었습니다!");
				CDialogEx::OnOK();
			}
			SQLFreeHandle(SQL_HANDLE_STMT, h_statement);
		}
	}
}
