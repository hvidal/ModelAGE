//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "X_frmMetodo.h"
//---------------------------------------------------------------------------
#pragma link "X_frmItemClasse"
#pragma link "Grids"
#pragma resource "*.dfm"
TfrmMetodo *frmMetodo;
//---------------------------------------------------------------------------
__fastcall TfrmMetodo::TfrmMetodo(TComponent* Owner)
	: TfrmItemClasse(Owner)
{
    ListaArgumentos = new TList();
}
//---------------------------------------------------------------------------
void TfrmMetodo::PreparaGridArgumentos()
{
    if(sg_Argumentos->RowCount < 2)
    {
    	sg_Argumentos->RowCount = 2;
        sg_Argumentos->FixedRows = 1;
    }

    sg_Argumentos->Cells[0][0] = "Name";
    sg_Argumentos->Cells[1][0] = "Type";
    sg_Argumentos->Cells[2][0] = "Default";
    sg_Argumentos->Cells[3][0] = "Documentation";
}
//---------------------------------------------------------------------------
void TfrmMetodo::RefreshGridArgumentos()
{
    Argumento *argumento;

    // Se não possuir nenhum item, a primeira linha fica vazia
    if(ListaArgumentos->Count == 0)
    {
	sg_Argumentos->RowCount = 2;
        sg_Argumentos->Cells[0][1] = "";
        sg_Argumentos->Cells[1][1] = "";
        sg_Argumentos->Cells[2][1] = "";
        sg_Argumentos->Cells[3][1] = "";
    	return;
    }

    // Senão, preencho o grid com os valores
    sg_Argumentos->RowCount = ListaArgumentos->Count + 1;
    for(int i = 0; i < ListaArgumentos->Count; i++)
    {
        argumento = (Argumento*)ListaArgumentos->Items[i];
        sg_Argumentos->Cells[0][i+1] = argumento->GetNome();
        sg_Argumentos->Cells[1][i+1] = argumento->GetTipo();
        sg_Argumentos->Cells[2][i+1] = argumento->GetDefault();
        sg_Argumentos->Cells[3][i+1] = argumento->GetDocumentation();
    }
}
//---------------------------------------------------------------------------
void TfrmMetodo::SetListaArgumentos(TList *lista)
{
    ListaArgumentos->Clear();
    for(int i=0; i < lista->Count; i++)
        ListaArgumentos->Add(lista->Items[i]);
    RefreshGridArgumentos();
}
//---------------------------------------------------------------------------
void TfrmMetodo::SetValores(Metodo *metodo)
{
    TfrmItemClasse::SetValores(metodo);
    cbx_Abstract->Checked = metodo->IsAbstract();
    mm_PreConditions->Lines->Assign(metodo->GetPreCondicoes());
    mm_PostConditions->Lines->Assign(metodo->GetPosCondicoes());
    SetListaArgumentos(metodo->GetListaArgumentos());
    RefreshGridArgumentos();
}
//---------------------------------------------------------------------------
void TfrmMetodo::GetValores(Metodo *metodo)
{
    TfrmItemClasse::GetValores(metodo);
    metodo->SetAbstract(cbx_Abstract->Checked);
    metodo->SetPreCondicoes((TStringList*)mm_PreConditions->Lines);
    metodo->SetPosCondicoes((TStringList*)mm_PostConditions->Lines);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMetodo::FormActivate(TObject *Sender)
{
    pc_Dados->ActivePage = ts_General;
    LinhaSelecionadaGridArgumentos = 0;
    PreparaGridArgumentos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMetodo::mnuDeleteClick(TObject *Sender)
{
    if(LinhaSelecionadaGridArgumentos != 0 && ListaArgumentos->Count != 0)
    {
	ListaArgumentos->Delete(LinhaSelecionadaGridArgumentos-1);
        RefreshGridArgumentos();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMetodo::mnuInsertClick(TObject *Sender)
{
    Argumento *novo;
    novo = new Argumento();
    novo->SetNome("argName");
    novo->SetTipo("argType");
    novo->SetDefault("defaultValue");
    novo->SetDocumentation("");
    ListaArgumentos->Add(novo);
    RefreshGridArgumentos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMetodo::sg_ArgumentosSelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
    LinhaSelecionadaGridArgumentos = ARow;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMetodo::sg_ArgumentosSetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
    Argumento *argumento;
    argumento = (Argumento*)ListaArgumentos->Items[ARow-1];
    if(ACol == 0)
    	argumento->SetNome(Value);
    else if(ACol == 1)
    	argumento->SetTipo(Value);
    else if(ACol == 2)
    	argumento->SetDefault(Value);
    else if(ACol == 3)
    	argumento->SetDocumentation(Value);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMetodo::FormDestroy(TObject *Sender)
{
    delete ListaArgumentos;
}
//---------------------------------------------------------------------------

