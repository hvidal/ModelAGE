//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "X_frmAtributo.h"
//---------------------------------------------------------------------------
#pragma link "X_frmItemClasse"
#pragma resource "*.dfm"
TfrmAtributo *frmAtributo;
//---------------------------------------------------------------------------
__fastcall TfrmAtributo::TfrmAtributo(TComponent* Owner)
	: TfrmItemClasse(Owner)
{
}
//---------------------------------------------------------------------------
void TfrmAtributo::SetValores(Atributo *atributo)
{
    TfrmItemClasse::SetValores(atributo);
	ed_InitialValue->Text = atributo->GetValorInicial();
}
//---------------------------------------------------------------------------
void TfrmAtributo::GetValores(Atributo *atributo)
{
    TfrmItemClasse::GetValores(atributo);
	atributo->SetValorInicial(ed_InitialValue->Text);
}
//---------------------------------------------------------------------------
