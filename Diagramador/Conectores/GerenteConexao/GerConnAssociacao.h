#include <Interfaces\ISemanticaConexao.h>

#ifndef GerConnAssociacaoH
#define GerConnAssociacaoH

class GerConnAssociacao: public ISemanticaConexao
{
  public:
    // Entre conectores
    bool CanPointToConnector(int TipoConector)
    {
        return false;
    }
    bool CanPointToConnector()
    {
        return false;
    }

    //Entre Objetos
    bool CanPointToObject()
    {
        return true;
    }    
    bool CanStartAtObject(int TipoObjeto)
    {
        return true;
    }
    bool CanEndAtObject(int TipoObjeto)
    {
        return true;
    }
};
#endif
