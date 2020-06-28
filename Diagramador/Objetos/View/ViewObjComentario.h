#include "Objetos\View\ViewObjeto.h"

#include "Pintor\PartesObjeto\FormaComentario.h"

#ifndef ViewObjComentarioH
#define ViewObjComentarioH

class ViewObjComentario : public ViewObjeto
{
    FormaComentario *minhaForma;
 public:
    ViewObjComentario(): ViewObjeto()
    {
        *DefaultHeight = 30;
        *DefaultWidth = 60;

        minhaForma = new FormaComentario();
    }
    ~ViewObjComentario()
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
        return 80;
    }
    int MaxWidth()
    {
        return 200;
    }

    void Paint(TCanvas *Board);
    void Drag(TPaintBox *Board, int X, int Y);
	void SalvaView(int Ordem, TIniFile *INITIAL);
	void CarregaView(int Ordem, TIniFile *INITIAL);
};

void ViewObjComentario::Paint(TCanvas *Board)
{
    if(!*Visible) return;

    // Pinta o Comentario
    Board->Pen->Color = *LineColor;
    Board->Pen->Style = psSolid;
    Board->Brush->Color = *FillColor;
    Board->Brush->Style = bsSolid;
    Board->Font = TextFont;

    minhaForma->Paint(Board, *Xpos, *Ypos, *Height, *Width);
    minhaForma->PaintTextSingleLine(Board, GetCorpo()->GetName(), *Xpos, *Ypos, *Height, *Width);
    minhaForma->Seleciona(Board, *Xpos, *Ypos, *Height, *Width, *isSelected || *GroupSelected);
}
void ViewObjComentario::Drag(TPaintBox *Board, int X, int Y)
{
    minhaForma->Drag(Board->Canvas, X, Y, *Height, *Width);
    *Xpos = X - *Width/2;
    *Ypos = Y + *Height/2;
}
void ViewObjComentario::SalvaView(int Ordem, TIniFile *INITIAL)
{
    SalvaViewObjeto(Ordem, INITIAL);
}

void ViewObjComentario::CarregaView(int Ordem, TIniFile *INITIAL)
{
    CarregaViewObjeto(Ordem, INITIAL);
}

#endif