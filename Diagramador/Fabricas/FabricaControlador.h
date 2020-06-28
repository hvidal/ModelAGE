#include "Interfaces\IControladorObjeto.h"
#include "Interfaces\IControladorConector.h"

// Produtos fabricados:
#include "Controlador\ControladorObjetoClasse.h"

#ifndef FabricaControladorH

class FabricaControlador
{
	private:
    protected:
    public:
		IControladorObjeto* CriaControladorObjeto(int Type);
		IControladorConector* CriaControladorConector(int Id);
};
IControladorObjeto* FabricaControlador::CriaControladorObjeto(int Type)
{
    IControladorObjeto *Produto;
    switch(Type)
    {
        case oConceito:
            Produto = NULL;
            break;
        case oClasse:
            Produto = new ControladorObjetoClasse();
            break;
        case oAtor:
            Produto = NULL;
            break;
        case oEstado:
            Produto = NULL;
            break;
        case oEstadoInicial:
            Produto = NULL;
            break;
        case oEstadoFinal:
            Produto = NULL;
            break;
        case oComentario:
            Produto = NULL;
            break;
    }
    return Produto;
}
IControladorConector* FabricaControlador::CriaControladorConector(int Id)
{
    IControladorConector *Produto;
    switch(Id)
    {
        case cRetaBola:
            Produto = NULL;
            break;
        case cAssociacao:
            Produto = NULL;
            break;
        case cHeranca:
            Produto = NULL;
            break;
        case cAgregacao:
            Produto = NULL;
            break;
        case cComposicao:
            Produto = NULL;
            break;
        case cDependencia:
            Produto = NULL;
            break;
        case cTransicao:
            Produto = NULL;
            break;
        case cAssociativo:
            Produto = NULL;
            break;
    }
    return Produto;
}
#define FabricaControladorH
#endif
