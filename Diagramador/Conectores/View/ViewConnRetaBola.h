#include "Conectores\View\ViewConector.h"

#include "Pintor\PartesConector\PontaCircular.h"

#ifndef ViewConnRetaBolaH

class ViewConnRetaBola: public ViewConector
{
    private:
        PontaCircular *pontaCircular;

	public:
        ViewConnRetaBola():ViewConector()
        {
            pontaCircular = new PontaCircular();
        }
        ~ViewConnRetaBola()
        {
            delete pontaCircular;
        }

    	void Paint(TCanvas *Board, TColor cor);
        void PintaPonta(TCanvas *Board, TPoint Origem, TPoint Destino);

        void SalvaView(int Ordem, TIniFile *INITIAL);
        void CarregaView(int Ordem, TIniFile *INITIAL);
};

void ViewConnRetaBola::PintaPonta(TCanvas *Board, TPoint Origem, TPoint Destino)
{
    pontaCircular->SetSelection(*isSelected);
    pontaCircular->SetDragging(*isDragging);
    pontaCircular->Paint(Board, Origem, Destino);
}

void ViewConnRetaBola::Paint(TCanvas *Board, TColor cor)
{
    if(!*Visible) return;

    SetaCor(Board, cor, psSolid, psDot);

    PintaReta(Board);
}

void ViewConnRetaBola::SalvaView(int Ordem, TIniFile *INITIAL)
{
    SalvaViewConector(Ordem, INITIAL);
}
void ViewConnRetaBola::CarregaView(int Ordem, TIniFile *INITIAL)
{
    CarregaViewConector(Ordem, INITIAL);
}

#define ViewConnRetaBolaH
#endif