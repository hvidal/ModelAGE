#include "Objetos\Objeto.h"

#include "Pintor\PartesObjeto\FormaEstadoFinalInicial.h"

#ifndef ObjEstadoFinalInicialH

class ObjEstadoFinalInicial: public Objeto
{
 private:
    bool *EstadoFinal;
 public:
    ObjEstadoFinalInicial(int _Type, int _Id, bool estadoFinal): Objeto(_Type, _Id)
    {
        EstadoFinal = new bool;
        *EstadoFinal = estadoFinal;
    }
    ~ObjEstadoFinalInicial()
    {
    	delete EstadoFinal;
    }
    void Salva(int Ordem, TIniFile *INITIAL);
    void Carrega(int Ordem, TIniFile *INITIAL);
};
void ObjEstadoFinalInicial::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaObjeto(Ordem, INITIAL);
}
void ObjEstadoFinalInicial::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaObjeto(Ordem, INITIAL);
}

#define ObjEstadoFinalInicialH
#endif