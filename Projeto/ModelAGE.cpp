//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("ModelAGE.res");
USEFORM("Main.cpp", Base);
USEFORM("..\Janelas\X_frm_PainelDiagramador.cpp", frmPainelDiagramador);
USEFORM("..\Janelas\frmPropriedadesObjeto.cpp", frmObjectProperties);
USEFORM("..\Janelas\Sobre.cpp", About);
USEFORM("..\Janelas\Splash.cpp", frmSplash);
USEFORM("..\Janelas\frmDomain.cpp", frmDominio);
USEFORM("..\Janelas\X_frmItemClasse.cpp", frmItemClasse);
USEFORM("..\Janelas\X_frmMetodo.cpp", frmMetodo);
USEFORM("..\Janelas\X_frmAtributo.cpp", frmAtributo);
USEFORM("..\Janelas\frmPropriedadesClasse.cpp", frmClassProperties);
USE("ModelAGE.todo", ToDo);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->Title = "ModelAGE v1.0";
         Application->CreateForm(__classid(TBase), &Base);
                 Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
