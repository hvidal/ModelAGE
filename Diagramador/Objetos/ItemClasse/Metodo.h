#include "Objetos\ItemClasse\ItemClasse.h"

#ifndef MetodoH

// CLASSE: Argumento
class Argumento
{
	private:
    	AnsiString *Nome, *Tipo, *Default, *Documentation;
	public:
        Argumento()
        {
        	Nome = new AnsiString;
        	Tipo = new AnsiString;
        	Default = new AnsiString;
        	Documentation = new AnsiString;
        }
        ~Argumento()
        {
        	delete Nome, Tipo, Default, Documentation;
        }

        // Setters
        void SetNome(AnsiString novoNome)
        {
        	*Nome = novoNome;
        }
        void SetTipo(AnsiString novoTipo)
        {
        	*Tipo = novoTipo;
        }
        void SetDefault(AnsiString novoDefault)
        {
        	*Default = novoDefault;
        }
        void SetDocumentation(AnsiString novaDocumentation)
        {
        	*Documentation = novaDocumentation;
        }

        // Getters
        AnsiString GetNome()
        {
        	return *Nome;
        }
        AnsiString GetTipo()
        {
        	return *Tipo;
        }
        AnsiString GetDefault()
        {
        	return *Default;
        }
        AnsiString GetDocumentation()
        {
        	return *Documentation;
        }

        Argumento* Clone()
        {
            Argumento *clone;
            clone = new Argumento();
            clone->SetNome(GetNome());
            clone->SetTipo(GetTipo());
            clone->SetDefault(GetDefault());
            clone->SetDocumentation(GetDocumentation());
            return clone;
        }
};

// CLASSE: Metodo
class Metodo: public ItemClasse
{
	private:
        TStringList *PreCondicoes, *PosCondicoes;
        TList *ListaArgumentos;
        bool *Abstract;
    protected:
    public:
        Metodo()
        {
            PreCondicoes = new TStringList();
            PosCondicoes = new TStringList();
            ListaArgumentos = new TList();
            Abstract = new bool;

            // Default
            *Abstract = false;
        }
        ~Metodo()
        {
        	delete PreCondicoes, PosCondicoes, Abstract;
            ListaArgumentos->Clear();
            delete ListaArgumentos;
        }

        // Getters
        TStringList* GetPreCondicoes();
        TStringList* GetPosCondicoes();
        bool IsAbstract();

        // Setters
        void SetPreCondicoes(TStringList *novaPreCondicoes);
        void SetPosCondicoes(TStringList *novaPosCondicoes);
        void SetAbstract(bool abstract);

        // Serviços
        TList* GetListaArgumentos();
        AnsiString GetAssinaturaUML();

        Metodo* Clone();
};
bool Metodo::IsAbstract()
{
	return *Abstract;
}
void Metodo::SetAbstract(bool abstract)
{
	*Abstract = abstract;
}
TStringList* Metodo::GetPreCondicoes()
{
	return PreCondicoes;
}
TStringList* Metodo::GetPosCondicoes()
{
	return PosCondicoes;
}
void Metodo::SetPreCondicoes(TStringList *novaPreCondicoes)
{
	PreCondicoes->Assign(novaPreCondicoes);
}
void Metodo::SetPosCondicoes(TStringList *novaPosCondicoes)
{
	PosCondicoes->Assign(novaPosCondicoes);
}
TList* Metodo::GetListaArgumentos()
{
	return ListaArgumentos;
}
AnsiString Metodo::GetAssinaturaUML()
{
	// Função que retorna a assinatura UML do método
    // UML: "visibility name( parameter-list ): return-type { Property-String}"
    // parameter: "name: type-expression = default-value"

	AnsiString assinatura;
    Argumento *argumento;
	int i;

    assinatura = GetNome();
    assinatura += "(";
    for(i=0; i < ListaArgumentos->Count; i++)
    {
		argumento = (Argumento*)ListaArgumentos->Items[i];
	    assinatura += argumento->GetNome();
        if(argumento->GetTipo() != "")
        {
		    assinatura += ": ";
		    assinatura += argumento->GetTipo();
        }
        if(argumento->GetDefault() != "")
        {
		    assinatura += "= ";
		    assinatura += argumento->GetDefault();
        }

        if (i != ListaArgumentos->Count-1)
        {
		    assinatura += ", ";
        }
    }
    assinatura += ")";
    if (GetTipo() != "")
    {
	    assinatura += ": ";
	    assinatura += GetTipo();
    }

    return assinatura;
}
Metodo* Metodo::Clone()
{
    Metodo *clone;
    clone = new Metodo();

    // Propriedades do ItemClasse
    clone->SetNome(GetNome());
    clone->SetTipo(GetTipo());
    clone->SetEstereotipo(GetEstereotipo());
    clone->SetPropertyString(GetPropertyString());
    clone->SetVisibilidade(GetVisibilidade());
    clone->SetDocumentacao(GetDocumentacao());

    // Propriedades do metodo
    clone->SetPreCondicoes(GetPreCondicoes());
    clone->SetPosCondicoes(GetPosCondicoes());
    clone->SetAbstract(IsAbstract());

    for(int i=0; i < GetListaArgumentos()->Count; i++)
    {
        clone->GetListaArgumentos()->Add(((Argumento*)GetListaArgumentos()->Items[i])->Clone());
    }

    return clone;
}
#define MetodoH
#endif

