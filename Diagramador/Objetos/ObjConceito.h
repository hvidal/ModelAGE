#include "Objetos\Objeto.h"

#include "Pintor\PartesObjeto\FormaConceito.h"

#ifndef ObjConceitoH

class ObjConceito: public Objeto
{
  public:
    ObjConceito(int _Type, int _Id): Objeto(_Type, _Id)
    {
    }
    ~ObjConceito()
    {
    }

    void Salva(int Ordem, TIniFile *INITIAL);
    void Carrega(int Ordem, TIniFile *INITIAL);
};
void ObjConceito::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaObjeto(Ordem, INITIAL);
}
void ObjConceito::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaObjeto(Ordem, INITIAL);
}

#define ObjConceitoH
#endif