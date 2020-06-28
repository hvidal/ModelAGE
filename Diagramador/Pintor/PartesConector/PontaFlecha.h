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

    // O ponto inicial é igual ao ponto final
    p[3].x = Destino.x;
    p[3].y = Destino.y;

    // O vetor (Vx,Vy) é o vetor que parte do ponto base,
    // e atinge a origem (X1,Y1)
    Vx =Origem.x - p[0].x;
    Vy =Origem.y - p[0].y;

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
    if(Origem.x <= p[0].x && Origem.y >= p[0].y)
    {
	    // 3º Quadrante
    	Angulo = -Angulo;
    }
    else if(Origem.x >= p[0].x && Origem.y >= p[0].y)
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