#include "Fabricas\FabricaSemantica.h"

#include "Objetos\Objeto.h"
#include "Conectores\Connector.h"
#include "Conectores\ConnAssociacao.h"

#include "ItemProjeto.h"

#ifndef ProjetoH
#define ProjetoH

typedef void __fastcall (__closure *TNotificaInclusaoObjeto)(Objeto *novoObjeto);
typedef void __fastcall (__closure *TNotificaInclusaoConector)(Connector *novoConector);

class Projeto
{
	private:
        TList *ListaObjetos;
        TList *ListaConectores;
        TList *ListaDiagramas;
        TNotificaInclusaoObjeto notificaInclusaoObjeto;
        TNotificaInclusaoConector notificaInclusaoConector;

    protected:
        // Adição
        void AddObjeto(TObject *novo);
        void AddConector(TObject *novo);
        void AddDiagrama(TObject *novo);
            
    public:
    	Projeto()
        {
            ListaObjetos = new TList();
            ListaConectores = new TList();
            ListaDiagramas = new TList();
        }
    	~Projeto()
        {
            delete ListaObjetos, ListaConectores, ListaDiagramas;
        }

        void SetNotificacaoInclusaoObjeto(TNotificaInclusaoObjeto procedure);
        void NotificaInclusaoObjeto(TObject *novo);

        void SetNotificacaoInclusaoConector(TNotificaInclusaoConector procedure);
        void NotificaInclusaoConector(TObject *novo);

        // Busca
        ItemProjeto* GetObjeto(AnsiString nome, int type);
        ItemProjeto* GetConector(Objeto *A, Objeto *B, int type);
        ItemProjeto* GetConector(Objeto *A, Connector *End, int type);
        ItemProjeto* GetDiagrama(AnsiString nome);
};
void Projeto::SetNotificacaoInclusaoObjeto(TNotificaInclusaoObjeto procedure)
{
    notificaInclusaoObjeto = procedure;
}
void Projeto::NotificaInclusaoObjeto(TObject *novo)
{
    // Executo o procedimento de inclusão do objeto
    if (notificaInclusaoObjeto != NULL)
        (notificaInclusaoObjeto)((Objeto*)novo);
}
void Projeto::SetNotificacaoInclusaoConector(TNotificaInclusaoConector procedure)
{
    notificaInclusaoConector = procedure;
}
void Projeto::NotificaInclusaoConector(TObject *novo)
{
    // Executo o procedimento de inclusão do objeto
    if (notificaInclusaoConector != NULL)
        (notificaInclusaoConector)((Connector*)novo);
}
void Projeto::AddObjeto(TObject *novo)
{
    ListaObjetos->Add(novo);
}
void Projeto::AddConector(TObject *novo)
{
    ListaConectores->Add(novo);
    NotificaInclusaoConector((TObject*)novo);
}
void Projeto::AddDiagrama(TObject *novo)
{
    ListaDiagramas->Add(novo);
}
ItemProjeto* Projeto::GetObjeto(AnsiString nome, int type)
{
    Objeto *objeto;
    for(int i=0; i < ListaObjetos->Count; i++)
    {
        objeto = (Objeto*)ListaObjetos->Items[i];
        if (objeto->GetName() == nome)
        {
            return objeto;
        }
    }
    // Se chegar até aqui é porque não achei o objeto.
    FabricaSemantica fabrica;
    objeto = fabrica.FabricaObjetos(type, GetNewID());
    objeto->SetName(nome);
    AddObjeto((TObject*)objeto);

    return objeto;
}
ItemProjeto* Projeto::GetConector(Objeto *A, Objeto *B, int type)
{
    Connector *conector;
    for(int i=0; i < ListaConectores->Count; i++)
    {
        conector = (Connector*)ListaConectores->Items[i];
        if (conector->A == A && conector->B == B)
        {
            return conector;
        }
    }
    // Se chegar até aqui é porque não achei o conector.
    FabricaSemantica fabrica;
    conector = fabrica.FabricaConectores(type, GetNewID());
    conector->Connect(A, B);
    AddConector((TObject*)conector);

    return conector;
}
ItemProjeto* Projeto::GetConector(Objeto *A, Connector *End, int type)
{
    Connector *conector;
    ConnAssociativo *esteConector;
    for(int i=0; i < ListaConectores->Count; i++)
    {
        conector = (Connector*)ListaConectores->Items[i];
        if (conector->GetType() == type)
        {
            esteConector = (ConnAssociativo*)conector;
            if (esteConector->A == A && esteConector->GetConectorEndLine() == End)
            {
                return conector;
            }
        }
    }
    // Se chegar até aqui é porque não achei o conector.
    FabricaSemantica fabrica;
    conector = fabrica.FabricaConectores(type, GetNewID());
    esteConector = (ConnAssociativo*)conector;
    esteConector->Connect(A, NULL);
    esteConector->SetConectorEndLine(End);
    AddConector((TObject*)esteConector);

    return conector;
}
ItemProjeto* Projeto::GetDiagrama(AnsiString nome)
{
/*    ItemProjeto *diagrama;
    for(int i=0; i<ListaDiagramas->Count; i++)
    {
        diagrama = (ItemProjeto*)ListaDiagramas->Items[i];
        if (diagrama->GetDiagramName() == nome)
        {
            return diagrama;
        }
    }
*/
    return NULL;
}
#endif
