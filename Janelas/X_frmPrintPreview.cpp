//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "X_frmPrintPreview.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "PagePrnt"
#pragma resource "*.dfm"
TfrmPrintPreview *frmPrintPreview;
//---------------------------------------------------------------------------
__fastcall TfrmPrintPreview::TfrmPrintPreview(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintPreview::btnPrintClick(TObject *Sender)
{
	if(!Prn->Print())
    {
    	MessageBox(0, "You cancelled printing.", "Printing", MB_ICONINFORMATION | MB_OK);
    }    
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintPreview::btnNextPageClick(TObject *Sender)
{
     if(Prn->PageNumber > 1)
     {
          Prn->PageNumber = Prn->PageNumber - 1;
          FormShow(Sender);
     }    
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintPreview::btnPrevPageClick(TObject *Sender)
{
     if (Prn->PageNumber < Prn->PageCount)
     {
          Prn->PageNumber = Prn->PageNumber + 1;
          FormShow(Sender);
     }    
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintPreview::ZoomListClick(TObject *Sender)
{
     switch(ZoomList->ItemIndex)
     {
          case 0:
          	Prn->ZoomPercent = 200;
            break;
          case 1:
          	Prn->ZoomPercent = 175;
            break;
          case 2:
          	Prn->ZoomPercent = 150;
            break;
          case 3:
          	Prn->ZoomPercent = 125;
            break;
          case 4:
	        Prn->ZoomPercent = 100;
            break;
          case 5:
          	Prn->ZoomPercent = 50;
            break;
          case 6:
          	Prn->ZoomToWidth();
            break;
          case 7:
          	Prn->ZoomToHeight();
            break;
          case 8:
          	Prn->ZoomToFit();
            break;
     }
     ZoomTimer->Enabled = true;    
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintPreview::ZoomListKeyPress(TObject *Sender,
      char &Key)
{
     if (Key == 13)
     {
          try
          {
             Prn->ZoomPercent = ZoomList->Text.ToInt();
          }
          catch(...)
          {
          }
          Key = 0;
     }    
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintPreview::ZoomTimerTimer(TObject *Sender)
{
     ZoomTimer->Enabled = false;
     ZoomList->Text = AnsiString((int)Prn->ZoomPercent) + "%";    
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintPreview::FormShow(TObject *Sender)
{
	lblPage->Caption = AnsiString((int)Prn->PageNumber)+ " of " + AnsiString((int)Prn->PageCount);    
}
//---------------------------------------------------------------------------

