#include "Pintor\ParteObjeto.h"

#ifndef FormaComentarioH

class FormaComentario: public ParteObjeto
{
        int *TamOrelha;
        TPoint pt[6];
	public:
        FormaComentario(): ParteObjeto()
        {
	        TamOrelha = new int;
	        *TamOrelha = 5;
        }
        ~FormaComentario()
        {
        	delete TamOrelha;
        }
	    void Paint(TCanvas *Board, int X, int Y, int Height, int Width);
	    void Drag(TCanvas *Board, int X, int Y, int Height, int Width);
};
void FormaComentario::Paint(TCanvas *Board, int X, int Y, int Height, int Width)
{
    pt[0].x = X;
    pt[0].y = Y;
    pt[1].x = X;
    pt[1].y = Y - Height;
    pt[2].x = X + Width - *TamOrelha;
    pt[2].y = Y - Height;
    pt[3].x = X + Width;
    pt[3].y = Y - Height + *TamOrelha;
    pt[4].x = X + Width;
    pt[4].y = Y;
    pt[5].x = X;
    pt[5].y = Y;

    Board->Polygon(pt, 5);

    Board->MoveTo(X + Width - *TamOrelha, Y - Height);
    Board->LineTo(X + Width - *TamOrelha, Y - Height + *TamOrelha);
    Board->LineTo(X + Width, Y - Height + *TamOrelha);
}
void FormaComentario::Drag(TCanvas *Board, int X, int Y, int Height, int Width)
{
    Board->Brush->Style = bsClear;

    Board->MoveTo(X - Width/2, Y + Height/2);
    Board->LineTo(X - Width/2, Y - Height/2);
    Board->LineTo(X + Width/2 - *TamOrelha, Y - Height/2);
    Board->LineTo(X + Width/2, Y - Height/2 + *TamOrelha);
    Board->LineTo(X + Width/2, Y + Height/2);
    Board->LineTo(X - Width/2, Y + Height/2);

    Board->MoveTo(X + Width/2 - *TamOrelha, Y - Height/2 + 1);
    Board->LineTo(X + Width/2 - *TamOrelha, Y - Height/2 + *TamOrelha);
    Board->LineTo(X + Width/2, Y - Height/2 + *TamOrelha);
}
#define FormaComentarioH
#endif