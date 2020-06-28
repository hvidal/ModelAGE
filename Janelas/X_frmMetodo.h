//---------------------------------------------------------------------------
#ifndef X_frmMetodoH
#define X_frmMetodoH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ComCtrls.hpp>
#include "X_frmItemClasse.h"
#include "Grids.hpp"

#include "Objetos\ItemClasse\Metodo.h"
#include <vcl\Menus.hpp>
//---------------------------------------------------------------------------
class TfrmMetodo : public TfrmItemClasse
{
__published:	// IDE-managed Components
	TTabSheet *ts_Argumentos;
	TTabSheet *ts_Conditions;
	TLabel *lb_PreConditions;
	TLabel *lb_PostConditions;
	TMemo *mm_PreConditions;
	TMemo *mm_PostConditions;
	TCheckBox *cbx_Abstract;
	TStringGrid *sg_Argumentos;
	TLabel *lb_Virtual;
	TBevel *bv_Divisor;
	TPopupMenu *ppmArgumentos;
	TMenuItem *mnuInsert;
	TMenuItem *mnuDelete;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall mnuDeleteClick(TObject *Sender);
	void __fastcall mnuInsertClick(TObject *Sender);
        void __fastcall sg_ArgumentosSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall sg_ArgumentosSetEditText(TObject *Sender, int ACol,
          int ARow, const AnsiString Value);
    void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
	int LinhaSelecionadaGridArgumentos;
	TList *ListaArgumentos;
	void PreparaGridArgumentos();
	void RefreshGridArgumentos();    
public:		// User declarations
	void SetListaArgumentos(TList *lista);
    void SetValores(Metodo *metodo);
    void GetValores(Metodo *metodo);

	__fastcall TfrmMetodo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TfrmMetodo *frmMetodo;
//---------------------------------------------------------------------------
#endif
