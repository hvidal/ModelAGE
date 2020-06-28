//---------------------------------------------------------------------------

#ifndef X_frm_PainelDiagramadorH
#define X_frm_PainelDiagramadorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

#include "Diagrama.h"
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmPainelDiagramador : public TForm
{
__published:	// IDE-managed Components
    TPageControl *pc_Diagram;
    TTabSheet *ts_Diagram;
    TPanel *pnlClass;
    TPanel *pnlUseCases;
    TPanel *pnlSequence;
    TPanel *pnlEstados;
    TScrollBox *sbArea;
    TPaintBox *BBoard;
    TTabSheet *ts_Detail;
    TPanel *pn_Details;
    TLabel *Label2;
    TLabel *Label4;
    TLabel *lb_LastModified;
    TGroupBox *GroupBox1;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TEdit *ed_HSize;
    TEdit *ed_VSize;
    TButton *btnApply;
    TMemo *mm_Description;
    TPopupMenu *pmPropriedadesConector;
    TMenuItem *mnuConnectorSpecification;
    TMenuItem *mnuConnectorDeleteFromDiagram;
    TMenuItem *mnuConnectorSelectAll;
    TMenuItem *N5;
    TMenuItem *mnuConnectorSaveDiagram;
    TMenuItem *mnuConnectorRefresh;
    TMenuItem *N6;
    TMenuItem *mnuConnectorFormat;
    TMenuItem *mnuConnectorLineColor;
    TMenuItem *N8;
    TMenuItem *mnuConnectorPrint;
    TPopupMenu *pmPropriedadesGerais;
    TMenuItem *mnuSelectAll;
    TMenuItem *mnuSaveDiagram;
    TMenuItem *mnuRefresh;
    TMenuItem *N9;
    TMenuItem *mnuPrint;
    TPopupMenu *pmPropriedadesObjeto;
    TMenuItem *mnuObjectSpecification;
    TMenuItem *mnuObjectDeleteFromDiagram;
    TMenuItem *mnuObjectSelectAll;
    TMenuItem *mnuObjectHideDetails;
    TMenuItem *N2;
    TMenuItem *mnuObjectSaveDiagram;
    TMenuItem *mnuObjectRefresh;
    TMenuItem *N1;
    TMenuItem *mnuObjectFormat;
    TMenuItem *mnuObjectFillColor;
    TMenuItem *mnuObjectLineColor;
    TMenuItem *N4;
    TMenuItem *mnuObjectFont;
    TMenuItem *N3;
    TMenuItem *mnuObjectPrint;
    TSaveDialog *SaveDialog;
    TColorDialog *ColorDialog;
    TFontDialog *FontDialog;
    TPopupMenu *pmPropriedadesGrupo;
    TMenuItem *mnuGrupoDeleteFromDiagram;
    TMenuItem *mnuGrupoSelectAll;
    TMenuItem *mnuGrupoAlign;
    TMenuItem *mnuGrupoAlignLeft;
    TMenuItem *mnuGrupoAlignRight;
    TMenuItem *mnuGrupoAlignTop;
    TMenuItem *mnuGrupoAlignBottom;
    TMenuItem *mnuGrupoFormat;
    TMenuItem *mnuGrupoFormatFillColor;
    TMenuItem *mnuGrupoFormatLineColor;
    TMenuItem *N12;
    TMenuItem *mnuGrupoFormatFont;
    TMenuItem *N11;
    TMenuItem *mnuGrupoSaveDiagram;
    TMenuItem *mnuGrupoRefresh;
    TMenuItem *N10;
    TMenuItem *mnuGrupoPrint;
    TActionList *ActionList;
    TAction *actOpenSpecification;
    TAction *actInsereObjetoClasse;
    TAction *actInsereObjetoComentario;
    TAction *actInsereObjetoEstado;
    TAction *actInsereObjetoEstadoInicial;
    TAction *actInsereConectorHeranca;
    TAction *actInsereConectorAssociacao;
    TAction *actInsereConectorDependencia;
    TAction *actInsereConectorAssociativo;
    TAction *actResetPointer;
    TImageList *il_Diagram;
    TSpeedButton *spb_DClassePointer;
    TSpeedButton *spb_DClasseComentario;
    TAction *actInsereObjetoEstadoFinal;
    TAction *actInsereObjetoAtor;
    TSpeedButton *spb_DClasseClasse;
    TSpeedButton *spb_DClasseAssociacao;
    TSpeedButton *spb_DClasseAgregacao;
    TSpeedButton *spb_DClasseAssociativo;
    TSpeedButton *spb_DClassePacote;
    TSpeedButton *spb_DClasseDependencia;
    TSpeedButton *spb_DClasseHeranca;
    TSpeedButton *spb_DClasseABC;
    TSpeedButton *spb_DClasseNoteLink;
    TSpeedButton *spb_DCasoUsoPointer;
    TSpeedButton *spb_DCasoUsoPacote;
    TSpeedButton *spb_DCasoUsoABC;
    TSpeedButton *spb_DCasoUsoComentario;
    TSpeedButton *spb_DCasoUsoNoteLink;
    TSpeedButton *spb_DCasoUsoDependencia;
    TSpeedButton *spb_DCasoUsoHeranca;
    TSpeedButton *spb_DCasoUsoAtor;
    TSpeedButton *spb_DCasoUsoCasoUso;
    TSpeedButton *spb_DCasoUsoAssociacao;
    TSpeedButton *spb_DEstadosABC;
    TSpeedButton *spb_DEstadosComentario;
    TSpeedButton *spb_DEstadosNoteLink;
    TSpeedButton *spb_DEstadosPointer;
    TSpeedButton *spb_DEstadosEstado;
    TSpeedButton *spb_DEstadosEstadoInicial;
    TSpeedButton *spb_DEstadosEstadoFinal;
    TSpeedButton *spb_DEstadosTransicao;
    TAction *actInsereConectorAgregacao;
    TAction *actInsereConectorTransicao;
    TMenuItem *N7;
    TMenuItem *mnuZoomIn;
    TMenuItem *mnuZoomOut;
    TStatusBar *stb_Info;
    TAction *actZoomIn;
    TAction *actZoomOut;
    TMenuItem *mnuConnectorZoomIn;
    TMenuItem *mnuConnectorZoomOut;
    TMenuItem *N13;
    TMenuItem *mnuObjectZoomIn;
    TMenuItem *mnuObjectZoomOut;
    TMenuItem *N14;
    TMenuItem *mnuGrupoZoomIn;
    TMenuItem *mnuGrupoZoomOut;
    TMenuItem *N15;
    TAction *actPrint;
    TAction *actAlignLeft;
    TAction *actAlignRight;
    TAction *actAlignTop;
    TAction *actAlignBottom;
    TAction *actFormatFillColorObject;
    TAction *actFormatLineColorObject;
    TAction *actFormatFontObject;
    TAction *actFormatLineColorConnector;
    TAction *actFormatFillColorGroup;
    TAction *actFormatLineColorGroup;
    TAction *actFormatFontGroup;
    TAction *actDeleteFromDiagrama;
    TAction *actSelectAll;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall BBoardMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall BBoardMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y);
    void __fastcall BBoardMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y);
    void __fastcall BBoardPaint(TObject *Sender);
    void __fastcall btnApplyClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall actOpenSpecificationExecute(TObject *Sender);
    void __fastcall actResetPointerExecute(TObject *Sender);
    void __fastcall actInsereObjetoClasseExecute(TObject *Sender);
    void __fastcall actInsereObjetoComentarioExecute(TObject *Sender);
    void __fastcall actInsereObjetoEstadoExecute(TObject *Sender);
    void __fastcall actInsereObjetoEstadoInicialExecute(
      TObject *Sender);
    void __fastcall actInsereObjetoEstadoFinalExecute(TObject *Sender);
    void __fastcall actInsereObjetoAtorExecute(TObject *Sender);
    void __fastcall actInsereConectorHerancaExecute(TObject *Sender);
    void __fastcall actInsereConectorAssociacaoExecute(
      TObject *Sender);
    void __fastcall actInsereConectorDependenciaExecute(
      TObject *Sender);
    void __fastcall actInsereConectorAssociativoExecute(
      TObject *Sender);
    void __fastcall actInsereConectorAgregacaoExecute(TObject *Sender);
    void __fastcall actInsereConectorTransicaoExecute(TObject *Sender);
    void __fastcall actZoomInExecute(TObject *Sender);
    void __fastcall actZoomOutExecute(TObject *Sender);
    void __fastcall actPrintExecute(TObject *Sender);
    void __fastcall actAlignLeftExecute(TObject *Sender);
    void __fastcall actAlignRightExecute(TObject *Sender);
    void __fastcall actAlignTopExecute(TObject *Sender);
    void __fastcall actAlignBottomExecute(TObject *Sender);
    void __fastcall actFormatFillColorObjectExecute(TObject *Sender);
    void __fastcall actFormatLineColorObjectExecute(TObject *Sender);
    void __fastcall actFormatLineColorConnectorExecute(TObject *Sender);
    void __fastcall actFormatFillColorGroupExecute(TObject *Sender);
    void __fastcall actFormatLineColorGroupExecute(TObject *Sender);
    void __fastcall actFormatFontGroupExecute(TObject *Sender);
    void __fastcall actFormatFontObjectExecute(TObject *Sender);
    void __fastcall actDeleteFromDiagramaExecute(TObject *Sender);
    void __fastcall actSelectAllExecute(TObject *Sender);
private:	// User declarations
    void ControlPanelVisibilityByType(int DiagramType);
    Diagrama *H;
public:		// User declarations
    Diagrama* GetDiagrama();
    void SetDiagrama(Diagrama *thisDiagrama);                         
    void SetBoardBounds(int HSize, int VSize);
    void AbrePopupMenuDiagrama(TMouseButton Button);
    __fastcall TfrmPainelDiagramador(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPainelDiagramador *frmPainelDiagramador;
//---------------------------------------------------------------------------
#endif
