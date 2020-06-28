#include "Objetos\ObjConceito.h"
#include "Objetos\ObjClasse.h"
#include "Objetos\ObjAtor.h"
#include "Objetos\ObjComentario.h"
#include "Objetos\ObjEstado.h"
#include "Objetos\ObjEstadoFinalInicial.h"

#include "Conectores\ConnAssociacao.h"
#include "Conectores\ConnRetaBola.h"
#include "Conectores\ConnHeranca.h"
#include "Conectores\ConnDependencia.h"
#include "Conectores\ConnAgregacao.h"
#include "Conectores\ConnAssociativo.h"

#ifndef FabricaSemanticaH

#define cRetaBola 	1
#define cAssociacao    	2
#define cHeranca       	3
#define cAgregacao 	4
#define cComposicao 	5
#define cDependencia 	6
#define cTransicao	7
#define cAssociativo	8

#define oConceito 	  1
#define oClasse      	  2
#define oAtor    	  3
#define oEstado 	  4
#define oEstadoInicial    5
#define oEstadoFinal      6
#define oComentario      -1

class FabricaSemantica
{
    private:
    protected:
    public:
      Objeto* FabricaObjetos(int Type, int ID);
      Connector* FabricaConectores(int Type, int Id);
};

Objeto* FabricaSemantica::FabricaObjetos(int Type, int ID)
{
    Objeto *Produto;
    switch(Type)
    {
        case oConceito:
            Produto = new ObjConceito(Type, ID);
            break;
        case oClasse:
            Produto = new ObjClasse(Type, ID);
            break;
        case oAtor:
            Produto = new ObjAtor(Type, ID);
            break;
        case oEstado:
            Produto = new ObjEstado(Type, ID);
            break;
        case oEstadoInicial:
            Produto = new ObjEstadoFinalInicial(Type, ID, false);
            break;
        case oEstadoFinal:
            Produto = new ObjEstadoFinalInicial(Type, ID, true);
            break;
        case oComentario:
            Produto = new ObjComentario(Type, ID);
            break;
    }
    return Produto;
}

Connector* FabricaSemantica::FabricaConectores(int Type, int Id)
{
    Connector *Produto;
    switch(Type)
    {
        case cRetaBola:
            Produto = new ConnRetaBola(Type, Id);
            break;
        case cAssociacao:
            Produto = new ConnAssociacao(Type, Id);
            break;
        case cHeranca:
            Produto = new ConnHeranca(Type, Id);
            break;
        case cAgregacao:
            Produto = new ConnAgregacao(Type, Id);
            break;
        case cComposicao:
            Produto = new ConnAgregacao(Type, Id);
            break;
        case cDependencia:
            Produto = new ConnDependencia(Type, Id);
            break;
        case cTransicao:
            Produto = new ConnDependencia(Type, Id);
            break;
        case cAssociativo:
            Produto = new ConnAssociativo(Type, Id);
            break;
    }
    return Produto;
}

#define FabricaSemanticaH
#endif
