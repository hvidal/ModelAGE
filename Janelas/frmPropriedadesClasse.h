//---------------------------------------------------------------------------
#ifndef frmPropriedadesClasseH
#define frmPropriedadesClasseH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include "frmPropriedadesObjeto.h"
#include "Grids.hpp"
#include <vcl\Menus.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmClassProperties : public TfrmObjectProperties
{
__published:	// IDE-managed Components
    TLabel *lb_Documentation;
    TMemo *mm_Documentation;
    TLabel *lb_Stereotype;
    TComboBox *cb_Stereotype;
    TTabSheet *ts_Attributes;
    TStringGrid *sg_Atributos;
    TTabSheet *ts_Operations;
    TStringGrid *sg_Metodos;
    TImageList *ClassImages;
    TPopupMenu *ppmAtributos;
    TMenuItem *mnuInsertAtributo;
    TMenuItem *mnuDeleteAtributo;
    TMenuItem *mnuN1;
    TMenuItem *mnuSpecificationAtributo;
    TPopupMenu *ppmMetodos;
    TMenuItem *mnuSpecificationMetodo;
    TMenuItem *MenuItem2;
    TMenuItem *mnuInsertMetodo;
    TMenuItem *mnuDeleteMetodo;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall mnuInsertAtributoClick(TObject *Sender);
    void __fastcall mnuDeleteAtributoClick(TObject *Sender);
    void __fastcall mnuInsertMetodoClick(TObject *Sender);
    void __fastcall mnuDeleteMetodoClick(TObject *Sender);
    void __fastcall mnuSpecificationAtributoClick(TObject *Sender);
    void __fastcall mnuSpecificationMetodoClick(TObject *Sender);
    void __fastcall sg_AtributosSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect);
    void __fastcall sg_MetodosSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect);
    void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
    int LinhaSelecionadaGridAtributos;
    int LinhaSelecionadaGridMetodos;

    TList *ListaAtributos;
    TList *ListaMetodos;

    void PreparaGridAtributos();
    void PreparaGridMetodos();
public:		// User declarations

    void SetListaAtributos(TList *lista);
    void SetListaMetodos(TList *lista);
    TList* GetListaAtributos();
    TList* GetListaMetodos();

    void RefreshGridAtributos();
    void RefreshGridMetodos();

    void SetStereotype(AnsiString stereotype);
    AnsiString GetStereotype();

    void SetDocumentation(TStringList *documentation);
    TStrings* GetDocumentation();

    __fastcall TfrmClassProperties(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TfrmClassProperties *frmClassProperties;
//---------------------------------------------------------------------------
#endif

