#include "Conectores\Connector.h"

#ifndef ConnAgregacaoH

class ConnAgregacao: public Connector
{
	private:
    public:
        ConnAgregacao(int ConnType, int ConnId):Connector(ConnType, ConnId)
        {
        }
        ~ConnAgregacao()
        {
        }
        void Salva(int Ordem, TIniFile *INITIAL);
        void Carrega(int Ordem, TIniFile *INITIAL);
};
void ConnAgregacao::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaConector(Ordem, INITIAL);
}
void ConnAgregacao::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaConector(Ordem, INITIAL);
}
#define ConnAgregacaoH
#endif