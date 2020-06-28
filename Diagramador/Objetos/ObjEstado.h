#include "Objetos\Objeto.h"

#include "Pintor\PartesObjeto\FormaEstado.h"

#ifndef ObjEstadoH

class ObjEstado: public Objeto
{
 public:
    ObjEstado(int _Type, int _Id): Objeto(_Type, _Id)
    {
    }

    void Salva(int Ordem, TIniFile *INITIAL);
    void Carrega(int Ordem, TIniFile *INITIAL);
};
void ObjEstado::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaObjeto(Ordem, INITIAL);
}
void ObjEstado::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaObjeto(Ordem, INITIAL);
}
#define ObjEstadoH
#endif