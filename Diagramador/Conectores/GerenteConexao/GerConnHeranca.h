#include <Interfaces\ISemanticaConexao.h>

#ifndef GerConnHerancaH
#define GerConnHerancaH

class GerConnHeranca: public ISemanticaConexao
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
