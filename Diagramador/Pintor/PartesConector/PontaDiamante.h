#include "Pintor\ParteConector.h"

#ifndef PontaDiamanteH

class PontaDiamante: public ParteConector
{
	private:
        // Variável que indica se o interior do diamante
        // deve ser pintado ou não
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

    // O ponto inicial é igual ao ponto final
    p[4].x = Destino.x;
    p[4].y = Destino.y;

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