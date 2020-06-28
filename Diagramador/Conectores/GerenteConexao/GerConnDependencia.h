#include <Interfaces\ISemanticaConexao.h>

#ifndef GerConnDependenciaH
#define GerConnDependenciaH

class GerConnDependencia: public ISemanticaConexao
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
