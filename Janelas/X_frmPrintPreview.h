//---------------------------------------------------------------------------

#ifndef X_frmPrintPreviewH
#define X_frmPrintPreviewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "PagePrnt.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmPrintPreview : public TForm
{
__published:	// IDE-managed Components
    TTimer *ZoomTimer;
    TPagePrinter *Prn;
    TPanel *Panel1;
    TLabel *Label1;
    TLabel *lblPage;
    TSpeedButton *btnNextPage;
    TSpeedButton *btnPrevPage;
    TBitBtn *btnPrint;
    TComboBox *ZoomList;
    void __fastcall btnPrintClick(TObject *Sender);
    void __fastcall btnNextPageClick(TObject *Sender);
    void __fastcall btnPrevPageClick(TObject *Sender);
    void __fastcall ZoomListClick(TObject *Sender);
    void __fastcall ZoomListKeyPress(TObject *Sender, char &Key);
    void __fastcall ZoomTimerTimer(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmPrintPreview(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrintPreview *frmPrintPreview;
//---------------------------------------------------------------------------
#endif
