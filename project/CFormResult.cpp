// CFormResult.cpp: 구현 파일
//

#include "pch.h"
#include "project.h"
#include "CFormResult.h"


// CFormResult

IMPLEMENT_DYNCREATE(CFormResult, CFormView)

CFormResult::CFormResult()
	: CFormView(IDD_FORM)
{	

}

CFormResult::~CFormResult()
{
}

void CFormResult::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormResult, CFormView)
END_MESSAGE_MAP()


// CFormResult 진단
BOOL CFormResult::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CFormResult::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

#ifdef _DEBUG
void CFormResult::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormResult::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormResult 메시지 처리기

