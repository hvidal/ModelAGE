//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "frmPropriedadesObjeto.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"

TfrmObjectProperties *frmObjectProperties;
//---------------------------------------------------------------------------
__fastcall TfrmObjectProperties::TfrmObjectProperties(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmObjectProperties::btnCancelarClick(TObject *Sender)
{
	Result = 0;
	Close();
}
//---------------------------------------------------------------------------
int TfrmObjectProperties::ResultOK()
{
	return Result;
}
//---------------------------------------------------------------------------
void TfrmObjectProperties::SetObjectName(AnsiString name)
{
	ed_Name->Text = name;
}
//---------------------------------------------------------------------------
AnsiString TfrmObjectProperties::GetObjectName()
{
	return ed_Name->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfrmObjectProperties::FormActivate(TObject *Sender)
{
	pc_ObjectProperties->ActivePage = ts_General;
	ed_Name->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmObjectProperties::btnOKClick(TObject *Sender)
{
	if(ed_Name->Text == "")
    {
        ed_Name->SetFocus();
        return;
    }
	Result = 1;
	Close();
}
//---------------------------------------------------------------------------