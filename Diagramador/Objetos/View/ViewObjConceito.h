#include "Objetos\View\ViewObjeto.h"

#include "Pintor\PartesObjeto\FormaConceito.h"

#ifndef ViewObjConceitoH
#define ViewObjConceitoH

class ViewObjConceito: public ViewObjeto
{
    FormaConceito *minhaForma;

 public:
    ViewObjConceito(): ViewObjeto()
    {
        *DefaultHeight = 30;
        *DefaultWidth = 60;
        minhaForma = new FormaConceito();
    }
    ~ViewObjConceito()
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
        return 25;
    }
    int MinWidth()
    {
        return 30;
    }
    int MaxHeight()
    {
        return 60;
    }
    int MaxWidth()
    {
        return 120;
    }

    void SalvaView(int Ordem, TIniFile *INITIAL);
    void CarregaView(int Ordem, TIniFile *INITIAL);

    void Paint(TCanvas *Board);
    void Drag(TPaintBox *Board, int X, int Y);
};

void ViewObjConceito::Paint(TCanvas *Board)
{
    if(!*Visible) return;

    // Pinta o Retângulo
    Board->Pen->Color = *LineColor;
    Board->Pen->Style = psSolid;
    Board->Brush->Color = *FillColor;
    Board->Brush->Style = bsSolid;
    Board->Font = TextFont;

    minhaForma->Paint(Board, *Xpos, *Ypos, *Height, *Width);
    minhaForma->PaintTextSingleLine(Board, GetCorpo()->GetName(), *Xpos, *Ypos, *Height, *Width);
    minhaForma->Seleciona(Board, *Xpos, *Ypos, *Height, *Width, *isSelected || *GroupSelected);
}
void ViewObjConceito::Drag(TPaintBox *Board, int X, int Y)
{
    minhaForma->Drag(Board->Canvas, X, Y, *Height, *Width);
    *Xpos = X - *Width/2;
    *Ypos = Y + *Height/2;
}
void ViewObjConceito::SalvaView(int Ordem, TIniFile *INITIAL)
{
    SalvaViewObjeto(Ordem, INITIAL);
}
void ViewObjConceito::CarregaView(int Ordem, TIniFile *INITIAL)
{
    CarregaViewObjeto(Ordem, INITIAL);
}
#endif
