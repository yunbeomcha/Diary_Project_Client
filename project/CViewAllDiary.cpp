// CViewAllDiary.cpp: 구현 파일
//

#include "pch.h"
#include "project.h"
#include "CViewAllDiary.h"
#include "afxdialogex.h"

// CViewAllDiary 대화 상자

IMPLEMENT_DYNAMIC(CViewAllDiary, CDialogEx)

CViewAllDiary::CViewAllDiary(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_VIEW, pParent)
{
	m_pForm = NULL;	//폼뷰의 포인터 초기화
	InitFont();		//폰트정보 설정
}

CViewAllDiary::~CViewAllDiary()
{
}

void CViewAllDiary::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CViewAllDiary, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CViewAllDiary::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CViewAllDiary::OnBnClickedButtonNext)
END_MESSAGE_MAP()


// CViewAllDiary 메시지 처리기


void CViewAllDiary::OnDestroy()
{
	CDialogEx::OnDestroy();
	for (int i = 0; i < WEEK; i++)
	{
		//종료시 그려져있던 내용 삭제
		m_pWndText[i]->FreeDiaryView();	
	}

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CViewAllDiary::InitFont()
{

	// TODO: 여기에 구현 코드 추가.
	//날짜에 대한 폰트정보
	m_fonts.fontDate.CreateFont(23, 0, 0, 0, FW_NORMAL,
		FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS SHELL Dlg"));
	//제목에 대한 폰트정보
	m_fonts.fontTitle.CreateFont(23, 0, 0, 0, FW_NORMAL,
		FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS SHELL Dlg"));
	//내용에 대한 폰트정보
	m_fonts.fontText.CreateFont(23, 0, 0, 0, FW_NORMAL,
		FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS SHELL Dlg"));	

}


void CViewAllDiary::setODBC(SQLHDBC mh_odbc)
{
	// TODO: 여기에 구현 코드 추가.
	this->mh_odbc = mh_odbc;	//odbc 함수를 사용하기 위한 정보
}

void CViewAllDiary::AllocForm()		//폼뷰를 프레임에 할당하는 함수
{
	CCreateContext context;
	ZeroMemory(&context, sizeof(context));

	//프레임의 크기 할당받을 CRect 객체크기를 프레임의 크기로 설정
	CRect rectOfPanelArea;		
	GetDlgItem(IDC_STATIC_RECT)->GetWindowRect(&rectOfPanelArea);
	ScreenToClient(&rectOfPanelArea);
	if (m_pForm != NULL) {
		delete m_pForm;
	}

	//폼뷰 객체 생성 후 프레임 크기에 폼뷰를 할당
	m_pForm = new CFormResult();	
	m_pForm->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rectOfPanelArea, this, IDD_FORM, &context);	
	m_pForm->OnInitialUpdate();
	m_pForm->ShowWindow(SW_SHOW);

}


BOOL CViewAllDiary::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	UpdateData(TRUE);

	//보여질 처음날짜를 현재날짜에서 6일전의 날짜로, 마지막 날짜를 현재 날짜로 설정
	m_TimeStart = CTime::GetCurrentTime() - CTimeSpan(WEEK - 1, 0, 0, 0);	
	m_TimeEnd = CTime::GetCurrentTime();

	AllocForm();	//폼뷰를 할당
	SetWeekView();	//일주일간의 일기를 보여줌

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CViewAllDiary::OnBnClickedButtonPrev()	//일주일 전 버튼인 경우
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//현재 보여지는 날짜 기준으로 시작 날짜와 끝 날짜를 일주일 전의 날짜로 설정
	m_TimeStart = m_TimeStart - CTimeSpan(WEEK, 0, 0, 0);	
	m_TimeEnd = m_TimeEnd - CTimeSpan(WEEK, 0, 0, 0);	
	SetWeekView();		//해당 날짜에 맞는 일주일간의 일기를 보여줌
}


void CViewAllDiary::OnBnClickedButtonNext()	//일주일 후 버튼인 경우
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//현재 보여지는 날짜 기준으로 시작 날짜와 끝 날짜를 일주일 전의 날짜로 설정
	m_TimeStart = m_TimeStart + CTimeSpan(WEEK, 0, 0, 0);	
	m_TimeEnd = m_TimeEnd + CTimeSpan(WEEK, 0, 0, 0);		
	SetWeekView();	//해당 날짜에 맞는 일주일간의 일기를 보여줌
}

void CViewAllDiary::SetWeekView()
{
	// TODO: 여기에 구현 코드 추가.
	m_pForm->SetScrollPos(SB_HORZ, 0, 1);	//스크롤 바를 맨 처음 위치로 할당
	int cnt = 0;
	CString queryStr;
	ViewData viewData;	//DB에 받아올 정보 날짜, 제목, 내용으로 구성된 구조체

	//unsigned int raw_data;
	HSTMT h_statement;	//ODBC를 사용하기 위한 환경 정보
	RETCODE ret_code;
	unsigned short record_state[MAX_COUNT];	//받아온 데이터 상태 정보

	CString strStart, strEnd;	//시작 날짜와 끝 날짜의 문자열
	strStart = m_TimeStart.Format(_T("%Y-%m-%d"));	//시작 날짜를 문자열로
	strEnd = m_TimeEnd.Format(_T("%Y-%m-%d"));		//끝 날짜를 문자열로

	for (int i = 0; i < 7; i++)	//일주일 간의 내용을 저장할 배열
	{
		if (m_pWndText[i] != NULL) {	//이미 할당된 내용이 있으면
			m_pWndText[i]->FreeDiaryView();	//해당 내용을 지움
			delete m_pWndText[i];
		}
		m_pWndText[i] = NULL;	//NULL로 초기화
	}

	queryStr.Format(L"select date, title, contents from diaryinfo where id = '%s' and date between '%s' and '%s' order by date;",
		m_calenderID, strStart, strEnd);		//시작날짜와 끝 날짜의 기간동안 해당하는 ID의 일기 날짜, 제목, 내용을 가져오라는 질의문

	if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_STMT, mh_odbc, &h_statement)) {
		unsigned long recordNum = 0;
		SQLSetStmtAttr(h_statement, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)15, SQL_IS_UINTEGER);
		SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)sizeof(viewData), 0);
		SQLSetStmtAttr(h_statement, SQL_ATTR_CONCURRENCY, (SQLPOINTER)SQL_CONCUR_ROWVER, SQL_IS_UINTEGER);
		SQLSetStmtAttr(h_statement, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER)SQL_CURSOR_KEYSET_DRIVEN, SQL_IS_UINTEGER);
		SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_NUMBER, (SQLPOINTER)MAX_COUNT, SQL_IS_UINTEGER);
		SQLSetStmtAttr(h_statement, SQL_ATTR_ROW_STATUS_PTR, record_state, 0);

		SQLBindCol(h_statement, 1, SQL_WCHAR, &viewData.date, sizeof(wchar_t) * 20, NULL);
		SQLBindCol(h_statement, 2, SQL_WCHAR, &viewData.title, sizeof(wchar_t) * 100, NULL);
		SQLBindCol(h_statement, 3, SQL_WCHAR, &viewData.contents, sizeof(wchar_t) * 1000, NULL);


		ret_code = SQLExecDirect(h_statement, (SQLWCHAR*)(const wchar_t*)queryStr, SQL_NTS);

		int i = 0;
		while (ret_code = SQLFetchScroll(h_statement, SQL_FETCH_NEXT, 0) != SQL_NO_DATA) {
			if (record_state[i] != SQL_ROW_DELETED && record_state[i] != SQL_ROW_ERROR)	//해당 데이터가 존재한다면
			{

				CString date;
				date = viewData.date;	//날짜 데이터를 받음
				int nYear = _wtoi(date.Left(4));
				int nMon = _wtoi(date.Mid(5, 2));
				int nDay = _wtoi(date.Mid(8, 2));
				CTime dateTime(nYear, nMon, nDay, 23, 59, 59);	//CTime 정보로 데이터를 다시 설정해줌
				CTimeSpan ts = dateTime - m_TimeStart;		//시작 날짜와의 차를 통해
				int i = ts.GetDays();				//날짜, 제목, 내용의 정보를 넣을 배열 인덱스를 얻음
				m_pWndText[i] = new CStaticView;	//날짜, 제목, 내용을 생성할 CStaticView 객체를 생성

				//CStaticView의 CreateDiaryView를 통해 CStatic을 동적할당해 날짜, 제목, 내용을 나타냄
				m_pWndText[i]->CreateDiaryView(viewData.date, viewData.title, viewData.contents		
					, i, GetDlgItem(IDD_FORM), &m_fonts.fontDate, &m_fonts.fontTitle, &m_fonts.fontText);
			}
		}
		for (int i = 0; i < WEEK; i++)			//배열이 비어있는 곳은 날짜만 나타나게 하기위해
			if (m_pWndText[i] == NULL) {		//만약 비어있다면
				CTime calDate = m_TimeStart + CTimeSpan(i, 0, 0, 0);	//인덱스로 해당 날짜를 계산하고
				CString date = calDate.Format(_T("%Y-%m-%d"));			//날짜를 문자열로 변환

				m_pWndText[i] = new CStaticView;		//CStaticView객체를 생성하여
				m_pWndText[i]->CreateDiaryView(date, _T(""), _T("")		//해당 날짜에 비어있는 제목과 내용을 나타냄
					, i, GetDlgItem(IDD_FORM), &m_fonts.fontDate, &m_fonts.fontTitle, &m_fonts.fontText);
			}
		SQLFreeHandle(SQL_HANDLE_STMT, h_statement);
	}
	Invalidate(TRUE);
}