#include "Objetos\Objeto.h"

#include "Pintor\PartesObjeto\FormaComentario.h"

#ifndef ObjComentarioH

class ObjComentario : public Objeto
{
  public:
    ObjComentario(int _Type, int _Id): Objeto(_Type, _Id)
    {
    }

	void Salva(int Ordem, TIniFile *INITIAL);
	void Carrega(int Ordem, TIniFile *INITIAL);
};

void ObjComentario::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaObjeto(Ordem, INITIAL);
}

void ObjComentario::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaObjeto(Ordem, INITIAL);
}
#define ObjComentarioH
#endif