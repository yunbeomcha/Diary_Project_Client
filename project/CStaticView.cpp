// CStaticView.cpp: 구현 파일
//

#include "pch.h"
#include "project.h"
#include "CStaticView.h"

// CStaticView

IMPLEMENT_DYNAMIC(CStaticView, CStatic)

CStaticView::CStaticView()
{
	m_pStaticDate = NULL;
	m_pStaticTitle = NULL;
	m_pStaticText = NULL;

}

CStaticView::~CStaticView()
{
}


BEGIN_MESSAGE_MAP(CStaticView, CStatic)
END_MESSAGE_MAP()



// CStaticView 메시지 처리기
void CStaticView::CreateDiaryView(CString date, CString title, CString text, int index, CWnd *pcwnd, CFont *fontDate, CFont *fontTitle, CFont *fontText)
{
	int num = 3;
	// TODO: 여기에 구현 코드 추가.

	//모아보기에서 보여지는 일기들이 보여지는 형식 지정
	m_pStaticDate = new CStatic;
	m_pStaticTitle = new CStatic;
	m_pStaticText = new CStatic;

	m_pStaticDate->Create(date, WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(10 + 200 * index, 0, 5 + 200 * (index + 1), 30), pcwnd);
	m_pStaticTitle->Create(_T("제목 : ") + title, WS_CHILD | WS_VISIBLE | SS_LEFT,
		CRect(20 + 200 * index, 30, 15 + 200 * (index + 1), 60), pcwnd);
	m_pStaticText->Create(text, WS_CHILD |  WS_VISIBLE | SS_SUNKEN | SS_LEFT,
		CRect(10 + 200 * index, 60, 5 + 200 * (index + 1), 350), pcwnd);
	m_pStaticDate->SetFont(fontDate);
	m_pStaticTitle->SetFont(fontTitle);
	m_pStaticText->SetFont(fontText);

}
void CStaticView::FreeDiaryView()
{
	// TODO: 여기에 구현 코드 추가.
	delete m_pStaticDate;
	delete m_pStaticTitle;
	delete m_pStaticText;
	m_pStaticDate = NULL;
	m_pStaticTitle = NULL;
	m_pStaticText = NULL;

}


