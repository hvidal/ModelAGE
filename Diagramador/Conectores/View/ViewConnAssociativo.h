#include "Conectores\View\ViewConector.h"

#ifndef ViewConnAssociativoH

class ViewConnAssociativo: public ViewConector
{
    private:
	public:
        ViewConnAssociativo():ViewConector()
        {
        }

    	void Paint(TCanvas *Board, TColor cor);
        void PintaPonta(TCanvas *Board, TPoint Origem, TPoint Destino);
        
    	void SalvaView(int Ordem, TIniFile *INITIAL);
        void CarregaView(int Ordem, TIniFile *INITIAL);
};

void ViewConnAssociativo::PintaPonta(TCanvas *Board, TPoint Origem, TPoint Destino)
{
}

void ViewConnAssociativo::Paint(TCanvas *Board, TColor cor)
{
    if(!*Visible) return;

    SetaCor(Board, cor, psDash, psDot);

    if(*isDragging != true)
    	Board->Brush->Color = clWhite;

    PintaReta(Board);
}
void ViewConnAssociativo::SalvaView(int Ordem, TIniFile *INITIAL)
{
    SalvaViewConector(Ordem, INITIAL);
}

void ViewConnAssociativo::CarregaView(int Ordem, TIniFile *INITIAL)
{
    CarregaViewConector(Ordem, INITIAL);
}

#define ViewConnAssociativoH
#endif