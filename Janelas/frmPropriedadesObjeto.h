//---------------------------------------------------------------------------
#ifndef frmPropriedadesObjetoH
#define frmPropriedadesObjetoH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TfrmObjectProperties : public TForm
{
__published:	// IDE-managed Components
	TPageControl *pc_ObjectProperties;
	TTabSheet *ts_General;
	TPanel *Panel1;
	TBitBtn *btnOK;
	TBitBtn *btnCancelar;
	TLabel *lb_Name;
	TEdit *ed_Name;
	void __fastcall btnCancelarClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
private:	// User declarations
	int Result;
public:		// User declarations
	int ResultOK();

	void SetObjectName(AnsiString name);
	AnsiString GetObjectName();

	__fastcall TfrmObjectProperties(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TfrmObjectProperties *frmObjectProperties;
//---------------------------------------------------------------------------
#endif
