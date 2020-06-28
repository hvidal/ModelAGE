//---------------------------------------------------------------------------
#ifndef SplashH
#define SplashH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmSplash : public TForm
{
__published:	// IDE-managed Components
	TShape *Shape1;
	TTimer *Timer1;
	TImage *Image1;
        TProgressBar *f;
        TLabel *lb_Info;
	void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmSplash(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TfrmSplash *frmSplash;
//---------------------------------------------------------------------------
#endif
