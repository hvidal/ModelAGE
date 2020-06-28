#include "Conectores\Connector.h"

#ifndef ConnAssociativoH

class ConnAssociativo: public Connector
{
    private:
	public:
        ConnAssociativo(int ConnType, int ConnId):Connector(ConnType, ConnId)
        {
        }

    	void Salva(int Ordem, TIniFile *INITIAL);
        void Carrega(int Ordem, TIniFile *INITIAL);
};

void ConnAssociativo::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaConector(Ordem, INITIAL);
}
void ConnAssociativo::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaConector(Ordem, INITIAL);
}

#define ConnAssociativoH
#endif