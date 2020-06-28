#include "Objetos\Objeto.h"

#include "Pintor\PartesObjeto\FormaEstado.h"

#ifndef ViewObjEstadoH
#define ViewObjEstadoH

class ViewObjEstado: public ViewObjeto
{
    FormaEstado *minhaForma;

 public:
    ViewObjEstado(): ViewObjeto()
    {
        *DefaultHeight = 30;
        *DefaultWidth = 60;

        minhaForma = new FormaEstado();
    }
    ~ViewObjEstado()
    {
        delete minhaForma;
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
        return 40;
    }
    int MinWidth()
    {
        return 40;
    }
    int MaxHeight()
    {
        return 100;
    }
    int MaxWidth()
    {
        return 200;
    }

    void SalvaView(int Ordem, TIniFile *INITIAL);
    void CarregaView(int Ordem, TIniFile *INITIAL);

    void Paint(TCanvas *Board);
    void Drag(TPaintBox *Board, int X, int Y);
};

void ViewObjEstado::Paint(TCanvas *Board)
{
    if(!*Visible) return;

    // Pinta o Estado
    Board->Pen->Color = *LineColor;
    Board->Pen->Style = psSolid;
    Board->Brush->Color = *FillColor;
    Board->Brush->Style = bsSolid;
    Board->Font = TextFont;

    minhaForma->Paint(Board, *Xpos, *Ypos, *Height, *Width);
    minhaForma->PaintTextSingleLine(Board, GetCorpo()->GetName(), *Xpos, *Ypos, *Height, *Width);
    minhaForma->Seleciona(Board, *Xpos, *Ypos, *Height, *Width, *isSelected || *GroupSelected);
}
void ViewObjEstado::Drag(TPaintBox *Board, int X, int Y)
{
    minhaForma->Drag(Board->Canvas, X, Y, *Height, *Width);
    *Xpos = X - *Width/2;
    *Ypos = Y + *Height/2;
}
void ViewObjEstado::SalvaView(int Ordem, TIniFile *INITIAL)
{
    SalvaViewObjeto(Ordem, INITIAL);
}
void ViewObjEstado::CarregaView(int Ordem, TIniFile *INITIAL)
{
    CarregaViewObjeto(Ordem, INITIAL);
}

#endif