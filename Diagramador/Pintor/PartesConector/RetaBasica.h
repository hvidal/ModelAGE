#include "Pintor\ParteConector.h"

#ifndef RetaBasicaH

class RetaBasica: public ParteConector
{
	public:
        RetaBasica(): ParteConector()
        {
        }
        ~RetaBasica()
        {
        }
        void Paint(TCanvas *Board, TPoint Origem, TPoint Destino);
};

void RetaBasica::Paint(TCanvas *Board, TPoint Origem, TPoint Destino)
{
    Board->MoveTo(Origem.x,Origem.y);
    Board->LineTo(Destino.x,Destino.y);
}

#define RetaBasicaH
#endif