#include "DlgSoruSor.hpp"
#include <HypCStaticText.hpp>

void  CDlgSoruSor::doShowDialogBox (void)
{
    //this->ClearTermKeys();
    //this->InsertTermKey(0, KEY_ENTER);
    HypCStaticText  text1( 0, 5, 80, 20, 100, "Hello World", LTEXT );
    HypCStaticText  text2( 0, 35, 80, 20, 100, "Hello World", LTEXT );
    HypCStaticText  text3( 0, 65, 80, 20, 100, "Hello World", LTEXT );
    this->m_pGWindow->AddControl( text1 );
    this->m_pGWindow->AddControl( text2 );
    this->m_pGWindow->AddControl( text3 );
    //this->m_pGWindow->Open( );
}

void CDlgSoruSor::OnComplete()
{
    int i = 0;
}
void CDlgSoruSor::InsertTermKey( UINT16 id, UINT16 key )
{
    m_pGWindow->AddTermKey(id, key);
}
int CDlgSoruSor::AsyncResult()
{ 
    return 0;
}

void CDlgSoruSor::Cancel()
{
    int i = 0;
}

void CDlgSoruSor::WindowComplete(HypCGrafixWindow& wnd, void* pArg)
{
    wnd.Open();
}

