#include "Objetos\View\ViewObjConceito.h"
#include "Objetos\View\ViewObjClasse.h"
#include "Objetos\View\ViewObjAtor.h"
#include "Objetos\View\ViewObjComentario.h"
#include "Objetos\View\ViewObjEstado.h"
#include "Objetos\View\ViewObjEstadoFinalInicial.h"

#include "Conectores\View\ViewConnAssociacao.h"
#include "Conectores\View\ViewConnRetaBola.h"
#include "Conectores\View\ViewConnHeranca.h"
#include "Conectores\View\ViewConnDependencia.h"
#include "Conectores\View\ViewConnAgregacao.h"
#include "Conectores\View\ViewConnAssociativo.h"

#ifndef FabricaViewsH
#define FabricaViewsH

class FabricaViews
{
	private:
    protected:
    public:
		ViewObjeto* FabricaViewObjetos(int Type);
		ViewConector* FabricaViewConectores(int Type);
};

ViewObjeto* FabricaViews::FabricaViewObjetos(int Type)
{
    ViewObjeto *Produto;
    switch(Type)
    {
        case oConceito:
            Produto = new ViewObjConceito();
            break;
        case oClasse:
            Produto = new ViewObjClasse();
            break;
        case oAtor:
            Produto = new ViewObjAtor();
            break;
        case oEstado:
            Produto = new ViewObjEstado();
            break;
        case oEstadoInicial:
            Produto = new ViewObjEstadoFinalInicial(false);
            break;
        case oEstadoFinal:
            Produto = new ViewObjEstadoFinalInicial(true);
            break;
        case oComentario:
            Produto = new ViewObjComentario();
            break;
    }
    return Produto;
}

ViewConector* FabricaViews::FabricaViewConectores(int Type)
{
    ViewConector *Produto;
    switch(Type)
    {
        case cRetaBola:
            Produto = new ViewConnRetaBola();
            break;
        case cAssociacao:
            Produto = new ViewConnAssociacao();
            break;
        case cHeranca:
            Produto = new ViewConnHeranca();
            break;
        case cAgregacao:
            Produto = new ViewConnAgregacao(false);
            break;
        case cComposicao:
            Produto = new ViewConnAgregacao(true);
            break;
        case cDependencia:
            Produto = new ViewConnDependencia(true);
            break;
        case cTransicao:
            Produto = new ViewConnDependencia(false);
            break;
        case cAssociativo:
            Produto = new ViewConnAssociativo();
            break;
    }
    return Produto;
}

#endif
