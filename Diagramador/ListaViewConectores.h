#include "Conectores\View\ViewConector.h"
#include "Objetos\View\ViewObjeto.h"

#ifndef ListaViewConectoresH

// Classe que cria uma lista duplamente encadeada
// de conectores.
struct nodeViewConn
{
  	ViewConector *Conn;
   	struct nodeViewConn *Next;
   	struct nodeViewConn *Prior;
};
typedef struct nodeViewConn *FilaConectores;

class ListaViewConectores
{
    private:
    protected:
       	void RemoveTodosSelecionados();
	public:
        FilaConectores listaPTR, FinalListaPTR;

        ListaViewConectores()
        {
            listaPTR = 0;
            FinalListaPTR = 0;
        }
        ~ListaViewConectores()
        {
            Clear();
        }
        bool ListaVazia();
        void Clear();
        void Esvazia();
        void Apaga(ViewConector *view);
        void InsereLista(ViewConector *Novo);
        bool ExisteConexao(ViewObjeto *O1, ViewObjeto *O2);
        void UnSelectAllConnectors();
        void RemovePorViewObjeto(ViewObjeto *Obj);
};

void ListaViewConectores::Clear()
{
	FilaConectores c, lixo;
    ViewConector *CLixo;
	if(!ListaVazia())
	{
	 	c = listaPTR;
	 	while(c != 0)
   		{
   			CLixo = c->Conn;
   			lixo = c;
   			c = c->Next;
   			delete CLixo, lixo;
  		}
	}
	listaPTR = 0;
    FinalListaPTR = 0;
}

bool ListaViewConectores::ListaVazia()
{
	return (listaPTR == 0);
}

void ListaViewConectores::Esvazia()
{
	FilaConectores c, lixo;
	if(!ListaVazia())
	{
	 	c = listaPTR;
	 	while(c != 0)
        {
			c->Conn->SetSelection(false);
            lixo = c;
            c = c->Next;
            delete lixo;
        }
	}
	listaPTR = 0;
    FinalListaPTR = 0;
}

void ListaViewConectores::InsereLista(ViewConector *Novo)
{
    FilaConectores NovoNode;
    NovoNode = new nodeViewConn;
    NovoNode->Conn = Novo;
    NovoNode->Prior = 0;
    NovoNode->Next = listaPTR;
    if(listaPTR != 0)
        listaPTR->Prior = NovoNode;
    else
        FinalListaPTR = NovoNode;

	listaPTR = NovoNode;
}
void ListaViewConectores::Apaga(ViewConector *view)
{
   	FilaConectores p, q;

   	p=listaPTR;
   	q=0;
   	while(p!=0)
   	{
       	if (p->Conn == view)
       	{
           	if(q == 0) // p é o primeiro Conector da lista
               	listaPTR = p->Next;
           	else
               	q->Next = p->Next;

           	if(p->Next != 0)
            	p->Next->Prior = q;

			if(FinalListaPTR == p) // P é o último
				FinalListaPTR = p->Prior;

	        delete p;
	        break;
		}
        q=p;
        p=p->Next;
	}
}
void ListaViewConectores::RemoveTodosSelecionados()
{
	// Apaga o conector selecionado
   	FilaConectores p, q;

   	p=listaPTR;
   	q=0;
   	while(p!=0)
   	{
       	if (p->Conn->GetSelection())
       	{
           	if(q == 0) // p é o primeiro Conector da lista
               	listaPTR = p->Next;
           	else
               	q->Next = p->Next;

           	if(p->Next != 0)
            	p->Next->Prior = q;

			if(FinalListaPTR == p) // P é o último
				FinalListaPTR = p->Prior;

	        delete p;
	        break;
		}
        q=p;
        p=p->Next;
	}
}
bool ListaViewConectores::ExisteConexao(ViewObjeto *O1, ViewObjeto *O2)
{
	FilaConectores c;
    if(!ListaVazia())
    {
        for(c = listaPTR; c!=0; c = c->Next)
        {
            if((c->Conn->ViewA == O1 && c->Conn->ViewB == O2) || (c->Conn->ViewA == O2 && c->Conn->ViewB == O1))
                return true;
        }
    }
    return false;
}

void ListaViewConectores::RemovePorViewObjeto(ViewObjeto *view)
{
    FilaConectores c;
    TList *ListaDelecao;
    ListaDelecao = new TList();

    if(!ListaVazia())
    {
        for(c = listaPTR; c!=0; c = c->Next)
        {
            if(c->Conn->ViewA == view || c->Conn->ViewB == view)
            {
                if (c->Conn->GetViewPointingAtMe() != NULL)
                {
                    c->Conn->GetViewPointingAtMe()->SetConectorViewEndLine(NULL);
                    ListaDelecao->Add(c->Conn->GetViewPointingAtMe());
                    c->Conn->SetViewPointingAtMe(NULL);
                }

                if (c->Conn->GetConectorViewEndLine() != NULL)
                {
                    c->Conn->GetConectorViewEndLine()->SetViewPointingAtMe(NULL);
                }

                ListaDelecao->Add(c->Conn);
            }
        }
    }

    for(int i = 0; i < ListaDelecao->Count; i++)
    {
        Apaga((ViewConector*)ListaDelecao->Items[i]);
    }

    delete ListaDelecao;
}

void ListaViewConectores::UnSelectAllConnectors()
{
    FilaConectores c;
    if(!ListaVazia())
    {
        for(c = listaPTR; c!=0; c = c->Next)
        {
            (c->Conn)->SetSelection(false);
        }
    }
}
#define ListaViewConectoresH
#endif