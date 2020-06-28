//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include "Splash.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TfrmSplash *frmSplash;
//---------------------------------------------------------------------------
__fastcall TfrmSplash::TfrmSplash(TComponent* Owner)
	: TForm(Owner)
{
	randomize();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSplash::Timer1Timer(TObject *Sender)
{
    f->Position += random(10);
    if(f->Position >= 100)
    {
    	Timer1->Enabled = false;
    	frmSplash->Close();
    }
    else if(f->Position >= 0 && f->Position <= 20)
    {
    	lb_Info->Caption = "Loading Resources...";
    }
    else if(f->Position > 20 && f->Position <= 43)
    {
    	lb_Info->Caption = "Loading Classes...";
    }
    else if(f->Position > 43 && f->Position <= 68)
    {
    	lb_Info->Caption = "Loading Domain Resources...";
    }
    else if(f->Position > 68 && f->Position <= 90)
    {
    	lb_Info->Caption = "Loading Dynamic Components...";
    }
    else if(f->Position > 90)
    {
    	lb_Info->Caption = "Initializing ModelAGE...";
    }

}
//---------------------------------------------------------------------------