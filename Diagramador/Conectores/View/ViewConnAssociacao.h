#include "Conectores\View\ViewConector.h"
#include "Conectores\View\ViewConnAssociativo.h"

#ifndef ViewConnAssociacaoH
#define ViewConnAssociacaoH

class ViewConnAssociacao: public ViewConector
{
    private:
    public:
    ViewConnAssociacao():ViewConector()
    {
    }
    ~ViewConnAssociacao()
    {
    }

    void Paint(TCanvas *Board, TColor cor);
    void PintaPonta(TCanvas *Board, TPoint Origem, TPoint Destino);
    
    void SalvaView(int Ordem, TIniFile *INITIAL);
    void CarregaView(int Ordem, TIniFile *INITIAL);
};

void ViewConnAssociacao::PintaPonta(TCanvas *Board, TPoint Origem, TPoint Destino)
{

}

void ViewConnAssociacao::Paint(TCanvas *Board, TColor cor)
{
    if (!*Visible) return;

    SetaCor(Board, cor, psSolid, psDot);

    PintaReta(Board);
}

void ViewConnAssociacao::SalvaView(int Ordem, TIniFile *INITIAL)
{
    SalvaViewConector(Ordem, INITIAL);
}

void ViewConnAssociacao::CarregaView(int Ordem, TIniFile *INITIAL)
{
    CarregaViewConector(Ordem, INITIAL);
}

#endif
