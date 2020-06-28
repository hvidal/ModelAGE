#include "Conectores\View\ViewConector.h"

#include "Pintor\PartesConector\PontaTriangular.h"

#ifndef ViewConnHerancaH

class ViewConnHeranca: public ViewConector
{
    private:
    PontaTriangular *pontaTriangular;

    public:
    ViewConnHeranca(): ViewConector()
    {
        pontaTriangular = new PontaTriangular();
    }
    ~ViewConnHeranca()
    {
        delete pontaTriangular;
    }
    void Paint(TCanvas *Board, TColor cor);
    void PintaPonta(TCanvas *Board, TPoint Origem, TPoint Destino);
        
    void SalvaView(int Ordem, TIniFile *INITIAL);
    void CarregaView(int Ordem, TIniFile *INITIAL);
};

void ViewConnHeranca::PintaPonta(TCanvas *Board, TPoint Origem, TPoint Destino)
{
    pontaTriangular->SetSelection(*isSelected);
    pontaTriangular->SetDragging(*isDragging);
    pontaTriangular->Paint(Board, Origem, Destino);
}

void ViewConnHeranca::Paint(TCanvas *Board, TColor cor)
{
    if(!*Visible) return;

    SetaCor(Board, cor, psSolid, psDot);

    PintaReta(Board);
}

void ViewConnHeranca::SalvaView(int Ordem, TIniFile *INITIAL)
{
    SalvaViewConector(Ordem, INITIAL);
}

void ViewConnHeranca::CarregaView(int Ordem, TIniFile *INITIAL)
{
    CarregaViewConector(Ordem, INITIAL);
}
#define ViewConnHerancaH
#endif