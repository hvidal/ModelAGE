#include "Objetos\Objeto.h"

#include "Pintor\PartesObjeto\FormaClasse.h"

#include "Objetos\ItemClasse\Metodo.h"
#include "Objetos\ItemClasse\Atributo.h"

#ifndef ObjClasseH

class ObjClasse: public Objeto
{
    AnsiString *Stereotype;
 public:
    TList *listaAtributos;
    TList *listaMetodos;

    ObjClasse(int _Type, int _Id): Objeto(_Type, _Id)
    {
    	Stereotype = new AnsiString;
        listaAtributos = new TList();
        listaMetodos = new TList();
    }
    ~ObjClasse()
    {
    	delete Stereotype;
        delete listaAtributos, listaMetodos;
    }

    void SetStereotype(AnsiString stereotype);
    AnsiString GetStereotype();
    AnsiString GetStringStereotype();

    void InsereAtributo(Atributo *novo);
    void InsereMetodo(Metodo *novo);

    Atributo* GetAtributo(int Indice);
    Metodo* GetMetodo(int Indice);
    TList* GetListaAtributos();
    TList* GetListaMetodos();
    void SetListaAtributos(TList *lista);
    void SetListaMetodos(TList *lista);

    void EsvaziaAtributos();
    void EsvaziaMetodos();

	void Salva(int Ordem, TIniFile *INITIAL);
	void Carrega(int Ordem, TIniFile *INITIAL);
};

void ObjClasse::SetStereotype(AnsiString stereotype)
{
	*Stereotype = stereotype;
}
AnsiString ObjClasse::GetStereotype()
{
	return *Stereotype;
}
AnsiString ObjClasse::GetStringStereotype()
{
	return ("<<" + *Stereotype + ">>");
}
void ObjClasse::SetListaAtributos(TList *lista)
{
    listaAtributos->Clear();
    for(int i=0; i < lista->Count; i++)
        listaAtributos->Add(((Atributo*)lista->Items[i])->Clone());
}
void ObjClasse::SetListaMetodos(TList *lista)
{
    listaMetodos->Clear();
    for(int i=0; i < lista->Count; i++)
        listaMetodos->Add(((Metodo*)lista->Items[i])->Clone());
}
void ObjClasse::InsereAtributo(Atributo *novo)
{
	listaAtributos->Add(novo);
}
void ObjClasse::InsereMetodo(Metodo *novo)
{
    listaMetodos->Add(novo);
}
Atributo* ObjClasse::GetAtributo(int Indice)
{
	Atributo *atributo;
    atributo = (Atributo*)listaAtributos->Items[Indice];
	return atributo;
}
Metodo* ObjClasse::GetMetodo(int Indice)
{
	Metodo *metodo;
    metodo = (Metodo*)listaMetodos->Items[Indice];
	return metodo;
}
TList* ObjClasse::GetListaAtributos()
{
	return listaAtributos;
}
TList* ObjClasse::GetListaMetodos()
{
	return listaMetodos;
}
void ObjClasse::EsvaziaAtributos()
{
	listaAtributos->Clear();
}
void ObjClasse::EsvaziaMetodos()
{
	listaMetodos->Clear();
}
void ObjClasse::Salva(int Ordem, TIniFile *INITIAL)
{
/*
	int cont;
    Atributo *atributo;
    Metodo *metodo;

    SalvaObjeto(Ordem, INITIAL);

    INITIAL->WriteBool("Objeto" + AnsiString(Ordem), "Hide", *Hide);
    INITIAL->WriteInteger("Objeto" + AnsiString(Ordem), "NAttr", listaAtributos->Count);
    INITIAL->WriteInteger("Objeto" + AnsiString(Ordem), "NMeth", listaMetodos->Count);

    for(cont = 0; cont < listaAtributos->Count; cont++)
    {
    	atributo = GetAtributo(cont);
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "Attr" + AnsiString(cont), atributo->GetNome());
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "AttrT" + AnsiString(cont), atributo->GetTipo());
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "AttrV" + AnsiString(cont), atributo->GetVisibilidade());
    }
    for(cont = 0; cont < listaMetodos->Count; cont++)
    {
    	metodo = GetMetodo(cont);
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "Meth" + AnsiString(cont), metodo->GetNome());
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "MethT" + AnsiString(cont), metodo->GetTipo());
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "MethV" + AnsiString(cont), metodo->GetVisibilidade());
    }
*/
}
void ObjClasse::Carrega(int Ordem, TIniFile *INITIAL)
{
/*
	int cont, Qtd;
    AnsiString Nome, Tipo, Visibilidade;
    Atributo *atributo;
    Metodo *metodo;

    CarregaObjeto(Ordem, INITIAL);

    *Hide = INITIAL->ReadBool("Objeto" + AnsiString(Ordem), "Hide", false);

    Qtd = INITIAL->ReadInteger("Objeto" + AnsiString(Ordem),"NAttr", 0);
    for(cont = 0; cont < Qtd; cont++)
    {
    	atributo = new Atributo();
    	Nome = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "Attr" + AnsiString(cont), ""));
        atributo->SetNome(Nome);

        Tipo = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "AttrT" + AnsiString(cont), ""));
        atributo->SetTipo(Tipo);

        Visibilidade = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "AttrV" + AnsiString(cont), ""));
        atributo->SetVisibilidade(atributo->GetIndexVisibilidade(Visibilidade));

        InsereAtributo(atributo);
    }

    Qtd = INITIAL->ReadInteger("Objeto" + AnsiString(Ordem),"NMeth", 0);
    for(cont = 0; cont < Qtd; cont++)
    {
    	metodo = new Metodo();

    	Nome = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "Meth" + AnsiString(cont), ""));
        metodo->SetNome(Nome);

        Tipo = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "MethT" + AnsiString(cont), ""));
        metodo->SetTipo(Tipo);

        Visibilidade = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "MethV" + AnsiString(cont), ""));
        metodo->SetVisibilidade(metodo->GetIndexVisibilidade(Visibilidade));

        InsereMetodo(metodo);
    }
*/
}
#define ObjClasseH
#endif