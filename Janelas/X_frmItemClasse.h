//---------------------------------------------------------------------------
#ifndef X_frmItemClasseH
#define X_frmItemClasseH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ComCtrls.hpp>
//---------------------------------------------------------------------------

#include "Objetos\ItemClasse\ItemClasse.h"

class TfrmItemClasse : public TForm
{
__published:	// IDE-managed Components
	TPanel *pn_Botoes;
	TBitBtn *btnOK;
	TBitBtn *btnCancelar;
	TPageControl *pc_Dados;
	TTabSheet *ts_General;
	TLabel *lb_Name;
	TLabel *lb_Type;
	TLabel *lb_Stereotype;
	TLabel *lb_PropertyString;
	TLabel *lb_Documentation;
	TEdit *ed_Name;
	TEdit *ed_PropertyString;
	TComboBox *cb_Stereotype;
	TComboBox *cb_Type;
	TGroupBox *gb_Visibility;
	TRadioButton *rb_Private;
	TRadioButton *rb_Public;
	TRadioButton *rb_Protected;
	TMemo *mm_Documentation;
	void __fastcall btnCancelarClick(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
private:	// User declarations
    int Result;
protected:
    void SetValores(ItemClasse *itemClasse);
    void GetValores(ItemClasse *itemClasse);

    void SetVisibilidade(int visibilidade);
    int GetVisibilidade();
public:		// User declarations
    int ResultOK();
    __fastcall TfrmItemClasse(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmItemClasse *frmItemClasse;
//---------------------------------------------------------------------------
#endif
