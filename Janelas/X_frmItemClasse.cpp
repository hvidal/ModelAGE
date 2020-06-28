//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "X_frmItemClasse.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TfrmItemClasse *frmItemClasse;
//---------------------------------------------------------------------------
__fastcall TfrmItemClasse::TfrmItemClasse(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
int TfrmItemClasse::ResultOK()
{
	return Result;
}
//---------------------------------------------------------------------------
void TfrmItemClasse::SetVisibilidade(int visibilidade)
{
	if (visibilidade == Vis_PRIVATE)
    	rb_Private->Checked = true;
    else if (visibilidade == Vis_PROTECTED)
    	rb_Protected->Checked = true;
    else
    	rb_Public->Checked = true;
}
//---------------------------------------------------------------------------
int TfrmItemClasse::GetVisibilidade()
{
	if (rb_Private->Checked)
    	return Vis_PRIVATE;
    else if (rb_Protected->Checked)
    	return Vis_PROTECTED;
    else
    	return Vis_PUBLIC;
}
//---------------------------------------------------------------------------
void TfrmItemClasse::SetValores(ItemClasse *itemClasse)
{
	ed_Name->Text = itemClasse->GetNome();
    cb_Type->Text = itemClasse->GetTipo();
    cb_Stereotype->Text = itemClasse->GetEstereotipo();
    ed_PropertyString->Text = itemClasse->GetPropertyString();
    SetVisibilidade(itemClasse->GetVisibilidade());
    mm_Documentation->Lines->Assign(itemClasse->GetDocumentacao());
}
//---------------------------------------------------------------------------
void TfrmItemClasse::GetValores(ItemClasse *itemClasse)
{
	itemClasse->SetNome(ed_Name->Text);
	itemClasse->SetTipo(cb_Type->Text);
	itemClasse->SetEstereotipo(cb_Stereotype->Text);
	itemClasse->SetPropertyString(ed_PropertyString->Text);
	itemClasse->SetVisibilidade(GetVisibilidade());
	itemClasse->SetDocumentacao((TStringList*)mm_Documentation->Lines);
}
//---------------------------------------------------------------------------
void __fastcall TfrmItemClasse::btnCancelarClick(TObject *Sender)
{
	Result = 0;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmItemClasse::btnOKClick(TObject *Sender)
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