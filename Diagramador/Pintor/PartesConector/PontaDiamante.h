#include "Pintor\ParteConector.h"

#ifndef PontaDiamanteH

class PontaDiamante: public ParteConector
{
	private:
        // Vari�vel que indica se o interior do diamante
        // deve ser pintado ou n�o
    	bool *Pinta;

	public:
        PontaDiamante(bool pintarInterior): ParteConector()
        {
            Pinta = new bool;
            *Pinta = pintarInterior;
        }
        ~PontaDiamante()
        {
            delete Pinta;
        }
        void Paint(TCanvas *Board, TPoint Origem, TPoint Destino);

        void SetPinta(bool devePintar);
        bool GetPinta();
};

void PontaDiamante::SetPinta(bool devePintar)
{
	*Pinta = devePintar;
}
bool PontaDiamante::GetPinta()
{
	return *Pinta;
}
void PontaDiamante::Paint(TCanvas *Board, TPoint Origem, TPoint Destino)
{
    float Angulo, CosAngulo, Vx, Vy, SomaQuadrados;
    TColor CorOriginal;
    TPoint PontoMeio;
    TPoint p[5];

    p[0].x = Destino.x;
    p[0].y = Destino.y;

    // O ponto inicial � igual ao ponto final
    p[4].x = Destino.x;
    p[4].y = Destino.y;

    // O vetor (Vx,Vy) � o vetor que parte do ponto base,
    // e atinge a origem (X1,Y1)
    Vx =Origem.x - p[0].x;
    Vy =Origem.y - p[0].y;

    // Agora usaremos a f�rmula
    //        u . v = |u||v| cos �
    // Onde:
    // u . v = Produto Escalar
    // Obs.: Neste caso o produto escalar � feito entre o vetor
    //      (Vx,Vy) com o vetor horizontal (1,0).
    //       Portanto, Produto Escalar = Vx.
    // |u| = m�dulo de u = raiz quadrada de Vx^2 + Vy^2
    // |v| = m�dulo de v = 1
    // cos � = � o que n�s queremos

    SomaQuadrados = Vx*Vx + Vy*Vy;

    // Se o centro do objeto Origem est� sobre o
    // ponto base...
    if(SomaQuadrados == 0)
		return;

    CosAngulo = Vx/sqrt(SomaQuadrados);

    //Consigo o angulo em Radianos
    Angulo = acos(CosAngulo);

    // Converto para Graus
    Angulo = Angulo * 180 / M_PI;

    // Se a origem (X1,Y1) estiver no 3� ou 4� quadrante
    // em rela��o ao ponto base, ent�o tem que mudar o
    // sinal do angulo, pois o calculo vetorial fornece
    // o cosseno do menor �ngulo entre os vetores, e n�o o maior...
    if(Origem.x <= p[0].x && Origem.y >= p[0].y)
    {
	    // 3� Quadrante
    	Angulo = -Angulo;
    }
    else if(Origem.x >= p[0].x && Origem.y >= p[0].y)
    {
    	// 4� Quadrante
        Angulo = -Angulo;
    }

    // Agora acharemos os dois pontos principais.
    // Para isso, precisamos rodar em torno do ponto base
    // um ponto que est� � 10 pixels de dist�ncia do mesmo.
    // Usamos o angulo achado acima para saber qual a dire��o
    // da origem. Ent�o, somamos 25 graus no sentido hor�rio
    // e anti-hor�rio para buscar os pontos A e B, respectivamente.

    // N�o podemos nos esquecer que o nosso angulo est� em graus
    // e a fun��o cos() e sin() usam angulos em radianos, por isso
    // temos que fazer a convers�o...

	p[1].x = p[0].x + 10 * cos(((Angulo - 30)*M_PI)/180.0);
	p[1].y = p[0].y - 10 * sin(((Angulo - 30)*M_PI)/180.0);

	p[3].x = p[0].x + 10 * cos(((Angulo + 30)*M_PI)/180.0);
	p[3].y = p[0].y - 10 * sin(((Angulo + 30)*M_PI)/180.0);

    p[2].x = p[0].x + 19 * cos(((Angulo)*M_PI)/180.0);
	p[2].y = p[0].y - 19 * sin(((Angulo)*M_PI)/180.0);

    PontoMeio.x = p[0].x + 17 * cos(((Angulo)*M_PI)/180.0);
	PontoMeio.y = p[0].y - 17 * sin(((Angulo)*M_PI)/180.0);

    CorOriginal = Board->Brush->Color;

    Board->Brush->Color = clBlack;
    if(*Pinta)
    {
    	Board->Polygon(p, 4);
    }
    else
    {   if (*isDragging)
	        Board->Brush->Color = clBlack;
        else
	        Board->Brush->Color = clWhite;
    	Board->Polygon(p, 4);
//        Board->Polyline(p, 4);
    }
    Board->Brush->Color = CorOriginal;
}

#define PontaDiamanteH
#endif