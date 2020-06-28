#include "Pintor\ParteConector.h"

#ifndef PontaCircularH

class PontaCircular: public ParteConector
{
	private:
        int *raio;
	public:
        PontaCircular(): ParteConector()
        {
            raio = new int;
            *raio = 4;
        }
        ~PontaCircular()
        {
        }
	void Paint(TCanvas *Board, TPoint Origem, TPoint Destino);
};

void PontaCircular::Paint(TCanvas *Board, TPoint Origem, TPoint Destino)
{
	float Angulo, CosAngulo, Vx, Vy, SomaQuadrados;
	TPoint PontoMeio;

    // O vetor (Vx,Vy) � o vetor que parte do ponto base,
    // e atinge a origem (X1,Y1)
    Vx =Origem.x - Destino.x;
    Vy =Origem.y - Destino.y;

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
    if(Origem.x <= Destino.x && Origem.y >= Destino.y)
    {
	    // 3� Quadrante
    	Angulo = -Angulo;
    }
    else if(Origem.x >= Destino.x && Origem.y >= Destino.y)
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

    PontoMeio.x = Destino.x + (*raio) * cos(((Angulo)*M_PI)/180.0);
	PontoMeio.y = Destino.y - (*raio) * sin(((Angulo)*M_PI)/180.0);

    Board->Ellipse(PontoMeio.x - *raio , PontoMeio.y - *raio, PontoMeio.x + *raio, PontoMeio.y + *raio);
}

#define PontaCircularH
#endif