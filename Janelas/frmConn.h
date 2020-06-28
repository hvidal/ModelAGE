//---------------------------------------------------------------------------
#ifndef frmConnH
#define frmConnH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmConnProp : public TForm
{
__published:	// IDE-managed Components
	TLabel *Flag;
	TBitBtn *btnOK;
	TBitBtn *btnCancelar;
	TLabel *Label1;
	TGroupBox *Position;
	TShape *Shape1;
	TShape *Shape2;
	TLabel *Label2;
	TLabel *Source;
	TLabel *Label3;
	TRichEdit *Name;
	TGroupBox *GroupBox1;
	TRadioButton *rb_Left;
	TRadioButton *rb_Center;
	TRadioButton *rb_Right;
	TRadioButton *opt1;
	TRadioButton *opt2;
	TRadioButton *optM;
	TRadioButton *opt5;
	TRadioButton *opt4;
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall btnCancelarClick(TObject *Sender);
	
	
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmConnProp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TfrmConnProp *frmConnProp;
//---------------------------------------------------------------------------
#endif
