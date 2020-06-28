#include "Pintor\ParteConector.h"

#ifndef PontaFlechaH

class PontaFlecha: public ParteConector
{
	public:
        PontaFlecha(): ParteConector()
        {
        }
        ~PontaFlecha()
        {
        }
	void Paint(TCanvas *Board, TPoint Origem, TPoint Destino);
};

void PontaFlecha::Paint(TCanvas *Board, TPoint Origem, TPoint Destino)
{
    float Angulo, CosAngulo, Vx, Vy, SomaQuadrados;
    TPoint p[4];

    p[0].x = Destino.x;
    p[0].y = Destino.y;

    // O ponto inicial � igual ao ponto final
    p[3].x = Destino.x;
    p[3].y = Destino.y;

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

	p[1].x = p[0].x + 13 * cos(((Angulo - 30)*M_PI)/180.0);
	p[1].y = p[0].y - 13 * sin(((Angulo - 30)*M_PI)/180.0);

	p[2].x = p[0].x + 13 * cos(((Angulo + 30)*M_PI)/180.0);
	p[2].y = p[0].y - 13 * sin(((Angulo + 30)*M_PI)/180.0);

    Board->MoveTo(p[0].x, p[0].y);
    Board->LineTo(p[1].x, p[1].y);

    Board->MoveTo(p[0].x, p[0].y);
    Board->LineTo(p[2].x, p[2].y);
}

#define PontaFlechaH
#endif