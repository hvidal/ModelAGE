#include "Conectores\View\ViewConector.h"

#include "Pintor\PartesConector\PontaDiamante.h"

#ifndef ViewConnAgregacaoH

class ViewConnAgregacao: public ViewConector
{
	private:
        PontaDiamante *pontaDiamante;

    public:
        ViewConnAgregacao(bool _Pinta): ViewConector()
        {
            pontaDiamante = new PontaDiamante(_Pinta);
        }
        ~ViewConnAgregacao()
        {
            delete pontaDiamante;
        }
        void Paint(TCanvas *Board, TColor cor);
        void PintaPonta(TCanvas *Board, TPoint Origem, TPoint Destino);

        void SalvaView(int Ordem, TIniFile *INITIAL);
        void CarregaView(int Ordem, TIniFile *INITIAL);
};

void ViewConnAgregacao::PintaPonta(TCanvas *Board, TPoint Origem, TPoint Destino)
{
    pontaDiamante->SetSelection(*isSelected);
    pontaDiamante->SetDragging(*isDragging);
    pontaDiamante->Paint(Board, Origem, Destino);
}

void ViewConnAgregacao::Paint(TCanvas *Board, TColor cor)
{
    if(!*Visible) return;

    SetaCor(Board, cor, psSolid, psDot);

    PintaReta(Board);
}

void ViewConnAgregacao::SalvaView(int Ordem, TIniFile *INITIAL)
{
    SalvaViewConector(Ordem, INITIAL);
}

void ViewConnAgregacao::CarregaView(int Ordem, TIniFile *INITIAL)
{
    CarregaViewConector(Ordem, INITIAL);
}
#define ViewConnAgregacaoH
#endif