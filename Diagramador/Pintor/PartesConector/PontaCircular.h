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

    // O vetor (Vx,Vy) é o vetor que parte do ponto base,
    // e atinge a origem (X1,Y1)
    Vx =Origem.x - Destino.x;
    Vy =Origem.y - Destino.y;

    // Agora usaremos a fórmula
    //        u . v = |u||v| cos ð
    // Onde:
    // u . v = Produto Escalar
    // Obs.: Neste caso o produto escalar é feito entre o vetor
    //      (Vx,Vy) com o vetor horizontal (1,0).
    //       Portanto, Produto Escalar = Vx.
    // |u| = módulo de u = raiz quadrada de Vx^2 + Vy^2
    // |v| = módulo de v = 1
    // cos ð = É o que nós queremos

    SomaQuadrados = Vx*Vx + Vy*Vy;

    // Se o centro do objeto Origem está sobre o
    // ponto base...
    if(SomaQuadrados == 0)
		return;

    CosAngulo = Vx/sqrt(SomaQuadrados);

    //Consigo o angulo em Radianos
    Angulo = acos(CosAngulo);

    // Converto para Graus
    Angulo = Angulo * 180 / M_PI;

    // Se a origem (X1,Y1) estiver no 3º ou 4º quadrante
    // em relação ao ponto base, então tem que mudar o
    // sinal do angulo, pois o calculo vetorial fornece
    // o cosseno do menor ângulo entre os vetores, e não o maior...
    if(Origem.x <= Destino.x && Origem.y >= Destino.y)
    {
	    // 3º Quadrante
    	Angulo = -Angulo;
    }
    else if(Origem.x >= Destino.x && Origem.y >= Destino.y)
    {
    	// 4º Quadrante
        Angulo = -Angulo;
    }

    // Agora acharemos os dois pontos principais.
    // Para isso, precisamos rodar em torno do ponto base
    // um ponto que está à 10 pixels de distância do mesmo.
    // Usamos o angulo achado acima para saber qual a direção
    // da origem. Então, somamos 25 graus no sentido horário
    // e anti-horário para buscar os pontos A e B, respectivamente.

    // Não podemos nos esquecer que o nosso angulo está em graus
    // e a função cos() e sin() usam angulos em radianos, por isso
    // temos que fazer a conversão...

    PontoMeio.x = Destino.x + (*raio) * cos(((Angulo)*M_PI)/180.0);
	PontoMeio.y = Destino.y - (*raio) * sin(((Angulo)*M_PI)/180.0);

    Board->Ellipse(PontoMeio.x - *raio , PontoMeio.y - *raio, PontoMeio.x + *raio, PontoMeio.y + *raio);
}

#define PontaCircularH
#endif