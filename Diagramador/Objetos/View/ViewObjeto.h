#include "FuncoesBasicas.h"

#include "Objetos\Objeto.h"

#ifndef ViewObjetoH
#define ViewObjetoH

class ViewObjeto
{
  private:
    Objeto *Corpo;

  protected:
    int *DefaultHeight, *DefaultWidth;

  public:
/*
*        *Xpos    *Width
*           |<------->|
*           v
*           +---------+  -
*           |         |  | *Height
*           |         |  |
*   *Ypos-> +---------+  -
*/
    int *Xpos;
    int *Ypos;
    int *Height, *Width;
    bool *GroupSelected;

    TColor *FillColor, *LineColor;
    TFont  *TextFont;

    virtual int DefaultSize_Height()=0;
    virtual int DefaultSize_Width()=0;
    virtual int MinHeight()=0;
    virtual int MinWidth()=0;
    virtual int MaxHeight()=0;
    virtual int MaxWidth()=0;

    bool *Visible;

    bool *isSelected;

    ViewObjeto(int _X, int _Y, int _Height, int _Width);
    ViewObjeto()
    {
        Aloca();

        *FillColor = (TColor)RGB(239, 239, 239);
        *LineColor = clBlue;

        TextFont->Name = "Arial";
        TextFont->Color = clNavy;
        TextFont->Size = 8;
    }
    ~ViewObjeto()
    {
        delete Xpos, Ypos, Height, Width, isSelected;
        delete Visible, GroupSelected;
        delete FillColor, LineColor;
        delete DefaultHeight, DefaultWidth;
    }

    Objeto* GetCorpo();
    void SetCorpo(Objeto *corpo);

    void Inicializa(int _X, int _Y);
    void Aloca();
    void AjustaNome(TPaintBox *Board);

    void PaintText(TCanvas *Board);
    void PaintTextCustom(int Altura, TCanvas *Board);

    void Restaura(int _X, int _Y, int _Height, int _Width, AnsiString _Name);

    bool isHere(int X, int Y);
    int isResize(int X, int Y);

    void SetFillColor(TColor fillColor);
    void SetLineColor(TColor lineColor);
    void SetFont(TFont *textFont);
    TColor GetLineColor();
    TColor GetFillColor();
    TFont* GetFont();

    void Seleciona(TCanvas *Board);

    void Agrupa();
    virtual void Paint(TCanvas *Board)=0;
    virtual void Drag(TPaintBox *Board, int X, int Y)=0;

    void SalvaViewObjeto(int Ordem, TIniFile *INITIAL);
    virtual void SalvaView(int Ordem, TIniFile *INITIAL)=0;

    void CarregaViewObjeto(int Ordem, TIniFile *INITIAL);
    virtual void CarregaView(int Ordem, TIniFile *INITIAL)=0;

    void Selected();
};

Objeto* ViewObjeto::GetCorpo()
{
    return Corpo;
}
void ViewObjeto::SetCorpo(Objeto *corpo)
{
    Corpo = corpo;
}
void ViewObjeto::Aloca()
{
    Xpos = new int;
    Ypos = new int;
    Height = new int;
    Width = new int;
    isSelected = new bool;
    Visible = new bool;
    GroupSelected = new bool;

    DefaultHeight = new int;
    DefaultWidth = new int;

    FillColor = new TColor;
    LineColor = new TColor;
    TextFont = new TFont;
}
void ViewObjeto::Agrupa()
{
	*GroupSelected = true;
    *isSelected = false;
}
void ViewObjeto::Inicializa(int _X, int _Y)
{
    *Xpos = _X;
    *Ypos = _Y + DefaultSize_Height();
    *Height = DefaultSize_Height();
    *Width = DefaultSize_Width();
    *isSelected = false;
    *GroupSelected = false;
    *Visible = true;
}
void ViewObjeto::Restaura(int _X, int _Y, int _Height, int _Width, AnsiString _Name)
{
    *Xpos = _X;
    *Ypos = _Y;
    *Height = _Height;
    *Width = _Width;
    *isSelected = false;
    *GroupSelected = false;
    *Visible = true;
}
ViewObjeto::ViewObjeto(int _X, int _Y, int _Height, int _Width)
{
    Aloca();
    Inicializa(_X, _Y);
}
void ViewObjeto::SetFillColor(TColor fillColor)
{
	*FillColor = fillColor;
}
void ViewObjeto::SetLineColor(TColor lineColor)
{
	*LineColor = lineColor;
}
void ViewObjeto::SetFont(TFont *textFont)
{
	TextFont->Name = textFont->Name;
	TextFont->Size = textFont->Size;
	TextFont->Color = textFont->Color;
}
TColor ViewObjeto::GetLineColor()
{
	return *LineColor;
}
TColor ViewObjeto::GetFillColor()
{
	return *FillColor;
}
TFont* ViewObjeto::GetFont()
{
	return TextFont;            
}
bool ViewObjeto::isHere(int X, int Y)
{
    if((X>=(*Xpos - 2) && X<=(*Xpos + *Width + 3)) && (Y>=(*Ypos - *Height - 2) && Y<=(*Ypos + 3)))
        return true;
    return false;
}
void ViewObjeto::Selected()
{
    *isSelected = true;
    *GroupSelected = false;
}

void ViewObjeto::AjustaNome(TPaintBox *Board)
{
	// Ajusta o tamanho do objeto
    // de acordo com o texto em seu interior...
	int MaiorHeight, MaiorWidth=0;

    Board->Canvas->Font = TextFont;

   	MaiorWidth = Board->Canvas->TextWidth(GetCorpo()->GetName());
    MaiorHeight = Board->Canvas->TextHeight(GetCorpo()->GetName());

    if(MaiorWidth > *Width)
    {
         if(MaiorWidth < MaxWidth())
         {
              if((MaiorWidth + 4) < MaxWidth())
                  *Width = MaiorWidth + 4;
              else
                  *Width = MaiorWidth;
         }
         else
         {
              *Width = MaxWidth();
         }
    }
    if(MaiorHeight > *Height)
    {
         if(MaiorHeight < MaxHeight())
         {
              if((MaiorHeight + 4) < MaxHeight())
                  *Height = MaiorHeight + 4;
              else
                  *Height = MaiorHeight;
         }
         else
         {
              *Height = MaxHeight();
         }
    }

}
void ViewObjeto::Seleciona(TCanvas *Board)
{
	bool Pinta = false;

    if(*isSelected)
    {
		Board->Pen->Color = clBlack;
        Board->Brush->Color = clBlack;
        Pinta = true;
    }
    else if(*GroupSelected)
    {
		Board->Pen->Color = clBlack;
        Board->Brush->Color = clBlack;
        Pinta = true;
    }

    if(Pinta)
    {
        Board->Pen->Style = psSolid;
        Board->Brush->Style = bsSolid;

        Board->Rectangle(*Xpos - 2, *Ypos - 2 , *Xpos + 3, *Ypos + 3);
        Board->Rectangle(*Xpos + *Width/2 - 2, *Ypos - 2 , *Xpos + *Width/2 + 3, *Ypos + 3);
        Board->Rectangle(*Xpos + *Width - 2, *Ypos - 2 , *Xpos + *Width + 3, *Ypos + 3);

        Board->Rectangle(*Xpos + *Width - 2, *Ypos - *Height/2 - 2 , *Xpos + *Width + 3, *Ypos - *Height/2 + 3);

        Board->Rectangle(*Xpos - 2, *Ypos - *Height - 2 , *Xpos + 3, *Ypos - *Height + 3);
        Board->Rectangle(*Xpos + *Width/2 - 2, *Ypos - *Height - 2 , *Xpos + *Width/2 + 3, *Ypos - *Height + 3);
        Board->Rectangle(*Xpos + *Width - 2, *Ypos - *Height - 2 , *Xpos + *Width + 3, *Ypos - *Height + 3);

        Board->Rectangle(*Xpos - 2, *Ypos - *Height/2 - 2 , *Xpos + 3, *Ypos - *Height/2 + 3);
    }
}
int ViewObjeto::isResize(int X, int Y)
{
/*
                         7--6--5
                         |     |
                         8     4
                         |     |
                         1--2--3
*/
    if((X>=(*Xpos - 2) && X<=(*Xpos + 3)) && (Y>=(*Ypos - 2) && Y<=(*Ypos + 3)))
        return 1;
    else if(X>=(*Xpos + *Width/2 - 2) && X<=(*Xpos + *Width/2 + 3) && (Y>=(*Ypos - 2) && Y<=(*Ypos + 3)))
        return 2;
    else if(X>=(*Xpos + *Width - 2) && X<=(*Xpos + *Width + 3) && (Y>=(*Ypos - 2) && Y<=(*Ypos + 3)))
        return 3;
    else if((X>=(*Xpos + *Width - 2) && X<=(*Xpos + *Width + 3)) && (Y>=(*Ypos - *Height/2 - 2) && Y<=(*Ypos - *Height/2 + 3)))
        return 4;
    else if(X>=(*Xpos + *Width - 2) && X<=(*Xpos + *Width + 3) && (Y>=(*Ypos - *Height - 2) && Y<=(*Ypos - *Height + 3)))
        return 5;
    else if(X>=(*Xpos + *Width/2 - 2) && X<=(*Xpos + *Width/2 + 3) && (Y>=(*Ypos - *Height - 2) && Y<=(*Ypos - *Height + 3)))
        return 6;
    else if((X>=(*Xpos - 2) && X<=(*Xpos + 3)) && (Y>=(*Ypos - *Height - 2) && Y<=(*Ypos - *Height + 3)))
        return 7;
    else if((X>=(*Xpos - 2) && X<=(*Xpos + 3)) && (Y>=(*Ypos - *Height/2 - 2) && Y<=(*Ypos - *Height/2 + 3)))
        return 8;
    else
        return 0;
}

void ViewObjeto::SalvaViewObjeto(int Ordem, TIniFile *INITIAL)
{
}
void ViewObjeto::CarregaViewObjeto(int Ordem, TIniFile *INITIAL)
{
}

#endif
