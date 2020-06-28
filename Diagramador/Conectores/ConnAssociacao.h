#include "Conectores\Connector.h"
#include "Conectores\ConnAssociativo.h"

#ifndef ConnAssociacaoH

class ConnAssociacao: public Connector
{
    private:
	public:
        ConnAssociacao(int ConnType, int ConnId):Connector(ConnType, ConnId)
        {
        }
        ~ConnAssociacao()
        {
        }
    	void Salva(int Ordem, TIniFile *INITIAL);
	    void Carrega(int Ordem, TIniFile *INITIAL);
};
void ConnAssociacao::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaConector(Ordem, INITIAL);
}

void ConnAssociacao::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaConector(Ordem, INITIAL);
}

#define ConnAssociacaoH
#endif