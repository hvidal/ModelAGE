#include "Conectores\Connector.h"

#ifndef IControladorConectorH
#define IControladorConectorH

// Classe Interface do Controlador de Conectores
class IControladorConector
{
	private:
    	virtual void MontaJanela(Connector *conector)=0;
        virtual void SalvaDados(Connector *conector, TPaintBox *Board)=0;
    protected:
    public:
        virtual bool Execute(Connector *conector, TPaintBox *Board)=0;
};

#endif
