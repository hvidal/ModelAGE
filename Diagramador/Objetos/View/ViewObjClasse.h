#include "Objetos\View\ViewObjeto.h"

#include "Pintor\PartesObjeto\FormaClasse.h"

#include "Objetos\ItemClasse\Metodo.h"
#include "Objetos\ItemClasse\Atributo.h"

#ifndef ViewObjClasseH

class ViewObjClasse: public ViewObjeto
{
    int *FitHeight;
    bool *Hide;
    FormaClasse *minhaForma;

 public:
    ViewObjClasse(): ViewObjeto()
    {
        FitHeight = new int;
        Hide = new bool;

        *DefaultHeight = 50;
        *DefaultWidth = 60;

        minhaForma = new FormaClasse();
        SetHide(false);
    }
    ~ViewObjClasse()
    {
        delete FitHeight, Hide, minhaForma;
    }
    int DefaultSize_Height()
    {
        return *DefaultHeight;
    }
    int DefaultSize_Width()
    {
        return *DefaultWidth;
    }
    int MinHeight()
    {
        return *FitHeight;
    }
    int MinWidth()
    {
        return 30;
    }
    int MaxHeight()
    {
        return 3000;
    }
    int MaxWidth()
    {
        return 1000;
    }

    int GetNumeroLinhasTitulo();

    void SetHeight(TCanvas *Board);

    void SetHide(bool HideValue);
    bool GetHide();

    void Paint(TCanvas *Board);
    void Drag(TPaintBox *Board, int X, int Y);

	void SalvaView(int Ordem, TIniFile *INITIAL);
	void CarregaView(int Ordem, TIniFile *INITIAL);
};

int ViewObjClasse::GetNumeroLinhasTitulo()
{
    int NumeroLinhasTitulo = 1;
    if(((ObjClasse*)GetCorpo())->GetStereotype()!="") NumeroLinhasTitulo++;
    if(((ObjClasse*)GetCorpo())->GetParent() != "Logical View") NumeroLinhasTitulo++;
    return NumeroLinhasTitulo;
}
void ViewObjClasse::SetHide(bool HideValue)
{
	*Hide = HideValue;
}
void ViewObjClasse::SetHeight(TCanvas *Board)
{
    int TextHeight = Board->TextHeight("X");

    ObjClasse *corpo;
    corpo = (ObjClasse*)GetCorpo();

    // Preciso atualizar o valor do número de atributos e métodos
    // porque quando este número vale zero, as linhas divisoras da
    // classe ficam coladas uma nas outras...
    int NumeroAtributos, NumeroMetodos;

    // ... Numero de atributos...
    if (corpo->GetListaAtributos()->Count == 0) NumeroAtributos = 1;
    else NumeroAtributos = corpo->GetListaAtributos()->Count;
    // ... Numero de metodos...
    if (corpo->GetListaMetodos()->Count == 0) NumeroMetodos = 1;
    else NumeroMetodos = corpo->GetListaMetodos()->Count;

    // Comparo e calculo o valor do height
    if(*Hide)
    {
	    *FitHeight = TextHeight * GetNumeroLinhasTitulo() + IconSize * 2 + 7;
    	*Height = *FitHeight;
    }
    else
    {
	    *FitHeight = TextHeight * GetNumeroLinhasTitulo() + IconSize*(NumeroAtributos + NumeroMetodos) + 7;
	    if(*Height < *FitHeight)
	    {
	    	*Height = *FitHeight;
	    }
    }
}
bool ViewObjClasse::GetHide()
{
	return *Hide;
}
void ViewObjClasse::Paint(TCanvas *Board)
{
    if(!*Visible) return;

    ObjClasse *corpo;
    corpo = (ObjClasse*)GetCorpo();

    // Pinta o Retângulo
    Board->Pen->Color = *LineColor;
    Board->Pen->Style = psSolid;
    Board->Brush->Color = *FillColor;
    Board->Brush->Style = bsSolid;
    Board->Font = TextFont;

	SetHeight(Board);

    // Atualizo
    minhaForma->SetListaAtributos(corpo->GetListaAtributos());
    minhaForma->SetListaMetodos(corpo->GetListaMetodos());
    minhaForma->SetHiddenDetails(GetHide());

    minhaForma->SetNumeroLinhasTitulo(GetNumeroLinhasTitulo());

    minhaForma->Paint(Board, *Xpos, *Ypos, *Height, *Width);

    int Altura = *Ypos - *Height;

    if(corpo->GetStereotype()!="")
    {
	    minhaForma->PaintTextSingleLineCustom(Altura, Board, corpo->GetStringStereotype(), *Xpos, *Ypos, *Height, *Width);
        Altura += Board->TextHeight("X");
    }
    minhaForma->PaintTextSingleLineCustom(Altura, Board, corpo->GetName(), *Xpos, *Ypos, *Height, *Width);
    if(corpo->GetParent() != "Logical View")
    {
        Altura += Board->TextHeight("X");
	    minhaForma->PaintTextSingleLineCustom(Altura, Board, corpo->GetStringParent(), *Xpos, *Ypos, *Height, *Width);
    }

    minhaForma->Seleciona(Board, *Xpos, *Ypos, *Height, *Width, *isSelected || *GroupSelected);
}
void ViewObjClasse::Drag(TPaintBox *Board, int X, int Y)
{
    ObjClasse *corpo;
    corpo = (ObjClasse*)GetCorpo();

    // Atualizo
    minhaForma->SetListaAtributos(corpo->GetListaAtributos());
    minhaForma->SetListaMetodos(corpo->GetListaMetodos());
    minhaForma->SetHiddenDetails(GetHide());

    minhaForma->Drag(Board->Canvas, X, Y, *Height, *Width);
    *Xpos = X - *Width/2;
    *Ypos = Y + *Height/2;
}

void ViewObjClasse::SalvaView(int Ordem, TIniFile *INITIAL)
{
/*	int cont;
    Atributo *atributo;
    Metodo *metodo;

    SalvaObjeto(Ordem, INITIAL);

    INITIAL->WriteBool("Objeto" + AnsiString(Ordem), "Hide", *Hide);
    INITIAL->WriteInteger("Objeto" + AnsiString(Ordem), "NAttr", listaAtributos->Count);
    INITIAL->WriteInteger("Objeto" + AnsiString(Ordem), "NMeth", listaMetodos->Count);

    for(cont = 0; cont < listaAtributos->Count; cont++)
    {
    	atributo = GetAtributo(cont);
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "Attr" + AnsiString(cont), atributo->GetNome());
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "AttrT" + AnsiString(cont), atributo->GetTipo());
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "AttrV" + AnsiString(cont), atributo->GetVisibilidade());
    }
    for(cont = 0; cont < listaMetodos->Count; cont++)
    {
    	metodo = GetMetodo(cont);
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "Meth" + AnsiString(cont), metodo->GetNome());
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "MethT" + AnsiString(cont), metodo->GetTipo());
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "MethV" + AnsiString(cont), metodo->GetVisibilidade());
    }
*/
}
void ViewObjClasse::CarregaView(int Ordem, TIniFile *INITIAL)
{
/*
	int cont, Qtd;
    AnsiString Nome, Tipo, Visibilidade;
    Atributo *atributo;
    Metodo *metodo;

    CarregaObjeto(Ordem, INITIAL);

    *Hide = INITIAL->ReadBool("Objeto" + AnsiString(Ordem), "Hide", false);

    Qtd = INITIAL->ReadInteger("Objeto" + AnsiString(Ordem),"NAttr", 0);
    for(cont = 0; cont < Qtd; cont++)
    {
    	atributo = new Atributo();
    	Nome = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "Attr" + AnsiString(cont), ""));
        atributo->SetNome(Nome);

        Tipo = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "AttrT" + AnsiString(cont), ""));
        atributo->SetTipo(Tipo);

        Visibilidade = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "AttrV" + AnsiString(cont), ""));
        atributo->SetVisibilidade(atributo->GetIndexVisibilidade(Visibilidade));

        InsereAtributo(atributo);
    }

    Qtd = INITIAL->ReadInteger("Objeto" + AnsiString(Ordem),"NMeth", 0);
    for(cont = 0; cont < Qtd; cont++)
    {
    	metodo = new Metodo();

    	Nome = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "Meth" + AnsiString(cont), ""));
        metodo->SetNome(Nome);

        Tipo = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "MethT" + AnsiString(cont), ""));
        metodo->SetTipo(Tipo);

        Visibilidade = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "MethV" + AnsiString(cont), ""));
        metodo->SetVisibilidade(metodo->GetIndexVisibilidade(Visibilidade));

        InsereMetodo(metodo);
    }
*/
}
#define ViewObjClasseH
#endif