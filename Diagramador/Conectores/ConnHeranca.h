#include "Conectores\Connector.h"

#ifndef ConnHerancaH

class ConnHeranca: public Connector
{
	private:
	public:
        ConnHeranca(int ConnType, int ConnId):Connector(ConnType, ConnId)
        {
        }
        ~ConnHeranca()
        {
        }
        void Salva(int Ordem, TIniFile *INITIAL);
        void Carrega(int Ordem, TIniFile *INITIAL);
};

void ConnHeranca::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaConector(Ordem, INITIAL);
}

void ConnHeranca::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaConector(Ordem, INITIAL);
}
#define ConnHerancaH
#endif