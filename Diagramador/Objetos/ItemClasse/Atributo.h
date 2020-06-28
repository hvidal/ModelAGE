#include "Objetos\ItemClasse\ItemClasse.h"

#ifndef AtributoH

class Atributo: public ItemClasse
{
	private:
    	AnsiString *ValorInicial;
    protected:
    public:
        Atributo()
        {
			ValorInicial = new AnsiString;

            // Default            
            *ValorInicial = "";
        }
        ~Atributo()
        {
        	delete ValorInicial;
        }

        // Getters
		AnsiString GetValorInicial();
        AnsiString GetAssinaturaUML();

        //Setters
        void SetValorInicial(AnsiString novoValorInicial);

        // Clone()
        Atributo* Clone();
};
AnsiString Atributo::GetValorInicial()
{
	return *ValorInicial;
}
void Atributo::SetValorInicial(AnsiString novoValorInicial)
{
	*ValorInicial = novoValorInicial;
}
AnsiString Atributo::GetAssinaturaUML()
{
	// Função que retorna a assinatura UML do atributo
    // UML: "visibility name: type-expression = Initial-Value { Property-String}"

	AnsiString assinatura;

    assinatura = GetNome();
    if(GetTipo() != "")
    {
	    assinatura += ": ";
	    assinatura += GetTipo();
    }
    if(GetValorInicial() != "")
    {
	    assinatura += " = ";
	    assinatura += GetValorInicial();
    }
    if(GetPropertyString() != "")
    {
	    assinatura += " {";
	    assinatura += GetPropertyString();
	    assinatura += "}";
    }

    return assinatura;
}
Atributo* Atributo::Clone()
{
    Atributo *clone;
    clone = new Atributo();

    // Propriedades do ItemClasse
    clone->SetNome(GetNome());
    clone->SetTipo(GetTipo());
    clone->SetEstereotipo(GetEstereotipo());
    clone->SetPropertyString(GetPropertyString());
    clone->SetVisibilidade(GetVisibilidade());
    clone->SetDocumentacao(GetDocumentacao());

    // Propriedades do atributo
    clone->SetValorInicial(GetValorInicial());
    return clone;
}
#define AtributoH
#endif

