#include "Pintor\ParteObjeto.h"

#ifndef FormaConceitoH

class FormaConceito: public ParteObjeto
{
	public:
        FormaConceito(): ParteObjeto()
        {
        }
        ~FormaConceito()
        {
        }
	    void Paint(TCanvas *Board, int X, int Y, int Height, int Width);
	    void Drag(TCanvas *Board, int X, int Y, int Height, int Width);
};
void FormaConceito::Paint(TCanvas *Board, int X, int Y, int Height, int Width)
{
    Board->Rectangle(X, Y, X + Width, Y - Height);
    Board->MoveTo(X, Y - 3);
    Board->LineTo(X + Width, Y - 3);

    Board->MoveTo(X, Y - Height + 2);
    Board->LineTo(X + Width, Y - Height + 2);
}
void FormaConceito::Drag(TCanvas *Board, int X, int Y, int Height, int Width)
{
    Board->Brush->Style = bsClear;

    Board->Rectangle(X - Width/2, Y - Height/2, X + Width/2, Y + Height/2);

    Board->MoveTo(X - Width/2 + 1, Y + Height/2 - 3);
    Board->LineTo(X  + Width/2 - 1, Y + Height/2 - 3);

    Board->MoveTo(X - Width/2 + 1, Y - Height/2 + 2);
    Board->LineTo(X  + Width/2 - 1, Y - Height/2 + 2);
}
#define FormaConceitoH
#endif