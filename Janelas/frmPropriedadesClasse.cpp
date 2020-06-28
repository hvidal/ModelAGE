//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "frmPropriedadesClasse.h"

// Edição de atributos
#include "X_frmAtributo.h"
#include "X_frmMetodo.h"

//---------------------------------------------------------------------------
#pragma link "frmPropriedadesObjeto"
#pragma link "Grids"
#pragma resource "*.dfm"

#include "Objetos\ItemClasse\Metodo.h"
#include "Objetos\ItemClasse\Atributo.h"

TfrmClassProperties *frmClassProperties;
//---------------------------------------------------------------------------
__fastcall TfrmClassProperties::TfrmClassProperties(TComponent* Owner)
	: TfrmObjectProperties(Owner)
{
    ListaAtributos = new TList();
    ListaMetodos   = new TList();
}
//---------------------------------------------------------------------------
void TfrmClassProperties::SetListaAtributos(TList *lista)
{
    ListaAtributos->Clear();
    for(int i=0; i < lista->Count; i++)
        ListaAtributos->Add(((Atributo*)lista->Items[i])->Clone());
    RefreshGridAtributos();
}
//---------------------------------------------------------------------------
void TfrmClassProperties::SetListaMetodos(TList *lista)
{
    ListaMetodos->Clear();
    for(int i=0; i < lista->Count; i++)
        ListaMetodos->Add(((Metodo*)lista->Items[i])->Clone());
    RefreshGridMetodos();
}
//---------------------------------------------------------------------------
TList* TfrmClassProperties::GetListaAtributos()
{
    return ListaAtributos;
}
//---------------------------------------------------------------------------
TList* TfrmClassProperties::GetListaMetodos()
{
    return ListaMetodos;
}
//---------------------------------------------------------------------------
void TfrmClassProperties::RefreshGridAtributos()
{
    Atributo *atributo;

    // Se não possuir nenhum item, a primeira linha fica vazia
    if(ListaAtributos->Count == 0)
    {
	sg_Atributos->RowCount = 2;
        sg_Atributos->Cells[0][1] = "";
        sg_Atributos->Cells[1][1] = "";
        sg_Atributos->Cells[2][1] = "";
        sg_Atributos->Cells[3][1] = "";
    	return;
    }

    // Senão, preencho o grid com os valores
    sg_Atributos->RowCount = ListaAtributos->Count + 1;
    for(int i = 0; i < ListaAtributos->Count; i++)
    {
    	atributo = (Atributo*)ListaAtributos->Items[i];
        sg_Atributos->Cells[0][i+1] = atributo->GetCharVisibilidade();
        sg_Atributos->Cells[1][i+1] = atributo->GetNome();
        sg_Atributos->Cells[2][i+1] = atributo->GetTipo();
        sg_Atributos->Cells[3][i+1] = atributo->GetValorInicial();
    }
}
//---------------------------------------------------------------------------
void TfrmClassProperties::RefreshGridMetodos()
{
	Metodo *metodo;

    // Se não possuir nenhum item, a primeira linha fica vazia
    if(ListaMetodos->Count == 0)
    {
    	sg_Metodos->RowCount = 2;
        sg_Metodos->Cells[0][1] = "";
        sg_Metodos->Cells[1][1] = "";
        sg_Metodos->Cells[2][1] = "";
        sg_Metodos->Cells[3][1] = "";
    	return;
    }

    // Senão, preencho o grid com os valores
    sg_Metodos->RowCount = ListaMetodos->Count + 1;
    for(int i = 0; i < ListaMetodos->Count; i++)
    {
        metodo = (Metodo*)ListaMetodos->Items[i];
        sg_Metodos->Cells[0][i+1] = metodo->GetCharVisibilidade();
        sg_Metodos->Cells[1][i+1] = metodo->GetNome();
        sg_Metodos->Cells[2][i+1] = metodo->GetTipo();
        sg_Metodos->Cells[3][i+1] = (metodo->IsAbstract())?AnsiString("X"):AnsiString("");
    }
}
//---------------------------------------------------------------------------
void TfrmClassProperties::SetStereotype(AnsiString stereotype)
{
    cb_Stereotype->Text = stereotype;
}
//---------------------------------------------------------------------------
AnsiString TfrmClassProperties::GetStereotype()
{
    return cb_Stereotype->Text;
}
//---------------------------------------------------------------------------
void TfrmClassProperties::SetDocumentation(TStringList *documentation)
{
    mm_Documentation->Lines->Assign(documentation);
}
//---------------------------------------------------------------------------
TStrings* TfrmClassProperties::GetDocumentation()
{
    return mm_Documentation->Lines;
}
//---------------------------------------------------------------------------
void TfrmClassProperties::PreparaGridAtributos()
{
    if(sg_Atributos->RowCount < 2)
    {
    	sg_Atributos->RowCount = 2;
        sg_Atributos->FixedRows = 1;
    }
    sg_Atributos->Cells[0][0] = "";
    sg_Atributos->Cells[1][0] = "Name";
    sg_Atributos->Cells[2][0] = "Type";
    sg_Atributos->Cells[3][0] = "Initial Value";
}
//---------------------------------------------------------------------------
void TfrmClassProperties::PreparaGridMetodos()
{
    if(sg_Metodos->RowCount < 2)
    {
    	sg_Metodos->RowCount = 2;
        sg_Metodos->FixedRows = 1;
    }

    sg_Metodos->Cells[0][0] = "";
    sg_Metodos->Cells[1][0] = "Name";
    sg_Metodos->Cells[2][0] = "Return Type";
    sg_Metodos->Cells[3][0] = "Abstract";
}
//---------------------------------------------------------------------------
void __fastcall TfrmClassProperties::FormActivate(TObject *Sender)
{
    TfrmObjectProperties::FormActivate(Sender);
    LinhaSelecionadaGridAtributos = 0;
    LinhaSelecionadaGridMetodos = 0;
    PreparaGridAtributos();
    PreparaGridMetodos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmClassProperties::mnuInsertAtributoClick(TObject *Sender)
{
    Atributo *novo;
    novo = new Atributo();
    novo->SetNome("name");
    novo->SetTipo("");
    novo->SetVisibilidade(Vis_PRIVATE);
    ListaAtributos->Add(novo);
    RefreshGridAtributos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmClassProperties::mnuDeleteAtributoClick(TObject *Sender)
{
    if(LinhaSelecionadaGridAtributos != 0 && ListaAtributos->Count != 0)
    {
    	ListaAtributos->Delete(LinhaSelecionadaGridAtributos-1);
        RefreshGridAtributos();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmClassProperties::mnuInsertMetodoClick(TObject *Sender)
{
    Metodo *novo;
    novo = new Metodo();
    novo->SetNome("opName");
    novo->SetTipo("");
    novo->SetVisibilidade(Vis_PRIVATE);
    ListaMetodos->Add(novo);
    RefreshGridMetodos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmClassProperties::mnuDeleteMetodoClick(TObject *Sender)
{
    if(LinhaSelecionadaGridMetodos != 0 && ListaMetodos->Count != 0)
    {
	    ListaMetodos->Delete(LinhaSelecionadaGridMetodos-1);
        RefreshGridMetodos();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmClassProperties::mnuSpecificationAtributoClick(
	TObject *Sender)
{
    Atributo *atributo;
    TfrmAtributo *thisWindow;

    if(LinhaSelecionadaGridAtributos != 0 && ListaAtributos->Count != 0)
    {
	    atributo = (Atributo*)ListaAtributos->Items[LinhaSelecionadaGridAtributos-1];
        thisWindow = new TfrmAtributo(Application);

        // Coloco os valores na tela
        thisWindow->SetValores(atributo);

        // Abro a tela
        thisWindow->ShowModal();

        // Recupero os valores da tela e os coloco na variável *atributo
        thisWindow->GetValores(atributo);
        RefreshGridAtributos();
    	delete thisWindow;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmClassProperties::mnuSpecificationMetodoClick(
	TObject *Sender)
{
    Metodo *metodo;
    TfrmMetodo *thisWindow;

    if(LinhaSelecionadaGridMetodos != 0 && ListaMetodos->Count != 0)
    {
    	metodo = (Metodo*)ListaMetodos->Items[LinhaSelecionadaGridMetodos-1];
        thisWindow = new TfrmMetodo(Application);

        // Coloco os valores na tela
        thisWindow->SetValores(metodo);

        // Abro a tela
        thisWindow->ShowModal();

        // Recupero os valores da tela e os coloco na variável *atributo
        thisWindow->GetValores(metodo);
        RefreshGridMetodos();
    	delete thisWindow;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmClassProperties::sg_AtributosSelectCell(
      TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
    LinhaSelecionadaGridAtributos = ARow;
}
//---------------------------------------------------------------------------

void __fastcall TfrmClassProperties::sg_MetodosSelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
    LinhaSelecionadaGridMetodos = ARow;
}
//---------------------------------------------------------------------------

void __fastcall TfrmClassProperties::FormDestroy(TObject *Sender)
{
    delete ListaAtributos, ListaMetodos;
}
//---------------------------------------------------------------------------

