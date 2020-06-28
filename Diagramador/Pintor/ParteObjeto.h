#include "Pintor/Figura.h"

#ifndef ParteObjetoH

class ParteObjeto: public Figura
{
	private:
    protected:
    public:
    	ParteObjeto(): Figura()
        {
        }
    	~ParteObjeto()
        {
        }

        // Abstratos:
	    virtual void Paint(TCanvas *Board, int X, int Y, int Height, int Width)=0;
	    virtual void Drag(TCanvas *Board, int X, int Y, int Height, int Width)=0;

        //SingleLine
        void PaintTextSingleLine(TCanvas *Board, AnsiString Name, int X, int Y, int Height, int Width);
		void PaintTextSingleLineCustom(int Altura, TCanvas *Board, AnsiString Name, int X, int Y, int Height, int Width);

        // MultiLine
        void PaintTextMultiLine(TCanvas *Board, TStringList *Linhas, int X, int Y, int Height, int Width, int Align);
		void PaintTextMultiLineCustom(int Altura, TCanvas *Board, TStringList *Linhas, int X, int Y, int Height, int Width, int Align);
		void AlinhaEsquerdaMultiLine(int Altura, TCanvas *Board, TStringList *Linhas, int X, int Y, int Height, int Width);
		void AlinhaDireitaMultiLine(int Altura, TCanvas *Board, TStringList *Linhas, int X, int Y, int Height, int Width);
		void AlinhaCentroMultiLine(int Altura, TCanvas *Board, TStringList *Linhas, int X, int Y, int Height, int Width);

        // Seleciona
	    void Seleciona(TCanvas *Board, int X, int Y, int Height, int Width, bool selected);
};
void ParteObjeto::PaintTextSingleLine(TCanvas *Board, AnsiString Name, int X, int Y, int Height, int Width)
{
    Board->Brush->Style = bsClear;

	int MeioObjeto;
    MeioObjeto = Y - Height/2 - (Board->TextHeight(Name))/2;
	PaintTextSingleLineCustom(MeioObjeto, Board, Name, X, Y, Height, Width);
}
void ParteObjeto::PaintTextSingleLineCustom(int Altura, TCanvas *Board, AnsiString Name, int X, int Y, int Height, int Width)
{
    Board->Brush->Style = bsClear;

   	int x = Board->TextWidth(Name) - Width;
   	Board->TextOut(X - x/2, Altura, Name);
}
void ParteObjeto::PaintTextMultiLine(TCanvas *Board, TStringList *Linhas, int X, int Y, int Height, int Width, int Align)
{
    Board->Brush->Style = bsClear;

	int MeioObjeto;
    MeioObjeto = Y - Height/2 - (Board->TextHeight("X")*Linhas->Count)/2;
	PaintTextMultiLineCustom(MeioObjeto, Board, Linhas, X, Y, Height, Width, Align);
}
void ParteObjeto::PaintTextMultiLineCustom(int Altura, TCanvas *Board, TStringList *Linhas, int X, int Y, int Height, int Width, int Align)
{
	// Alinhamento:
	// 1 - Esquerda
	// 2 - Centro
	// 3 - Direita

    Board->Brush->Style = bsClear;

	switch(Align)
	{
		case 1:
			AlinhaEsquerdaMultiLine(Altura, Board, Linhas, X, Y, Height, Width);
			break;
		case 2:
			AlinhaCentroMultiLine(Altura, Board, Linhas, X, Y, Height, Width);
			break;
		case 3:
			AlinhaDireitaMultiLine(Altura, Board, Linhas, X, Y, Height, Width);
			break;
	}
}
void ParteObjeto::AlinhaEsquerdaMultiLine(int Altura, TCanvas *Board, TStringList *Linhas, int X, int Y, int Height, int Width)
{
    int c, indiceLinha = 0;
    AnsiString Linha;

    // Texto Alinhado à Esquerda
    for(c = 0; c < Linhas->Count; c++)
    {
    	Linha = RetiraFaker(Linhas->Strings[indiceLinha]);
    	Board->TextOut(X + 2, Altura, Linha);
		Altura += Board->TextHeight(Linha);
		indiceLinha++;
    }
}
void ParteObjeto::AlinhaDireitaMultiLine(int Altura, TCanvas *Board, TStringList *Linhas, int X, int Y, int Height, int Width)
{
    int c, x, indiceLinha = 0;
    AnsiString Linha;

    // Texto Alinhado à direita
    for(c = 0; c < Linhas->Count; c++)
    {
    	Linha = RetiraFaker(Linhas->Strings[indiceLinha]);
		x = Board->TextWidth(Linha);
    	Board->TextOut(X + Width - x - 2, Altura, Linha);
		Altura += Board->TextHeight(Linha);
		indiceLinha++;
    }
}
void ParteObjeto::AlinhaCentroMultiLine(int Altura, TCanvas *Board, TStringList *Linhas, int X, int Y, int Height, int Width)
{
    int c, x, indiceLinha = 0;
    AnsiString Linha;

    // Texto Alinhado ao centro
    for(c = 0; c < Linhas->Count; c++)
    {
    	Linha = RetiraFaker(Linhas->Strings[indiceLinha]);
    	x = Board->TextWidth(Linha) - Width;
    	Board->TextOut(X - x/2, Altura, Linha);
		Altura += Board->TextHeight(Linha);
		indiceLinha++;
    }
}
void ParteObjeto::Seleciona(TCanvas *Board, int X, int Y, int Height, int Width, bool selected)
{
    if(selected)
    {
		Board->Pen->Color = clBlack;
        Board->Brush->Color = clBlack;

        Board->Pen->Style = psSolid;
        Board->Brush->Style = bsSolid;

        Board->Rectangle(X - 2, Y - 2 , X + 3, Y + 3);
        Board->Rectangle(X + Width/2 - 2, Y - 2 , X + Width/2 + 3, Y + 3);
        Board->Rectangle(X + Width - 2, Y - 2 , X + Width + 3, Y + 3);

        Board->Rectangle(X + Width - 2, Y - Height/2 - 2 , X + Width + 3, Y - Height/2 + 3);

        Board->Rectangle(X - 2, Y - Height - 2 , X + 3, Y - Height + 3);
        Board->Rectangle(X + Width/2 - 2, Y - Height - 2 , X + Width/2 + 3, Y - Height + 3);
        Board->Rectangle(X + Width - 2, Y - Height - 2 , X + Width + 3, Y - Height + 3);

        Board->Rectangle(X - 2, Y - Height/2 - 2 , X + 3, Y - Height/2 + 3);
    }
}
#define ParteObjetoH
#endif