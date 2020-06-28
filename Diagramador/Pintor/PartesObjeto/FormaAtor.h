#include "Pintor\ParteObjeto.h"

#ifndef FormaAtorH

class FormaAtor: public ParteObjeto
{
	public:
        FormaAtor(): ParteObjeto()
        {
        }
        ~FormaAtor()
        {
        }
	    void Paint(TCanvas *Board, int X, int Y, int Height, int Width);
	    void Drag(TCanvas *Board, int X, int Y, int Height, int Width);
        void LimpaFundo(TCanvas *Board, int X, int Y, int Height, int Width);
};
void FormaAtor::Paint(TCanvas *Board, int X, int Y, int Height, int Width)
{
    Board->Ellipse(X + Width/2 - 7, Y - Height, X + Width/2 + 7, Y - Height + 14);

    // Tronco
    Board->MoveTo(X + Width/2, Y - Height + 14);
    Board->LineTo(X + Width/2, Y - Height + 30);

    // Perna Esquerda
    Board->LineTo(X + Width/2 - 9, Y - Height + 45);

    // Perna Direita
    Board->MoveTo(X + Width/2, Y - Height + 30);
    Board->LineTo(X + Width/2 + 9, Y - Height + 45);

    // Braços
    Board->MoveTo(X + Width/2 - 9, Y - Height + 20);
    Board->LineTo(X + Width/2 + 9, Y - Height + 20);
}
void FormaAtor::Drag(TCanvas *Board, int X, int Y, int Height, int Width)
{
    Board->Brush->Style = bsClear;

    Board->Ellipse(X - 7, Y - Height/2, X + 7, Y - Height/2 + 14);

    // Tronco
    Board->MoveTo(X , Y - Height/2 + 14);
    Board->LineTo(X, Y - Height/2 + 30);

    // Perna Esquerda
    Board->LineTo(X - 9, Y - Height/2 + 45);

    // Perna Direita
    Board->MoveTo(X, Y - Height/2 + 30);
    Board->LineTo(X + 9, Y - Height/2 + 45);

    // Braços
    Board->MoveTo(X - 9, Y - Height/2 + 20);
    Board->LineTo(X + 9, Y - Height/2 + 20);
}
void FormaAtor::LimpaFundo(TCanvas *Board, int X, int Y, int Height, int Width)
{
    Board->Pen->Color = clWhite;
    Board->Pen->Style = psSolid;
    Board->Brush->Color = clWhite;
    Board->Brush->Style = bsSolid;
    Board->Rectangle(X, Y, X + Width, Y - Height);
}
#define FormaAtorH
#endif