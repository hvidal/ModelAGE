#include "Conectores\View\ViewConector.h"

#include "Pintor\PartesConector\PontaFlecha.h"

#ifndef ViewConnDependenciaH

class ViewConnDependencia: public ViewConector
{
    private:
        PontaFlecha *pontaFlecha;   
        bool *dash;

	public:
        ViewConnDependencia(bool dashedLine):ViewConector()
        {
            pontaFlecha = new PontaFlecha();

            dash = new bool;
            *dash = dashedLine;
        }
        ~ViewConnDependencia()
        {
            delete dash, pontaFlecha;
        }
        void Paint(TCanvas *Board, TColor cor);
        void PintaPonta(TCanvas *Board, TPoint Origem, TPoint Destino);

        void SalvaView(int Ordem, TIniFile *INITIAL);
        void CarregaView(int Ordem, TIniFile *INITIAL);
};

void ViewConnDependencia::PintaPonta(TCanvas *Board, TPoint Origem, TPoint Destino)
{
    pontaFlecha->SetSelection(*isSelected);
    pontaFlecha->SetDragging(*isDragging);
    pontaFlecha->Paint(Board, Origem, Destino);
}
void ViewConnDependencia::Paint(TCanvas *Board, TColor cor)
{
    if(!*Visible) return;

    if(*dash)
    {
        SetaCor(Board, cor, psDash, psDot);
        Board->Brush->Style = bsClear;
    }
    else
        SetaCor(Board, cor, psSolid, psDot);

    PintaReta(Board);
}

void ViewConnDependencia::SalvaView(int Ordem, TIniFile *INITIAL)
{
    SalvaViewConector(Ordem, INITIAL);
}

void ViewConnDependencia::CarregaView(int Ordem, TIniFile *INITIAL)
{
    CarregaViewConector(Ordem, INITIAL);
}
#define ViewConnDependenciaH
#endif