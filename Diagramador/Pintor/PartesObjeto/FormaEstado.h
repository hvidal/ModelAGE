#include "Pintor\ParteObjeto.h"

#ifndef FormaEstadoH

class FormaEstado: public ParteObjeto
{
	public:
        FormaEstado(): ParteObjeto()
        {
        }
        ~FormaEstado()
        {
        }
	    void Paint(TCanvas *Board, int X, int Y, int Height, int Width);
	    void Drag(TCanvas *Board, int X, int Y, int Height, int Width);
};
void FormaEstado::Paint(TCanvas *Board, int X, int Y, int Height, int Width)
{
    Board->RoundRect(X, Y, X + Width, Y - Height, 20, 20);
}
void FormaEstado::Drag(TCanvas *Board, int X, int Y, int Height, int Width)
{
    Board->Brush->Style = bsClear;
    Board->RoundRect(X - Width/2, Y - Height/2, X + Width/2, Y + Height/2, 20, 20);
}
#define FormaEstadoH
#endif