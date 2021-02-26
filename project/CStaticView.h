#pragma once


// CStaticView

class CStaticView : public CStatic
{
	DECLARE_DYNAMIC(CStaticView)

public:
	CStaticView();
	virtual ~CStaticView();
	CStatic *m_pStaticDate;		//날짜 정보 나타낼 CStatic 포인터
	CStatic *m_pStaticTitle;	//제목 정보 나타낼 CStatic 포인터
	CStatic *m_pStaticText;		//내용 정보 나타낼 CStatic 포인터

protected:
	DECLARE_MESSAGE_MAP()
public:
	//날짜, 제목, 내용을 나타내는 CStatic을 생성하는 함수
	void CreateDiaryView(CString date, CString title, CString text, int index, CWnd *pcwnd, CFont *fontDate, CFont *fontTitle, CFont *fontText);
	void FreeDiaryView();	//생성된 CStatic을 제거해주는 함수
};


