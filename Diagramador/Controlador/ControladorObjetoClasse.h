#include "Interfaces\IControladorObjeto.h"
#include "Objetos\ObjClasse.h"

#include "frmPropriedadesClasse.h"

#ifndef ControladorObjetoClasseH
#define ControladorObjetoClasseH

#define MaxLinhas 200

class ControladorObjetoClasse: public IControladorObjeto
{
	private:
    	TfrmClassProperties *thisForm;
    	void MontaJanela(Objeto *objeto);
        void SalvaDados(Objeto *objeto);
        void Aloca();
        void Desaloca();
    protected:
    public:
        bool Execute(Objeto *objeto);
        void EfetuaAjustesView(ViewObjeto *view, TPaintBox *Board);        
};
void ControladorObjetoClasse::Aloca()
{
    thisForm = new TfrmClassProperties(Application);
}
void ControladorObjetoClasse::Desaloca()
{
    delete thisForm;
}
void ControladorObjetoClasse::EfetuaAjustesView(ViewObjeto *view, TPaintBox *Board)
{
    ViewObjClasse *viewClasse;
    viewClasse = (ViewObjClasse *)view;
    viewClasse->AjustaNome(Board);
    viewClasse->SetHeight(Board->Canvas);
}
void ControladorObjetoClasse::MontaJanela(Objeto *objeto)
{
    ObjClasse *classe;
    classe = (ObjClasse*)objeto;

    // Preenche com os valores atuais...
    thisForm->SetObjectName(classe->GetName());
    thisForm->SetStereotype(classe->GetStereotype());
    thisForm->SetDocumentation(classe->GetDocumentation());

    thisForm->SetListaAtributos(classe->GetListaAtributos());
    thisForm->SetListaMetodos(classe->GetListaMetodos());
}
void ControladorObjetoClasse::SalvaDados(Objeto *objeto)
{
    ObjClasse *classe;
    classe = (ObjClasse*)objeto;

    if(thisForm->ResultOK()) // Botão OK
    {
        // Apago o conteúdo antigo
        classe->GetListaAtributos()->Clear();
        classe->GetListaMetodos()->Clear();

        // Coloco o conteúdo novo
        classe->SetListaAtributos(thisForm->GetListaAtributos());
        classe->SetListaMetodos(thisForm->GetListaMetodos());

	    classe->SetName(thisForm->GetObjectName());
        classe->SetStereotype(thisForm->GetStereotype());
        classe->SetDocumentation((TStringList*)thisForm->GetDocumentation());

        // Apago o conteúdo temporário
        thisForm->GetListaAtributos()->Clear();
        thisForm->GetListaMetodos()->Clear();
    }
}
bool ControladorObjetoClasse::Execute(Objeto *objeto)
{
    bool Resultado;

    Aloca();
    MontaJanela(objeto);
    thisForm->ShowModal();
    SalvaDados(objeto);
    Resultado = thisForm->ResultOK();
    Desaloca();

    return Resultado;
}
#endif
