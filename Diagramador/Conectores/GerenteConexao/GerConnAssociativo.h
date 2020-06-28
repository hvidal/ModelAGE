#include <Interfaces\ISemanticaConexao.h>

#ifndef GerConnAssociativoH
#define GerConnAssociativoH

class GerConnAssociativo: public ISemanticaConexao
{
  public:
    // Entre conectores
    bool CanPointToConnector(int TipoConector)
    {
        return true;
    }
    bool CanPointToConnector()
    {
        return true;
    }

    //Entre Objetos
    bool CanPointToObject()
    {
        return false;
    }
    bool CanStartAtObject(int TipoObjeto)
    {
        return true;
    }
    bool CanEndAtObject(int TipoObjeto)
    {
        return false;
    }
};
#endif
