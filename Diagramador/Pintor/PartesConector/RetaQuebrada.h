#include "Pintor\ParteConector.h"

#ifndef RetaQuebradaH

class RetaQuebrada: public ParteConector
{
	public:
        RetaQuebrada(): ParteConector()
        {
        }
        ~RetaQuebrada()
        {
        }
	void Paint(TCanvas *Board, TPoint Origem, TPoint Destino);
};

void RetaQuebrada::Paint(TCanvas *Board, TPoint Origem, TPoint Destino)
{
    float Hdiff, Meio, Menor;

    Hdiff = Origem.x - Destino.x;
    if(Hdiff < 0) Hdiff = -Hdiff;

    if(Hdiff < (DISTANCIA_LIMITE))
    {

// Linha do meio é horizontal
//        |    |
//        X X  X
//        +----+
//        |Obj |
//        +----+
//        X X  X
//        |    |

        Meio = (Origem.y-Destino.y)/2;
        if(Meio < 0) Meio = -Meio;

        Menor = (Origem.y < Destino.y)? Origem.y : Destino.y;

        Board->MoveTo(Origem.x,Origem.y);
        Board->LineTo(Origem.x, Menor + Meio);
        Board->LineTo(Destino.x, Menor + Meio);
        Board->LineTo(Destino.x,Destino.y);
    }
    else
    {

// Linha do meio é vertical
//        |    |
//      X |    | X
//   -----+----+-----
//        |Obj |
//   -----+----+-----
//      X |    | X
//        |    |

        Meio = (Origem.x-Destino.x)/2;
        if(Meio < 0) Meio = -Meio;

        Menor = (Origem.x < Destino.x)? Origem.x : Destino.x;

        Board->MoveTo(Origem.x,Origem.y);
        Board->LineTo(Menor + Meio ,Origem.y);
        Board->LineTo(Menor + Meio, Destino.y);
        Board->LineTo(Destino.x,Destino.y);
    }
}

#define RetaQuebradaH
#endif