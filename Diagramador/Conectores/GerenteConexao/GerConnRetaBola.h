#include <Interfaces\ISemanticaConexao.h>

#ifndef GerConnRetaBolaH
#define GerConnRetaBolaH

class GerConnRetaBola: public ISemanticaConexao
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
