#include "Objetos\View\ViewObjeto.h"

#include "Pintor\PartesObjeto\FormaAtor.h"

#ifndef ViewObjAtorH
#define ViewObjAtorH

class ViewObjAtor: public ViewObjeto
{
    FormaAtor *minhaForma;
 public:
    ViewObjAtor(): ViewObjeto()
    {
        *DefaultHeight = 60;
        *DefaultWidth = 40;

        minhaForma = new FormaAtor();
    }
    ~ViewObjAtor()
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

    void Paint(TCanvas *Board);
    void Drag(TPaintBox *Board, int X, int Y);
	void SalvaView(int Ordem, TIniFile *INITIAL);
	void CarregaView(int Ordem, TIniFile *INITIAL);
};

void ViewObjAtor::Paint(TCanvas *Board)
{
    if(!*Visible) return;

    Board->Font = TextFont;

    // Limpo o Fundo
	minhaForma->LimpaFundo(Board, *Xpos, *Ypos, *Height, *Width);

    Board->Pen->Color = *LineColor;

    int Altura = (*Ypos - *Height + 45);

    minhaForma->Paint(Board, *Xpos, *Ypos, *Height, *Width);
    minhaForma->PaintTextSingleLineCustom(Altura, Board, GetCorpo()->GetName(), *Xpos, *Ypos, *Height, *Width);
    minhaForma->Seleciona(Board, *Xpos, *Ypos, *Height, *Width, *isSelected || *GroupSelected);
}
void ViewObjAtor::Drag(TPaintBox *Board, int X, int Y)
{
    minhaForma->Drag(Board->Canvas, X, Y, *Height, *Width);
    *Xpos = X - *Width/2;
    *Ypos = Y + *Height/2;
}
void ViewObjAtor::SalvaView(int Ordem, TIniFile *INITIAL)
{
    SalvaViewObjeto(Ordem, INITIAL);
}
void ViewObjAtor::CarregaView(int Ordem, TIniFile *INITIAL)
{
    CarregaViewObjeto(Ordem, INITIAL);
}
#endif