#ifndef _DLGSORUSOR_HPP_
#define _DLGSORUSOR_HPP_
#include <HypCDialog.hpp>

class CDlgSoruSor : public HypCDialog 
{
public:
    CDlgSoruSor (HypCUserInterface *iface, const HypCFont *pTextFont, const HypCFont *pTitleFont, HypCGrafixWindow *window) : HypCDialog (iface,pTextFont,pTitleFont,window) {};
    virtual ~CDlgSoruSor() {};

    virtual int AsyncResult();
    virtual void Cancel();
    virtual const HString ClassName() { return "CDlgSoruSor";};

protected:
    virtual void InsertTermKey( UINT16 id, UINT16 key );
    virtual void  doShowDialogBox (void);
    virtual void OnComplete();

    void static WindowComplete(HypCGrafixWindow& wnd, void* pArg);
};
#endif
