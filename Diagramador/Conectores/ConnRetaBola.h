#include "Conectores\Connector.h"

#ifndef ConnRetaBolaH

class ConnRetaBola: public Connector
{
    private:
	public:
        ConnRetaBola(int ConnType, int ConnId):Connector(ConnType, ConnId)
        {
        }
        ~ConnRetaBola()
        {
        }

        void Salva(int Ordem, TIniFile *INITIAL);
        void Carrega(int Ordem, TIniFile *INITIAL);
};

void ConnRetaBola::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaConector(Ordem, INITIAL);
}
void ConnRetaBola::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaConector(Ordem, INITIAL);
}

#define ConnRetaBolaH
#endif