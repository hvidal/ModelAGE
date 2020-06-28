#include "Pintor\ParteObjeto.h"

#ifndef FormaEstadoFinalInicialH

class FormaEstadoFinalInicial: public ParteObjeto
{
	private:
    	bool *tipoEstado;
	public:
        FormaEstadoFinalInicial(): ParteObjeto()
        {
        	tipoEstado = new bool;
        }
        ~FormaEstadoFinalInicial()
        {
        	delete tipoEstado;
        }
	    void Paint(TCanvas *Board, int X, int Y, int Height, int Width);
	    void Drag(TCanvas *Board, int X, int Y, int Height, int Width);
        void SetTipoEstado(bool esseTipo)
        {
            // TRUE ==> Estado FINAL
            // FALSE ==> Estado INICIAL
			*tipoEstado = esseTipo;
        }
};
void FormaEstadoFinalInicial::Paint(TCanvas *Board, int X, int Y, int Height, int Width)
{
    if(*tipoEstado) // Estado Final
	    Board->Brush->Color = clWhite;
    else 			// Estado Inicial
	    Board->Brush->Color = clBlack;

    Board->Ellipse(X, Y, X + Width, Y - Height);

    Board->Brush->Color = clBlack;
    Board->Ellipse(X + 5, Y - 5, X + Width - 5, Y - Height + 5);
}
void FormaEstadoFinalInicial::Drag(TCanvas *Board, int X, int Y, int Height, int Width)
{
    Board->Brush->Style = bsClear;
    Board->Ellipse(X - Width/2, Y + Height/2, X + Width/2, Y - Height/2);
}
#define FormaEstadoFinalInicialH
#endif