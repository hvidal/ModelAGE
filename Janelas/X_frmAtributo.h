//---------------------------------------------------------------------------
#ifndef X_frmAtributoH
#define X_frmAtributoH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ComCtrls.hpp>

#include "X_frmItemClasse.h"

#include "Objetos\ItemClasse\Atributo.h"
//---------------------------------------------------------------------------
class TfrmAtributo : public TfrmItemClasse
{
__published:	// IDE-managed Components
	TEdit *ed_InitialValue;
	TLabel *lb_InitialValue;
private:	// User declarations
public:		// User declarations
    void SetValores(Atributo *atributo);
    void GetValores(Atributo *atributo);

	__fastcall TfrmAtributo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TfrmAtributo *frmAtributo;
//---------------------------------------------------------------------------
#endif
