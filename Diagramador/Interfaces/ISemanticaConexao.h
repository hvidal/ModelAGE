#ifndef ISemanticaConexaoH
#define ISemanticaConexaoH

/*
  Interface para defini��o de regras sem�nticas de conex�o de objetos.
*/

class ISemanticaConexao
{
  public:
    // Entre conectores
    virtual bool CanPointToConnector(int TipoConector) = 0;
    virtual bool CanPointToConnector() = 0;

    //Entre Objetos
    virtual bool CanPointToObject() = 0;    
    virtual bool CanStartAtObject(int TipoObjeto) = 0;
    virtual bool CanEndAtObject(int TipoObjeto) = 0;
};

#endif
