#include "Objetos\Objeto.h"

#ifndef IControladorObjetoH
#define IControladorObjetoH

// Classe Interface do Controlador de Objetos
class IControladorObjeto
{
	private:
    	virtual void MontaJanela(Objeto *view)=0;
        virtual void SalvaDados(Objeto *view)=0;
    protected:
    public:
        virtual bool Execute(Objeto *view)=0;
        virtual void EfetuaAjustesView(ViewObjeto *view, TPaintBox *Board)=0;
};

#endif
