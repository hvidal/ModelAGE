#include "Pintor\ParteObjeto.h"

#include "Objetos\ItemClasse\Metodo.h"
#include "Objetos\ItemClasse\Atributo.h"

#ifndef FormaClasseH

#define IconSize 15

class FormaClasse: public ParteObjeto
{
	private:
    	bool *HiddenDetails;
        int *NumeroLinhasTitulo;
        TList *listaAtributos, *listaMetodos;

        // Bitmaps
        Graphics::TBitmap *bmpAtributoPrivate;
        Graphics::TBitmap *bmpAtributoProtected;
        Graphics::TBitmap *bmpAtributoPublic;
        Graphics::TBitmap *bmpMetodoPrivate;
        Graphics::TBitmap *bmpMetodoProtected;
        Graphics::TBitmap *bmpMetodoPublic;

	public:
        FormaClasse(): ParteObjeto()
        {
			HiddenDetails = new bool;
            NumeroLinhasTitulo = new int;

            LoadBitmaps();
        }
        ~FormaClasse()
        {
        	delete HiddenDetails, NumeroLinhasTitulo;
            delete bmpAtributoPrivate, bmpAtributoProtected, bmpAtributoPublic,
              bmpMetodoPrivate, bmpMetodoProtected, bmpMetodoPublic;
        }
	    void Paint(TCanvas *Board, int X, int Y, int Height, int Width);
	    void Drag(TCanvas *Board, int X, int Y, int Height, int Width);

        void EscreveAtributos(TCanvas *Board, int X, int Y, int Height, int Width);
        void EscreveMetodos(TCanvas *Board, int X, int Y, int Height, int Width);

        void SetHiddenDetails(bool hiddenValue)
        {
        	*HiddenDetails = hiddenValue;
        }
        void SetListaAtributos(TList *lista)
        {
        	listaAtributos = lista;
        }
        void SetListaMetodos(TList *lista)
        {
        	listaMetodos = lista;
        }
        void SetNumeroLinhasTitulo(int numeroLinhasTitulo)
        {
        	*NumeroLinhasTitulo = numeroLinhasTitulo;
        }

        void LoadBitmaps();
        Graphics::TBitmap* GetBitmap(int Visibilidade, bool Atributo);

};
Graphics::TBitmap* FormaClasse::GetBitmap(int Visibilidade, bool Atributo)
{
    Graphics::TBitmap *bmp;

	if(Atributo)
    {
		if(Visibilidade == Vis_PRIVATE)
        	bmp = bmpAtributoPrivate;
		else if(Visibilidade == Vis_PROTECTED)
        	bmp = bmpAtributoProtected;
		else if(Visibilidade == Vis_PUBLIC)
        	bmp = bmpAtributoPublic;
    }
    else
    {
		if(Visibilidade == Vis_PRIVATE)
        	bmp = bmpMetodoPrivate;
		else if(Visibilidade == Vis_PROTECTED)
        	bmp = bmpMetodoProtected;
		else if(Visibilidade == Vis_PUBLIC)
        	bmp = bmpMetodoPublic;
    }
    return bmp;
}
void FormaClasse::LoadBitmaps()
{
    Graphics::TBitmap *Figuras = new Graphics::TBitmap();
    Byte *ptr;

    Figuras->LoadFromFile("ModelAGE.m01"); // Arquivo contendo os bitmaps

    bmpAtributoPrivate   = new Graphics::TBitmap();
    bmpAtributoProtected = new Graphics::TBitmap();
    bmpAtributoPublic    = new Graphics::TBitmap();
    bmpMetodoPrivate     = new Graphics::TBitmap();
    bmpMetodoProtected   = new Graphics::TBitmap();
    bmpMetodoPublic      = new Graphics::TBitmap();

    bmpAtributoPrivate->Height = IconSize;
    bmpAtributoPrivate->Width = IconSize;

    bmpAtributoProtected->Height = IconSize;
    bmpAtributoProtected->Width = IconSize;

    bmpAtributoPublic->Height = IconSize;
    bmpAtributoPublic->Width = IconSize;

    bmpMetodoPrivate->Height = IconSize;
    bmpMetodoPrivate->Width = IconSize;

    bmpMetodoProtected->Height = IconSize;
    bmpMetodoProtected->Width = IconSize;

    bmpMetodoPublic->Height = IconSize;
    bmpMetodoPublic->Width = IconSize;

    TRect rectOrigem, rectDestino;
    rectDestino = Rect(0,0,IconSize,IconSize);

    rectOrigem = Rect(0,0,IconSize,IconSize);
    bmpAtributoPrivate->Canvas->CopyRect(rectDestino, Figuras->Canvas, rectOrigem);

    rectOrigem = Rect(IconSize,0,2*IconSize,IconSize);
    bmpAtributoProtected->Canvas->CopyRect(rectDestino, Figuras->Canvas, rectOrigem);

    rectOrigem = Rect(2*IconSize,0,3*IconSize,IconSize);
    bmpAtributoPublic->Canvas->CopyRect(rectDestino, Figuras->Canvas, rectOrigem);

    rectOrigem = Rect(3*IconSize,0,4*IconSize,IconSize);
    bmpMetodoPrivate->Canvas->CopyRect(rectDestino, Figuras->Canvas, rectOrigem);

    rectOrigem = Rect(4*IconSize,0,5*IconSize,IconSize);
    bmpMetodoProtected->Canvas->CopyRect(rectDestino, Figuras->Canvas, rectOrigem);

    rectOrigem = Rect(5*IconSize,0,6*IconSize,IconSize);
    bmpMetodoPublic->Canvas->CopyRect(rectDestino, Figuras->Canvas, rectOrigem);

    delete Figuras;
}
void FormaClasse::Paint(TCanvas *Board, int X, int Y, int Height, int Width)
{
    int TextHeight;

    TextHeight = Board->TextHeight("X");

    Board->Rectangle(X, Y, X + Width, Y - Height);

    // Primeira Linha
    Board->MoveTo(X, Y - Height + (TextHeight * (*NumeroLinhasTitulo)) + 2);
    Board->LineTo(X + Width, Y - Height + (TextHeight * (*NumeroLinhasTitulo)) + 2);

    // segunda Linha
    if(*HiddenDetails)
    {
	    Board->MoveTo(X, Y - Height + IconSize + (TextHeight * (*NumeroLinhasTitulo)) + 4);
	    Board->LineTo(X + Width, Y - Height + IconSize + (TextHeight * (*NumeroLinhasTitulo)) + 4);
    }
    else
    {
        // ... Numero de atributos...
        int NumeroAtributos;
        if (listaAtributos->Count == 0) NumeroAtributos = 1;
        else NumeroAtributos = listaAtributos->Count;

	    Board->MoveTo(X, Y - Height + IconSize*(NumeroAtributos) + (TextHeight * (*NumeroLinhasTitulo)) + 4);
	    Board->LineTo(X + Width, Y - Height + IconSize*(NumeroAtributos) + (TextHeight * (*NumeroLinhasTitulo)) + 4);
    }

    if(*HiddenDetails) return;

    EscreveAtributos(Board, X, Y, Height, Width);
    EscreveMetodos(Board, X, Y, Height, Width);
}
void FormaClasse::Drag(TCanvas *Board, int X, int Y, int Height, int Width)
{
    int TextHeight;

    Board->Brush->Style = bsClear;

    if (Board->Pen->Mode == pmXor)
       Board->Pen->Color = clWhite;

    Board->Rectangle(X - Width/2, Y - Height/2, X + Width/2, Y + Height/2);

    TextHeight = Board->TextHeight("X");

    Board->MoveTo(X - Width/2 + 1, Y - Height/2 + (TextHeight * (*NumeroLinhasTitulo)) + 2);
    Board->LineTo(X + Width/2 - 1, Y - Height/2 + (TextHeight * (*NumeroLinhasTitulo)) + 2);

    if(*HiddenDetails)
    {
	    Board->MoveTo(X - Width/2 + 1, Y - Height/2 + TextHeight*(*NumeroLinhasTitulo) + IconSize + 4);
    	Board->LineTo(X  + Width/2 - 1, Y - Height/2 + TextHeight*(*NumeroLinhasTitulo) + IconSize + 4);
    }
    else
    {
        // ... Numero de atributos...
        int NumeroAtributos;
        if (listaAtributos->Count == 0) NumeroAtributos = 1;
        else NumeroAtributos = listaAtributos->Count;

	    Board->MoveTo(X - Width/2 + 1, Y - Height/2 + TextHeight*(*NumeroLinhasTitulo) + IconSize*NumeroAtributos + 4);
    	Board->LineTo(X + Width/2 - 1, Y - Height/2 + TextHeight*(*NumeroLinhasTitulo) + IconSize*NumeroAtributos + 4);
    }
}
void FormaClasse::EscreveAtributos(TCanvas *Board, int X, int Y, int Height, int Width)
{
    Graphics::TBitmap *Icon;
    Atributo *atributo;
    int Altura, c;

    Board->Brush->Style = bsClear;
    int TextHeight = Board->TextHeight("X");

    Altura = Y - Height + (TextHeight * (*NumeroLinhasTitulo)) + 3;
    for(c = 0; c < listaAtributos->Count; c++)
    {
	    atributo = (Atributo*)listaAtributos->Items[c];

        // Pinto o icone da visibilidade
        Board->Draw(X + 2, Altura, GetBitmap(atributo->GetVisibilidade(), true));

        // Escrevo o texto depois do icone
        Board->TextOut(X + 18, Altura, atributo->GetAssinaturaUML());
        Altura += IconSize;
    }
}
void FormaClasse::EscreveMetodos(TCanvas *Board, int X, int Y, int Height, int Width)
{
    Graphics::TBitmap *Icon;
    Metodo *metodo;
    int Altura, c, NumeroAtributos;

    Board->Brush->Style = bsClear;
    int TextHeight = Board->TextHeight("X");

    if(listaAtributos->Count == 0)
		NumeroAtributos = 1;
    else
    	NumeroAtributos = listaAtributos->Count;

    Altura = Y - Height + IconSize*(NumeroAtributos) + (TextHeight * (*NumeroLinhasTitulo)) + 5;
    for(c = 0; c < listaMetodos->Count; c++)
    {
	    metodo = (Metodo*)listaMetodos->Items[c];

        // Pinto o icone da visibilidade
        Board->Draw(X + 2, Altura, GetBitmap(metodo->GetVisibilidade(), false));

        // Escrevo o texto depois do icone
        if(metodo->IsAbstract())
            Board->Font->Style = TFontStyles()<< fsItalic;

        Board->TextOut(X + 18, Altura, metodo->GetAssinaturaUML());
        Board->Font->Style = TFontStyles()>> fsItalic;
        Altura += IconSize;
    }
}

#define FormaClasseH
#endif