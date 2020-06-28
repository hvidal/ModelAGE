#include <math.h>
#include<stdio.h>

#include "Conectores\Connector.h"

#include "Conectores\View\PontoQuebra.h"

#include "Objetos\View\ViewObjeto.h"
#include "Pintor\PartesConector\RetaBasica.h"

#include "Pintor\ParteConector.h"

#ifndef ViewConectorH
#define ViewConectorH

class ViewConector
{
  private:
    Connector *Corpo;

    // View do conector que se liga a mim
    ViewConector *ViewPointingAtMe;

    // View do conector que eu me ligo
    ViewConector *ViewEnd;

    // Lista dos pontos que constituem esta reta
    TList *pontos;

    // Variável que guarda o trecho do conector que mais se
    // aproximou do último clique em busca de conectores.
    int *TrechoSelecionado;

  protected:
    bool *isSelected, *isDragging;

    // Connector View - Reta Principal
    RetaBasica *retaBasica;

  public:
    ViewObjeto *ViewA;
    ViewObjeto *ViewB;

    int *AXOffset, *AYOffset, *BXOffset, *BYOffset;
    bool *Visible;
    TColor *LineColor;

    ViewConector()
    {
        retaBasica = new RetaBasica();

        isSelected = new bool;
        isDragging = new bool;
        Visible = new bool;
        LineColor = new TColor;

        AXOffset = new int;
        AYOffset = new int;
        BXOffset = new int;
        BYOffset = new int;

        pontos = new TList();

        TrechoSelecionado = new int;

        *isDragging = false;
        *isSelected = false;
        *Visible = true;

        *AXOffset = 0;
        *AYOffset = 0;
        *BXOffset = 0;
        *BYOffset = 0;

        *LineColor = clMaroon;

        *TrechoSelecionado = -2;

        ViewPointingAtMe = NULL;
        ViewEnd = NULL;
    }
    ~ViewConector()
    {
        if (ViewPointingAtMe != NULL)
            ViewPointingAtMe->SetConectorViewEndLine(NULL);

        if (ViewEnd != NULL)
            ViewEnd->SetViewPointingAtMe(NULL);

        delete isSelected, isDragging, Visible, LineColor;
        delete AXOffset, AYOffset, BXOffset, BYOffset;
        delete retaBasica;

        pontos->Clear();
        delete pontos, TrechoSelecionado;
    }

    void ConnectViews(ViewObjeto *ViewAX, ViewObjeto *ViewBX)
    {
        ViewA = ViewAX;
        ViewB = ViewBX;
    }
    // Getters & Setters
    void SetCorpo(Connector *corpo);
    Connector* GetCorpo();

    void SetLineColor(TColor lineColor);
    TColor GetLineColor();

    bool GetSelection();
    void SetSelection(bool selecao);

    bool GetDragging();
    void SetDragging(bool dragging);

    TPoint GetOrigem();
    TPoint GetDestino();
    TPoint GetFronteiraOrigem();
    TPoint GetFronteiraDestino();

    // Para conectores que apontam para outros conectores
    TPoint GetPontoDestino();
    TPoint GetPontoOrigem();

    TList* GetPontos()
    {
        return pontos;
    }
    void ClonePontos(TList *pontos)
    {
        // Clono a lista de pontos, sequestrando os pontos que existem
        // dentro da lista passada como parâmentro.
        PontoQuebra *ponto;
        for (int i=0; i<pontos->Count; i++)
        {
            ponto = (PontoQuebra*)pontos->Items[i];
            ponto->SetIdDono(GetCorpo()->GetId());
            this->pontos->Add(ponto);
        }
    }

    PontoQuebra GetPonto(int i);
    PontoQuebra* GetPontoAt(int X, int Y);
    int GetTrechoSelecionado();

    void VerificaPontoSobreReta(TPoint *ponto);

    void SetViewPointingAtMe(ViewConector *pointing)
    {
        ViewPointingAtMe = pointing;
    }
    ViewConector* GetViewPointingAtMe()
    {
        return ViewPointingAtMe;
    }
    void SetConectorViewEndLine(ViewConector *endLine);
    ViewConector* GetConectorViewEndLine();

    // Verifica se o ponto (X,Y) está sobre os pontos origem ou destino da reta
    bool IsBasePoint(int X, int Y);
    bool DentroQuadradinho(int X, int Y, TPoint ponto);

    void setOffset(int X, int Y, bool origem);
    void PintaSelecao(TCanvas *Board, bool ligaOutraReta);

    virtual void Paint(TCanvas *Board, TColor cor)=0;
    virtual void PintaPonta(TCanvas *Board, TPoint Origem, TPoint Destino) = 0;

    void PintaReta(TCanvas *Board);

    float DistanciaAoPonto(float x, float y);

    void SetaCor(TCanvas *Board, TColor cor, TPenStyle notdrag, TPenStyle drag);

    // Concretos:
    float DistanceToBreakLine(TPoint Origem, TPoint Destino, float x, float y);
    float DistanceToLine(TPoint Origem, TPoint Destino, float x, float y);

    void SalvaViewConector(int Ordem, TIniFile *INITIAL);
    virtual void SalvaView(int Ordem, TIniFile *INITIAL)=0;

    void CarregaViewConector(int Ordem, TIniFile *INITIAL);
    virtual void CarregaView(int Ordem, TIniFile *INITIAL)=0;

};
void ViewConector::SetCorpo(Connector *corpo)
{
    Corpo = corpo;
}
Connector* ViewConector::GetCorpo()
{
    return Corpo;
}
void ViewConector::SetSelection(bool selecao)
{
    *isSelected = selecao;
}
bool ViewConector::GetSelection()
{
    return *isSelected;
}
bool ViewConector::GetDragging()
{
    return *isDragging;
}
void ViewConector::SetDragging(bool dragging)
{
    *isDragging = dragging;
}
PontoQuebra ViewConector::GetPonto(int i)
{
    PontoQuebra ponto;
    ponto.x = ((PontoQuebra*)GetPontos()->Items[i])->x;
    ponto.y = ((PontoQuebra*)GetPontos()->Items[i])->y;
    return ponto;
}
PontoQuebra* ViewConector::GetPontoAt(int X, int Y)
{                          
    PontoQuebra p;
    // Dentro de cada ponto da linha
    for (int i=0; i<GetPontos()->Count; i++)
    {
        p = GetPonto(i);
        if (DentroQuadradinho(X, Y, p))
            return (PontoQuebra*)GetPontos()->Items[i];
    }
    return NULL;
}
void ViewConector::VerificaPontoSobreReta(TPoint *ponto)
{
    // Função que apaga o "ponto" se este estiver sobre a reta formada pelo
    // ponto anterior e pelo ponto posterior ao mesmo.

    TPoint pontoAnterior, pontoPosterior;
    int Distancia;

    // Primeiro ponto
    if (GetPontos()->IndexOf(ponto) == 0)
        pontoAnterior = GetOrigem();
    else
        pontoAnterior = GetPonto(GetPontos()->IndexOf(ponto)-1);

    // Último ponto
    if (GetPontos()->IndexOf(ponto) == (GetPontos()->Count-1))
        pontoPosterior = GetDestino();
    else
        pontoPosterior = GetPonto(GetPontos()->IndexOf(ponto)+1);

    // Perto da Reta
    if (InsideRect(ponto->x, ponto->y, pontoAnterior.x, pontoAnterior.y, pontoPosterior.x, pontoPosterior.y, 10.0))
    {
        Distancia = DistanceToLine(pontoAnterior, pontoPosterior, ponto->x, ponto->y);

        if (Distancia <= 10.0)
        {
            GetPontos()->Remove(ponto);
            delete ponto;
            ponto = NULL;
        }
    }

    if (ponto != NULL)
    {
        // Se eu soltei o primeiro ponto dentro do objeto origem, então...
        if (ViewA->isHere(ponto->x, ponto->y) &&
            GetPontos()->IndexOf(ponto) == 0)
        {
            GetPontos()->Remove(ponto);
            delete ponto;
        }
        // Se eu soltei o último ponto dentro do objeto destino, então...
        else if (ViewB->isHere(ponto->x, ponto->y) &&
                 GetPontos()->IndexOf(ponto) == GetPontos()->Count-1)
        {
            GetPontos()->Remove(ponto);
            delete ponto;
        }
    }
}
TPoint ViewConector::GetOrigem()
{
    TPoint Origem;
    Origem.x = *ViewA->Xpos + *ViewA->Width/2  - *AXOffset;
    Origem.y = *ViewA->Ypos - *ViewA->Height/2 - *AYOffset;
    return Origem;
}
TPoint ViewConector::GetDestino()
{
    TPoint Destino;
    Destino.x = *ViewB->Xpos + *ViewB->Width/2 - *BXOffset;
    Destino.y = *ViewB->Ypos - *ViewB->Height/2 - *BYOffset;
    return Destino;
}
TPoint ViewConector::GetFronteiraOrigem()
{
    TPoint FronteiraOrigem;

    if (GetPontos()->Count == 0)
        FronteiraOrigem = ParteConector::Fronteira(*ViewA->Xpos, *ViewA->Ypos, *ViewA->Height, *ViewA->Width, *AXOffset, *AYOffset, *ViewB->Xpos, *ViewB->Ypos, *ViewB->Height, *ViewB->Width, *BXOffset, *BYOffset);
    else
    {
        TPoint *ponto;
        ponto = (TPoint*)GetPontos()->Items[0];
        FronteiraOrigem = ParteConector::Fronteira(*ViewA->Xpos, *ViewA->Ypos, *ViewA->Height, *ViewA->Width, *AXOffset, *AYOffset, ponto->x, ponto->y, 0, 0, 0, 0);
    }

    return FronteiraOrigem;
}

TPoint ViewConector::GetFronteiraDestino()
{
    TPoint FronteiraDestino;

    if (GetPontos()->Count == 0)
        FronteiraDestino = ParteConector::Fronteira(*ViewB->Xpos, *ViewB->Ypos, *ViewB->Height, *ViewB->Width, *BXOffset, *BYOffset, *ViewA->Xpos, *ViewA->Ypos, *ViewA->Height, *ViewA->Width, *AXOffset, *AYOffset);
    else
    {
        TPoint *ponto;
        ponto = (TPoint*)GetPontos()->Items[GetPontos()->Count-1];
        FronteiraDestino = ParteConector::Fronteira(*ViewB->Xpos, *ViewB->Ypos, *ViewB->Height, *ViewB->Width, *BXOffset, *BYOffset, ponto->x, ponto->y, 0, 0, 0, 0);
    }

    return FronteiraDestino;
}
void ViewConector::PintaSelecao(TCanvas *Board, bool ligaOutraReta)
{
    if(*isSelected == true)
    {
        TPoint p1, p2;
        Board->Pen->Color = clBlack;
        Board->Pen->Style = psSolid;
        Board->Brush->Color = clBlack;
        Board->Brush->Style = bsSolid;

        p1 = GetOrigem();
        Board->Rectangle(p1.x - 2, p1.y - 2 , p1.x + 3, p1.y + 3);

        TPoint *ponto;
        for (int i=0; i<GetPontos()->Count;i++)
        {
            ponto = (TPoint*)GetPontos()->Items[i];
            Board->Rectangle(ponto->x - 2, ponto->y - 2 , ponto->x + 3, ponto->y + 3);
        }

        if(!ligaOutraReta)
        {
            p2 = GetDestino();
            Board->Rectangle(p2.x - 2, p2.y - 2 , p2.x + 3, p2.y + 3);
        }
    }
}
void ViewConector::PintaReta(TCanvas *Board)
{
    retaBasica->SetSelection(*isSelected);
    retaBasica->SetDragging(*isDragging);

    if (GetPontos()->Count > 0)
    {
        retaBasica->Paint(Board, GetFronteiraOrigem(), GetPonto(0));
        for (int i=1; i < GetPontos()->Count; i++)
        {
            retaBasica->Paint(Board, GetPonto(i-1), GetPonto(i));
        }
        retaBasica->Paint(Board, GetPonto(GetPontos()->Count-1), GetFronteiraDestino());
        PintaPonta(Board, GetPonto(GetPontos()->Count-1), GetFronteiraDestino());
    }
    else
    {
        retaBasica->Paint(Board, GetFronteiraOrigem(), GetFronteiraDestino());
        PintaPonta(Board, GetFronteiraOrigem(), GetFronteiraDestino());
    }
}
bool ViewConector::DentroQuadradinho(int X, int Y, TPoint ponto)
{
    // Função que retorna true se o ponto (X, Y) estiver dentro do quadradinho
    // cujo centro está em (ponto.x, ponto.y).
    if((X >= (ponto.x - 2) && X <= (ponto.x + 3)) && (Y >= (ponto.y - 2) && Y <= (ponto.y + 3)))
        return true;
    return false;
}
int ViewConector::GetTrechoSelecionado()
{
    return *TrechoSelecionado;
}
bool ViewConector::IsBasePoint(int X, int Y)
{
    // Função que retorna true se o ponto (X, Y) estiver sobre algum dos quadradinhos
    // de seleção deste conector.
    TPoint p1, p, p2;

    // Dentro do ponto de Origem
    p1 = GetOrigem();
    if(DentroQuadradinho(X, Y, p1))
        return true;

    // Dentro de cada ponto da linha
    for (int i=0; i<GetPontos()->Count; i++)
    {
        p = GetPonto(i);
        if (DentroQuadradinho(X, Y, p))
            return true;
    }

    // Dentro do ponto de Destino
    if(GetCorpo()->B != NULL)
    {
        p2 = GetDestino();
        if(DentroQuadradinho(X, Y, p2))
            return true;
    }
    return false;
}
void ViewConector::setOffset(int X, int Y, bool origem)
{
    if(origem)
    {
    	*AXOffset = X;
        *AYOffset = Y;
    }
    else
    {
    	*BXOffset = X;
        *BYOffset = Y;
    }
}

void ViewConector::SetLineColor(TColor lineColor)
{
    *LineColor = lineColor;
}
TColor ViewConector::GetLineColor()
{
    return *LineColor;
}
void ViewConector::SetaCor(TCanvas *Board, TColor cor, TPenStyle notdrag, TPenStyle drag)
{
    if (cor != clWhite)
    {
        Board->Pen->Color = *LineColor;
    }
    else
    {
        Board->Pen->Color = cor;
    }

    Board->Brush->Color = cor;

    if(!*isDragging)
    {
        Board->Brush->Style = bsSolid;
        Board->Pen->Style = notdrag;
        if(*isSelected)
            Board->Pen->Color = clRed;
    }
    else
    {
        Board->Brush->Style = bsClear;
        Board->Pen->Style = drag;
    }
}
void ViewConector::SetConectorViewEndLine(ViewConector *endLine)
{
    ViewEnd = endLine;
}
ViewConector* ViewConector::GetConectorViewEndLine()
{
    return ViewEnd;
}
TPoint ViewConector::GetPontoDestino()
{
    TPoint PontoDestino, PontoBaseA1, PontoBaseA2;

    PontoBaseA1 = ParteConector::Fronteira(
      *ViewEnd->ViewA->Xpos,
      *ViewEnd->ViewA->Ypos,
      *ViewEnd->ViewA->Height,
      *ViewEnd->ViewA->Width,
      *ViewEnd->AXOffset,
      *ViewEnd->AYOffset,
      *ViewEnd->ViewB->Xpos,
      *ViewEnd->ViewB->Ypos,
      *ViewEnd->ViewB->Height,
      *ViewEnd->ViewB->Width,
      *ViewEnd->BXOffset,
      *ViewEnd->BYOffset);

    PontoBaseA2 = ParteConector::Fronteira(
      *ViewEnd->ViewB->Xpos,
      *ViewEnd->ViewB->Ypos,
      *ViewEnd->ViewB->Height,
      *ViewEnd->ViewB->Width,
      *ViewEnd->BXOffset,
      *ViewEnd->BYOffset,
      *ViewEnd->ViewA->Xpos,
      *ViewEnd->ViewA->Ypos,
      *ViewEnd->ViewA->Height,
      *ViewEnd->ViewA->Width,
      *ViewEnd->AXOffset,
      *ViewEnd->AYOffset);

    PontoDestino.x = Menor(PontoBaseA1.x, PontoBaseA2.x) + Modulo(PontoBaseA1.x - PontoBaseA2.x)/2;
    PontoDestino.y = Menor(PontoBaseA1.y, PontoBaseA2.y) + Modulo(PontoBaseA1.y - PontoBaseA2.y)/2;

    return PontoDestino;
}
TPoint ViewConector::GetPontoOrigem()
{
    TPoint PontoOrigem, PontoDestino;
    PontoDestino = GetPontoDestino();
    PontoOrigem = ParteConector::Fronteira(*ViewA->Xpos, *ViewA->Ypos, *ViewA->Height, *ViewA->Width, *AXOffset, *AYOffset, PontoDestino.x, PontoDestino.y, 0, 0, 0, 0);

    return PontoOrigem;
}

float ViewConector::DistanciaAoPonto(float x, float y)
{
    if (GetPontos()->Count > 0)
    {
        float Distancia, Atual = 1000;

        if (InsideRect(x, y, GetOrigem().x, GetOrigem().y, GetPonto(0).x, GetPonto(0).y, 4.0))
        {
            Distancia = DistanceToLine(GetOrigem(), GetPonto(0), x, y);
            *TrechoSelecionado = -1;
        }
        else
            Distancia = 1000;

        for (int i=1; i<GetPontos()->Count;i++)
        {
            if (InsideRect(x, y, GetPonto(i-1).x, GetPonto(i-1).y, GetPonto(i).x, GetPonto(i).y, 4.0))
            {
                Atual = DistanceToLine(GetPonto(i-1), GetPonto(i), x, y);
                if (Atual < Distancia)
                {
                    Distancia = Atual;
                    *TrechoSelecionado = i-1;
                }
            }
            else
                continue;
        }

        if (InsideRect(x, y, GetPonto(GetPontos()->Count-1).x, GetPonto(GetPontos()->Count-1).y, GetDestino().x, GetDestino().y, 4.0))
            Atual = DistanceToLine(GetPonto(GetPontos()->Count-1), GetDestino(), x, y);

        if (Atual < Distancia)
        {
            Distancia = Atual;
            *TrechoSelecionado = GetPontos()->Count-1;
        }

        return Distancia;
    }
    else
    {
        *TrechoSelecionado = -1;     
        return DistanceToLine(GetOrigem(), GetDestino(), x, y);
    }
}

float ViewConector::DistanceToLine(TPoint Origem, TPoint Destino, float c, float d)
{
/*
*	Calcula a distância de um ponto (c, d) à reta
*	formada pelos pontos (x1,y1) e (x2,y2).
*	Cálculos: Olhar caderno de C.V.G.A. do
*	prof. Flávio Dickenstein
*/
    float a, b, x, y, qx, qy;

    if(Modulo(Origem.x - Destino.x) == 0) // Reta Vertical
    {
        return Modulo(c - Origem.x);
    }
    if(Modulo(Origem.y - Destino.y) == 0) // Reta Horizontal
    {
        return Modulo(d - Origem.y);
    }
    a = (Origem.y - Destino.y)/(float)(Origem.x - Destino.x);
    b = (float)(Destino.y - a * Destino.x);

    x = (c - a*b + a*d)/(float)(a*a + 1);
    y = (c - x + a*d)/(float)a;

    qx = (float)(x-c)*(x-c);
    qy = (float)(y-d)*(y-d);

    return (float)sqrt(qx+qy);
}

float ViewConector::DistanceToBreakLine(TPoint Origem, TPoint Destino, float x, float y)
{
    float Hdiff, Meio, Menor, distancia = 30;
    float MaiorX, MenorX, MaiorY, MenorY;

    Hdiff = Modulo(Origem.x - Destino.x);

    if(Hdiff < (DISTANCIA_LIMITE))
    {
        // Linha do meio é horizontal
        Meio = (Origem.y-Destino.y)/2.0;
        if(Meio < 0.0) Meio = -Meio;

        Menor = (Origem.y<Destino.y)?Origem.y:Destino.y;

        if(Between(y, Origem.y, Menor + Meio))
            distancia = Modulo(x - Origem.x);

        if(Between(x, Origem.x, Destino.x) && (Modulo(y - Menor - Meio) < distancia))
        {
            distancia = Modulo(y - Menor - Meio);
        }

        if(Between(y, Menor + Meio, Destino.y) && (Modulo(x - Destino.x) < distancia))
        {
            distancia = Modulo(x - Destino.x);
        }
    }
    else
    {
        // Linha do meio é vertical
        Meio = (Origem.x-Destino.x)/2.0;
        if(Meio < 0.0) Meio = -Meio;

        MenorX = (Origem.x<Destino.x)?Origem.x:Destino.x;
        MaiorX = (Origem.x>Destino.x)?Origem.x:Destino.x;
        MenorY = (Origem.x<Destino.x)?Origem.y:Destino.y;
        MaiorY = (Origem.x>Destino.x)?Origem.y:Destino.y;

        if(Between(x, MenorX, MenorX + Meio))
            distancia = Modulo(y - MenorY);

        if(Between(y, Origem.y, Destino.y) && (Modulo(x - MenorX - Meio) < distancia))
        {
            distancia = Modulo(x - MenorX - Meio);
        }

        if(Between(x, MenorX + Meio, MaiorX) && (Modulo(y - MaiorY) < distancia))
        {
            distancia = Modulo(y - MaiorY);
        }
    }
    return distancia;
}

void ViewConector::SalvaViewConector(int Ordem, TIniFile *INITIAL)
{
/*	AnsiString Linha;

    Linha = *Id;

    INITIAL->WriteString("Conector" + AnsiString(Ordem), "chave", Linha);

    Linha = A->GetCorpo()->GetId();
    Linha += " ";
    if(B != 0)
	    Linha += B->GetCorpo()->GetId();
    else
	    Linha += "-1";

    INITIAL->WriteString("Conector" + AnsiString(Ordem), "basico", Linha);

    Linha = *Label;
    INITIAL->WriteString("Conector" + AnsiString(Ordem),"label", Linha);

    // Offsets
    Linha = AnsiString(*AXOffset);
    Linha += " ";
    Linha += AnsiString(*AYOffset);
    Linha += " ";
    Linha += AnsiString(*BXOffset);
    Linha += " ";
    Linha += AnsiString(*BYOffset);
    INITIAL->WriteString("Conector" + AnsiString(Ordem),"offset", Linha);

    INITIAL->WriteInteger("Conector" + AnsiString(Ordem),"maior", *Maior);
    INITIAL->WriteInteger("Conector" + AnsiString(Ordem),"position", *Position);

    INITIAL->WriteInteger("Conector" + AnsiString(Ordem),"Color", *LineColor);

*/
}

void ViewConector::CarregaViewConector(int Ordem, TIniFile *INITIAL)
{
/*
 	// Carrega a label
    *Label = IniStrToStr(INITIAL->ReadString("Conector" + AnsiString(Ordem), "label", ""));
	Linhas = Break(*Label);
    *Maior = INITIAL->ReadInteger("Conector" + AnsiString(Ordem), "maior", 0);
    *Position = INITIAL->ReadInteger("Conector" + AnsiString(Ordem), "position", 1);

	// offsets
    char LinhaArray[100];
    AnsiString Linha = IniStrToStr(INITIAL->ReadString("Conector" + AnsiString(Ordem), "offset", ""));
    strcpy(LinhaArray, Linha.c_str());
    sscanf(LinhaArray, "%d %d %d %d", AXOffset, AYOffset, BXOffset, BYOffset);

    *LineColor = (TColor)INITIAL->ReadInteger("Conector" + AnsiString(Ordem), "Color", 0);
*/
}

#endif
