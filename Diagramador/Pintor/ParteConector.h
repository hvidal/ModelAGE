#include "Pintor/Figura.h"

#ifndef ParteConectorH

#define DISTANCIA_LIMITE 100

class ParteConector: public Figura
{
	private:
    protected:
        // variáveis de ESTADO
        bool *isDragging;
    public:
    	ParteConector(): Figura()
        {
            isDragging = new bool;
            *isDragging = false;
        }
    	~ParteConector()
        {
            delete isDragging;
        }

        // Abstratos:
        virtual void Paint(TCanvas *Board, TPoint Origem, TPoint Destino) = 0;

        static TPoint Fronteira(int XDest, int YDest, int BHeight, int BWidth, int XoffsetDest, int YoffsetDest, int XOrig, int YOrig, int AHeight, int AWidth, int XoffsetOrig, int YoffsetOrig);

        // Getters & Setters
        void SetDragging(bool dragging);

};
void ParteConector::SetDragging(bool dragging)
{
    *isDragging = dragging;
}

TPoint ParteConector::Fronteira(int XDest, int YDest, int BHeight, int BWidth, int XoffsetDest, int YoffsetDest, int XOrig, int YOrig, int AHeight, int AWidth, int XoffsetOrig, int YoffsetOrig)
{
    TPoint G;
    float X1, Y1, X2, Y2;
    X1 = XOrig + AWidth/2 - XoffsetOrig;
    Y1 = YOrig - AHeight/2 - YoffsetOrig;

    X2 = XDest + BWidth/2 - XoffsetDest;
    Y2 = YDest - BHeight/2 - YoffsetDest;

    float a, b, denominador; // Coeficientes da reta: y = ax + b

    denominador = (X2 - X1);

    if(denominador==0)
    {
        if(Y1>Y2)
        {
            // A linha corta pela borda inferior...
            G.x = X1;
            G.y = YDest;
            return G;
        }
        else
        {
            // A linha corta pela borda superior...
            G.x = X1;
            G.y = YDest - BHeight;
            return G;
        }
    }

    a = (Y2 - Y1)/denominador;

    b = Y1 - a * X1;

    if(X2 > X1) // [A]------>[B]
    {
        //   Ax-> +-------+
        //        |  Obj  |
        //        |       |
        //   Bx-> +-------+
        float Yaux, Xaux, Ax, Bx;

        Ax = YDest - BHeight;
        Bx = YDest;

        Yaux = a * (XDest) + b;

        if(Yaux >= Ax && Yaux <= Bx)
        {
            // A linha corta pela lateral esquerda...
            Yaux = a * (XDest) + b;

            G.x = XDest;
            G.y = Yaux + 1;
        }
        else if(Yaux > Bx && Yaux > Ax)
        {
            // A linha corta pela borda inferior...
            Xaux = ((YDest) - b)/a;

            G.x = Xaux;
            G.y = YDest;
        }
        else if(Yaux < Bx && Yaux < Ax)
        {
            // A linha corta pela borda superior...
            Xaux = ((YDest - BHeight) - b)/a;

            G.x = Xaux;
            G.y = YDest - BHeight;
        }
    }
    else // [A]<------[B]
    {
        //    +-------+ <-Ax
        //    |  Obj  |
        //    |       |
        //    +-------+ <-Bx
        float Yaux, Xaux, Ax, Bx;

        Ax = YDest - BHeight;
        Bx = YDest;

        Yaux = a * (XDest + BWidth) + b;

        if(Yaux >= Ax && Yaux <= Bx)
        {
            // A linha corta pela lateral direita...
            Yaux = a * (XDest + BWidth) + b;

            G.x = XDest + BWidth;
            G.y = Yaux + 1;
        }
        else if(Yaux > Bx && Yaux > Ax)
        {
            // A linha corta pela borda inferior...
            Xaux = ((YDest) - b)/a;

            G.x = Xaux;
            G.y = YDest;
        }
        else if(Yaux < Bx && Yaux < Ax)
        {
            // A linha corta pela borda superior...
            Xaux = ((YDest - BHeight) - b)/a;

            G.x = Xaux;
            G.y = YDest - BHeight;
        }
    }
    return G;
}
#define ParteConectorH
#endif