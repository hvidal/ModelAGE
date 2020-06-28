#include <Interfaces\ISemanticaConexao.h>

#include <Conectores\GerenteConexao\GerConnRetaBola.h>
#include <Conectores\GerenteConexao\GerConnAssociacao.h>
#include <Conectores\GerenteConexao\GerConnAssociativo.h>
#include <Conectores\GerenteConexao\GerConnDependencia.h>
#include <Conectores\GerenteConexao\GerConnHeranca.h>
#include <Conectores\GerenteConexao\GerConnAgregacao.h>

#ifndef FabricaGerenteConexaoH
#define FabricaGerenteConexaoH

class FabricaGerenteConexao
{
    public:
        ISemanticaConexao* FabricaGerente(int TipoConector);
};

ISemanticaConexao* FabricaGerenteConexao::FabricaGerente(int TipoConector)
{
    ISemanticaConexao *Produto;
    switch(TipoConector)
    {
        case cRetaBola:
            Produto = new GerConnRetaBola();
            break;
        case cAssociacao:
            Produto = new GerConnAssociacao();
            break;
        case cHeranca:
            Produto = new GerConnHeranca();
            break;
        case cAgregacao:
            Produto = new GerConnAgregacao();
            break;
        case cComposicao:
            Produto = new GerConnAgregacao();
            break;
        case cDependencia:
            Produto = new GerConnDependencia();
            break;
        case cTransicao:
            Produto = new GerConnDependencia();
            break;
        case cAssociativo:
            Produto = new GerConnAssociativo();
            break;
    }
    return Produto;
}

#endif
