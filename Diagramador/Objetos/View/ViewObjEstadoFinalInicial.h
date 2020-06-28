#include "Objetos\View\ViewObjeto.h"

#include "Pintor\PartesObjeto\FormaEstadoFinalInicial.h"

#ifndef ViewObjEstadoFinalInicialH

class ViewObjEstadoFinalInicial: public ViewObjeto
{
 private:
    bool *EstadoFinal;
    FormaEstadoFinalInicial *minhaForma;
 public:
    ViewObjEstadoFinalInicial(bool estadoFinal): ViewObjeto()
    {
        EstadoFinal = new bool;
        *DefaultHeight = 20;
        *DefaultWidth = 20;
        *EstadoFinal = estadoFinal;

        minhaForma = new FormaEstadoFinalInicial();
	    minhaForma->SetTipoEstado(*EstadoFinal);
    }
    ~ViewObjEstadoFinalInicial()
    {
    	delete EstadoFinal, minhaForma;
    }
    int DefaultSize_Height()
    {
        return *DefaultHeight;
    }
    int DefaultSize_Width()
    {
        return *DefaultWidth;
    }
    int MinHeight()
    {
        return 20;
    }
    int MinWidth()
    {
        return 20;
    }
    int MaxHeight()
    {
        return 20;
    }
    int MaxWidth()
    {
        return 20;
    }
    void SalvaView(int Ordem, TIniFile *INITIAL);
    void CarregaView(int Ordem, TIniFile *INITIAL);

    void Paint(TCanvas *Board);
    void Drag(TPaintBox *Board, int X, int Y);
};

void ViewObjEstadoFinalInicial::Paint(TCanvas *Board)
{
    if(!*Visible) return;

    // Pinta o Retângulo
    Board->Pen->Color = clBlack;
    Board->Pen->Style = psSolid;
    Board->Brush->Style = bsSolid;

    minhaForma->Paint(Board, *Xpos, *Ypos, *Height, *Width);
    minhaForma->Seleciona(Board, *Xpos, *Ypos, *Height, *Width, *isSelected || *GroupSelected);
}
void ViewObjEstadoFinalInicial::Drag(TPaintBox *Board, int X, int Y)
{
    minhaForma->Drag(Board->Canvas, X, Y, *Height, *Width);
    *Xpos = X - *Width/2;
    *Ypos = Y + *Height/2;
}
void ViewObjEstadoFinalInicial::SalvaView(int Ordem, TIniFile *INITIAL)
{
    SalvaViewObjeto(Ordem, INITIAL);
}
void ViewObjEstadoFinalInicial::CarregaView(int Ordem, TIniFile *INITIAL)
{
    CarregaViewObjeto(Ordem, INITIAL);
}

#define ViewObjEstadoFinalInicialH
#endif