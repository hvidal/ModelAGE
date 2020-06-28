#include "Objetos\Objeto.h"

#include "Pintor\PartesObjeto\FormaAtor.h"

#ifndef ObjAtorH

class ObjAtor: public Objeto
{
  public:
    ObjAtor(int _Type, int _Id): Objeto(_Type, _Id)
    {
    }
	void Salva(int Ordem, TIniFile *INITIAL);
	void Carrega(int Ordem, TIniFile *INITIAL);
};
void ObjAtor::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaObjeto(Ordem, INITIAL);
}
void ObjAtor::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaObjeto(Ordem, INITIAL);
}
#define ObjAtorH
#endif