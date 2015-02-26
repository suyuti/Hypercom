#include "StepAnketSec.hpp"
#include <HypCTransaction.hpp>
#include <HypCApplication.hpp>
#include <HypCUserInterface.hpp>
#include <HString.hpp>
#include "TransactionTags.h"
#include <HypCList.hpp> 
#include <HypCDialog.hpp> 
#include ".\ScreenBase\Appwindow.hpp"
#include ".\ScreenBase\mainwindow.hpp"
#include ".\Screens\defines.hpp"

#include <compiler.h>
#include <HypCTransaction.hpp>
//#include "YemekSepetiTags.h"
//#include <HypCJournal.hpp>
#include <HypCMsgBox.hpp>
#include <HypCListBox.hpp>


bool CStepAnketSec::doExecute()
{
    HypCTransactionData &TransData = Transaction().TransactionData();
    HypCListBox *listbox = Transaction().GetUserInterface()->ListBox();
    listbox->SetTitle("Yuklu Anketler");
    char buf[50];
    for( int i=0; i<17; i++)
    {
        sprintf( buf, "Anket%d", i );
        listbox->AddItem( buf );
    }

    listbox->ShowList();
    int res = listbox->ListResult();
    if( res < 0 )
    {
        return true;
    }
    HString itemTxt = listbox->GetItem(res);
    TransData.insert(TransactionTag::SECILEN_ANKET, itemTxt.c_str());

//    HypCMsgBox* msgbox = Transaction().GetUserInterface()->MsgBox();
//    HypMsgBoxParam Msg1 ( "ListBox result:", buf, BUTTON_OK, 0 );
//    msgbox->Message( Msg1 );
    return false;
}
