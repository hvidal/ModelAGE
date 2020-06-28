#include "Conectores\Connector.h"

#ifndef ConnDependenciaH

class ConnDependencia: public Connector
{
    private:
	public:
        ConnDependencia(int ConnType, int ConnId):Connector(ConnType, ConnId)
        {
        }
        ~ConnDependencia()
        {
        }
        void Salva(int Ordem, TIniFile *INITIAL);
        void Carrega(int Ordem, TIniFile *INITIAL);
};

void ConnDependencia::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaConector(Ordem, INITIAL);
}

void ConnDependencia::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaConector(Ordem, INITIAL);
}
#define ConnDependenciaH
#endif