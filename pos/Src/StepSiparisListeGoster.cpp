#define _INCLUDE_NUCLEUS_FILE_
#include "StepSiparisListeGoster.hpp"
#include <HypCTransaction.hpp>
#include <HypCUserInterface.hpp>
#include <HypCDialog.hpp>
#include <HypCInfoBox.hpp> 
#include <HypCPINEntryScreen.hpp>
#include <HypCList.hpp>
#include <HypCMsgBox.hpp>
#include <HypCFile.hpp>
#include "Utils\FileSysUtils.hpp"

#define	HOW_MANU_FILES	20

bool CStepSiparisListeGoster::doExecute()
{
	FillListe();

    //HypCDialog *pDlg = Transaction().GetUserInterface()->DialogBox("Dlg");
    //pDlg->ShowDialogBox();
    //SetExecAction( TRANS_END );
    return true;
}

void CStepSiparisListeGoster::FillListe()
{
	CFileSysUtils::InitDisks();
	int idx = 0;
	HypCList* pListBox = Transaction().GetUserInterface()->List();
	pListBox->SetOption(HypCList::OPT_CURRENT_ITEM);
	pListBox->SetTitle("Siparisler");
	pListBox->ClearList();

	STATUS stat;
	DSTAT obj;
    char pattern[] = "\\GelSips\\*.sip";

	stat = NU_Get_First(&obj, pattern);
	if (stat == NU_SUCCESS) {
		pListBox->InsertListItem( obj.lfname );
		while ((stat = NU_Get_Next(&obj)) == NU_SUCCESS) {
			pListBox->InsertListItem( obj.lfname );
		}
	}

	pListBox->InsertCmdItem("Yazdir");
	pListBox->InsertCmdItem("Sil");
	pListBox->InsertCmdItem("Hepsini Sil");

	pListBox->SetOption(HypCList::OPT_SELECT_ON_NUMBER | HypCList::OPT_AUTO_NUMBERS | HypCList::OPT_CURRENT_ITEM);
	//pListBox->ShowList(false, false);
	bool prev = (idx)? true : false;
	bool next = (idx < 4) ? true : false;
	bool cont = true;
	int cmdres, listres;
	char buf[50];

	int res = pListBox->ShowList( prev, next);
	switch ( res )
	{
		case HypCList::RES_CANCEL:
			return;
		case HypCList::RES_NEXT:
			idx += 1;
			if (idx > 4) idx = 4;
		break;
		case HypCList::RES_PRIOR:
			idx -= 1;
			if (idx < 0 ) idx = 0;
		break;
		case HypCList::RES_COMMAND:
		case HypCList::RES_ENTER:
			cont = false;
			cmdres = pListBox->CmdResult();
			//listres = pListBox->
		break;
	}
	switch (cmdres) {
		case 0: // Yazdir
			OnCmdYazdir();
		break;
		case 1:	// Sil
			OnCmdSil();
		break;
		case 2:	// Hepsini Sil
			OnCmdTumunuSil();
		break;
        default:
        ;
	}
}
void CStepSiparisListeGoster::OnCmdTumunuSil()
{
	STATUS stat;
	DSTAT obj;
	char pattern[] = "\\GelSips\\*.sip";
    char deletingFileName[100];

	stat = NU_Get_First(&obj, pattern);
	if (stat == NU_SUCCESS) {
        sprintf(deletingFileName, "\\%s\\%s", "GelSips", obj.lfname);
        stat = NU_Delete(deletingFileName);
		while ((stat = NU_Get_Next(&obj)) == NU_SUCCESS) {
            sprintf(deletingFileName, "\\%s\\%s", "GelSips", obj.lfname);
			stat = NU_Delete(deletingFileName);
		}
	}
	FillListe();
}
void CStepSiparisListeGoster::OnCmdYazdir()
{
}
void CStepSiparisListeGoster::OnCmdSil()
{
}
