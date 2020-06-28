//---------------------------------------------------------------------------
#ifndef frmDomainH
#define frmDomainH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmDominio : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PG;
	TTabSheet *Definition;
	TMemo *CDescription;
	TTabSheet *Attributes;
	TTabSheet *Methods;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TTabSheet *TabSheet1;
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *Edit1;
	TLabel *Label2;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmDominio(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TfrmDominio *frmDominio;
//---------------------------------------------------------------------------
#endif
