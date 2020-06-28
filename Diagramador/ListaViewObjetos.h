#include "Objetos\View\ViewObjeto.h"

#ifndef ListaViewObjetosH

// Classe que cria uma lista duplamente encadeada
// de views de objetos.
struct nodeViewObj
{
   	ViewObjeto *Obj;
   	struct nodeViewObj *Next;
   	struct nodeViewObj *Prior;
};
typedef struct nodeViewObj *FilaObjetos;

class ListaViewObjetos
{
	public:
	FilaObjetos listaPTR, FinalListaPTR;

	ListaViewObjetos()
	{
		listaPTR = 0;
		FinalListaPTR = 0;
	}
	~ListaViewObjetos()
	{
    	Clear();
	}
	bool ListaVazia();
    void Clear();
	void Esvazia();
    bool buscaObjeto(int ID);
	void InsereLista(ViewObjeto *Novo);
	void RemoveLista(ViewObjeto *VaiMorrer);
};
void ListaViewObjetos::Clear()
{
	FilaObjetos p, lixo;
    ViewObjeto *OLixo;
	if(!ListaVazia())
	{
	 	p = listaPTR;
	 	while(p != 0)
        {
        	OLixo = p->Obj;
       		lixo = p;
            p = p->Next;
       		delete OLixo, lixo;
        }
	}
	listaPTR = 0;
    FinalListaPTR = 0;
}
void ListaViewObjetos::Esvazia()
{
	FilaObjetos p, lixo;
	if(!ListaVazia())
	{
	 	p = listaPTR;
	 	while(p != 0)
        {
			*p->Obj->isSelected = false;
		    *p->Obj->GroupSelected = false;
            lixo = p;
            p = p->Next;
            delete lixo;
        }
	}
	listaPTR = 0;
    FinalListaPTR = 0;
}
bool ListaViewObjetos::buscaObjeto(int id)
{
	FilaObjetos p;
	for(p = listaPTR; p != 0; p = p->Next)
    {
    	if(p->Obj->GetCorpo()->GetId() == id)
        	return true;
    }
    return false;
}
bool ListaViewObjetos::ListaVazia()
{
	return (listaPTR == 0);
}

void ListaViewObjetos::InsereLista(ViewObjeto *Novo)
{
	FilaObjetos NovoNode;
   	NovoNode = new nodeViewObj;
   	NovoNode->Obj = Novo;
   	NovoNode->Prior = 0;
   	NovoNode->Next = listaPTR;
   	if(listaPTR != 0)
		listaPTR->Prior = NovoNode;
   	else
   		FinalListaPTR = NovoNode;

	listaPTR = NovoNode;
}
void ListaViewObjetos::RemoveLista(ViewObjeto *VaiMorrer)
{
	// Apaga o objeto selecionado

   	FilaObjetos p, q;

  	p=listaPTR;
   	q=0;
   	while(p!=0)
   	{
       	if (p->Obj == VaiMorrer)
       	{
          	if(q == 0) // p é o primeiro Objeto da lista
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

#define ListaViewObjetosH
#endif