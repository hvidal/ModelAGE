//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "frmDomain.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TfrmDominio *frmDominio;
//---------------------------------------------------------------------------
__fastcall TfrmDominio::TfrmDominio(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmDominio::FormClose(TObject *Sender, TCloseAction &Action)
{
	delete this;	
}
//---------------------------------------------------------------------------