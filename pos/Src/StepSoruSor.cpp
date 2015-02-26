#include "StepSoruSor.hpp"
#include <HypCTransaction.hpp>
#include <HypCUserInterface.hpp>
#include <HypCDialog.hpp>
#include <HypCInfoBox.hpp> 
#include <HypCPINEntryScreen.hpp>

bool CStepSoruSor::doExecute()
{
    //HypCDialog *pDlg = Transaction().GetUserInterface()->DialogBox("Dlg");
    //pDlg->ShowDialogBox();
    //SetExecAction( TRANS_END );
    HypCPINEntryScreen *pDlg = (HypCPINEntryScreen *)Transaction().GetUserInterface()->DialogBox("Dlg");
    HypInfoParam ip;
    ip.Title = HString("title");
    ip.Message = HString("msg");
    pDlg->Show(ip);
    SetExecAction( TRANS_END );
    return true;
}

