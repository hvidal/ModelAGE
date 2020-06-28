#ifndef ItemClasseH

#define Vis_PRIVATE   1
#define Vis_PROTECTED 2
#define Vis_PUBLIC    3

class ItemClasse
{
	private:
    	AnsiString *Nome, *Tipo, *Estereotipo, *PropertyString;
        TStringList *Documentacao;
        int *Visibilidade;
    protected:
    public:
        ItemClasse()
        {
            Nome = new AnsiString;
            Tipo = new AnsiString;
            Visibilidade = new int;
            Estereotipo = new AnsiString;
            Documentacao = new TStringList();
            PropertyString = new AnsiString;

            // Default
            *Nome = "";
            *Tipo = "";
            *Visibilidade = Vis_PRIVATE;
            *Estereotipo = "";
            *PropertyString = "";
        }
        ~ItemClasse()
        {
            delete Nome, Tipo, Visibilidade, Documentacao;
            delete Estereotipo, PropertyString;
        }

        // Getters
        AnsiString GetNome();
        AnsiString GetTipo();
        AnsiString GetEstereotipo();
        AnsiString GetPropertyString();
        int GetVisibilidade();
        TStringList* GetDocumentacao();

        AnsiString GetStringVisibilidade();
        AnsiString GetCharVisibilidade();

        int GetIndexVisibilidade(AnsiString CharVisibilidade);

        // Setters
        void SetNome(AnsiString novoNome);
        void SetTipo(AnsiString novoTipo);
        void SetEstereotipo(AnsiString novoEstereotipo);
        void SetPropertyString(AnsiString novaPropertyString);
        void SetVisibilidade(int novaVisibilidade);
        void SetDocumentacao(TStringList *novaDocumentacao);

        // Virtual
    	virtual AnsiString GetAssinaturaUML()=0;
};
AnsiString ItemClasse::GetNome()
{
	return *Nome;
}
AnsiString ItemClasse::GetTipo()
{
	return *Tipo;
}
AnsiString ItemClasse::GetEstereotipo()
{
	return *Estereotipo;
}
AnsiString ItemClasse::GetPropertyString()
{
	return *PropertyString;
}
int ItemClasse::GetVisibilidade()
{
	return *Visibilidade;
}
void ItemClasse::SetNome(AnsiString novoNome)
{
	*Nome = novoNome;
}
void ItemClasse::SetTipo(AnsiString novoTipo)
{
	*Tipo = novoTipo;
}
void ItemClasse::SetEstereotipo(AnsiString novoEstereotipo)
{
	*Estereotipo = novoEstereotipo;
}
void ItemClasse::SetPropertyString(AnsiString novaPropertyString)
{
	*PropertyString = novaPropertyString;
}
void ItemClasse::SetVisibilidade(int novaVisibilidade)
{
	*Visibilidade = novaVisibilidade;
}
TStringList* ItemClasse::GetDocumentacao()
{
	return Documentacao;
}
void ItemClasse::SetDocumentacao(TStringList *novaDocumentacao)
{
	Documentacao->Assign(novaDocumentacao);
}
AnsiString ItemClasse::GetStringVisibilidade()
{
	AnsiString Retorno;
	if (*Visibilidade == Vis_PRIVATE)
    	Retorno = "Private";
    else if (*Visibilidade == Vis_PROTECTED)
    	Retorno = "Protected";
    else
    	Retorno = "Public";
    return Retorno;
}
AnsiString ItemClasse::GetCharVisibilidade()
{
	AnsiString Retorno;
	if (*Visibilidade == Vis_PRIVATE)
    	Retorno = "-";
    else if (*Visibilidade == Vis_PROTECTED)
    	Retorno = "#";
    else
    	Retorno = "+";
    return Retorno;
}
int ItemClasse::GetIndexVisibilidade(AnsiString CharVisibilidade)
{
	int Retorno;
	if (CharVisibilidade == "-")
    	Retorno = Vis_PRIVATE;
    else if (CharVisibilidade == "+")
    	Retorno = Vis_PROTECTED;
    else
    	Retorno = Vis_PUBLIC;
    return Retorno;
}
#define ItemClasseH
#endif