//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <vcl\sysutils.hpp>
#include <vcl\windows.hpp>
#include <vcl\messages.hpp>
#include <vcl\sysutils.hpp>
#include <vcl\classes.hpp>
#include <vcl\graphics.hpp>
#include <vcl\controls.hpp>
#include <vcl\forms.hpp>
#include <vcl\dialogs.hpp>
#include <vcl\stdctrls.hpp>
#include <vcl\buttons.hpp>
#include <vcl\extctrls.hpp>
#include <vcl\menus.hpp>
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>

#include "TreeNodeData.h"
#include "Projeto.h"

#include <FileCtrl.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TBase : public TForm
{
__published:
	TStatusBar *StatusLine;
    TSplitter *Spl_Vertical;
    TPanel *pn_Left;
    TSplitter *Spl_Horizontal;
    TPageControl *pc_Arvores;
    TTabSheet *ts_Projeto;
    TTreeView *ProjectTree;
    TTabSheet *ts_Domain;
    TTreeView *DomainTree;
    TPageControl *pc_Notes;
    TTabSheet *ts_Notes;
    TMemo *Memo1;
    TToolBar *tb_Funcoes;
    TMainMenu *MainMenu1;
    TMenuItem *mnuNew;
    TMenuItem *mnuOpen;
    TMenuItem *mnuSave;
    TMenuItem *mnuSaveAs;
    TMenuItem *N8;
    TMenuItem *mnuProjectNew;
    TMenuItem *UseCasesDiagram1;
    TMenuItem *ClassDiagram1;
    TMenuItem *SequenceDiagram1;
    TMenuItem *StateDiagram1;
    TMenuItem *ComponentDiagram1;
    TMenuItem *mnuExit;
    TMenuItem *mnuOntologyDiagram;
    TMenuItem *mnuDiagram;
    TMenuItem *mnuObjectProperties;
    TMenuItem *mnuDeleteObject;
    TMenuItem *mnuSelectAll;
    TMenuItem *N7;
    TMenuItem *mnuPrint;
    TMenuItem *mnuTools;
    TMenuItem *HTMLReport1;
    TMenuItem *XMLReport1;
    TMenuItem *N2;
    TMenuItem *GenarateCode1;
    TMenuItem *mnuWindow;
    TMenuItem *mnuCascade;
    TMenuItem *mnuTile;
    TMenuItem *mnuTileHorizontal;
    TMenuItem *mnuTileVertical;
    TMenuItem *mnuArrange;
    TMenuItem *mnuMinimizeAll;
    TMenuItem *N5;
    TMenuItem *mnuRefresh;
    TMenuItem *Help1;
    TMenuItem *About1;
    TImageList *il_Imagens;
    TPrintDialog *pdPrint;
    TOpenDialog *OpenDialog;
    TSaveDialog *SaveDialog;
    TPopupMenu *ppmNewItemsProject;
    TMenuItem *NewUseCase2;
    TMenuItem *NewClassDiagram1;
    TMenuItem *NewSequenceDiagram1;
    TMenuItem *NewStateDiagram1;
    TMenuItem *NewComponentDiagram1;
    TDirectoryListBox *DirInicial;
    TToolButton *tb_NovoProjeto;
    TImageList *il_ToolBar;
    TToolButton *tb_AbreProjeto;
    TToolButton *tb_SalvaProjeto;
    TToolButton *ToolButton3;
    TToolButton *tb_ZoomIn;
    TToolButton *ToolButton5;
    TMenuItem *mnuZoomIn;
    TMenuItem *mnuZoomOut;
    TMenuItem *N13;
    TActionList *ActionList;
    TToolButton *tb_Print;
    TToolButton *tb_Projeto;
    TToolButton *ToolButton4;
    TAction *actZoomIn;
    TAction *actZoomOut;
    TMenuItem *N6;
    TToolButton *ToolButton1;
    TToolButton *ToolButton2;
    TToolButton *tb_Propriedades;
    TAction *actOpenSpecification;
    TAction *actPrintDiagram;
    TAction *actNewProject;
    TAction *actOpenProject;
    TAction *actSaveProject;
    TMenuItem *mnuProjeto;
    TMenuItem *mnuFileImport;
    TMenuItem *mnuFileExport;
    TMenuItem *Properties1;
    TToolButton *ToolButton6;
    TToolButton *ToolButton7;
    TToolButton *ToolButton8;
    TToolButton *ToolButton9;
    TAction *actWindowCascade;
    TAction *actWindowHorizontalTile;
    TAction *actWindowVerticalTile;
    TAction *actNewClassDiagram;
    TAction *actNewUseCaseDiagram;
    TAction *actNewStateChartDiagram;
    TAction *actNewSequenceDiagram;
    TToolButton *ToolButton10;
    TToolButton *tb_AlignLeft;
    TToolButton *tb_AlignRight;
    TToolButton *tb_AlignTop;
    TToolButton *tb_AlignBottom;
    TAction *actAlignLeft;
    TAction *actAlignRight;
    TAction *actAlignTop;
    TAction *actAlignBottom;
    TMenuItem *N1;
    TMenuItem *mnuDiagramAlign;
    TMenuItem *mnuAlignLeft;
    TMenuItem *mnuAlignRight;
    TMenuItem *mnuAlignTop;
    TMenuItem *mnuAlignBottom;
    TAction *actFormatFillColor;
    TMenuItem *mnuProcessChainDiagram;
    TMenuItem *N4;
    TMenuItem *N3;
    TMenuItem *mnuPopUpOntologyDiagram;
    TMenuItem *mnuPopUpProcessChainDiagram;
    TMenuItem *N9;
    TMenuItem *N10;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ProjectTreeDblClick(TObject *Sender);
    void __fastcall ProjectTreeDragDrop(TObject *Sender,
      TObject *Source, int X, int Y);
    void __fastcall ProjectTreeDragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept);
    void __fastcall ProjectTreeEdited(TObject *Sender, TTreeNode *Node,
      AnsiString &S);
    void __fastcall ProjectTreeExpanding(TObject *Sender,
      TTreeNode *Node, bool &AllowExpansion);
    void __fastcall ProjectTreeGetImageIndex(TObject *Sender,
      TTreeNode *Node);
    void __fastcall ProjectTreeGetSelectedIndex(TObject *Sender,
      TTreeNode *Node);
    void __fastcall About1Click(TObject *Sender);
    void __fastcall actZoomInExecute(TObject *Sender);
    void __fastcall actZoomOutExecute(TObject *Sender);
    void __fastcall actOpenSpecificationExecute(TObject *Sender);
    void __fastcall actPrintDiagramExecute(TObject *Sender);
    void __fastcall actWindowCascadeExecute(TObject *Sender);
    void __fastcall actWindowHorizontalTileExecute(TObject *Sender);
    void __fastcall actWindowVerticalTileExecute(TObject *Sender);
    void __fastcall actNewUseCaseDiagramExecute(TObject *Sender);
    void __fastcall actNewClassDiagramExecute(TObject *Sender);
    void __fastcall actNewStateChartDiagramExecute(TObject *Sender);
    void __fastcall actNewSequenceDiagramExecute(TObject *Sender);
    void __fastcall actAlignLeftExecute(TObject *Sender);
    void __fastcall actAlignRightExecute(TObject *Sender);
    void __fastcall actAlignTopExecute(TObject *Sender);
    void __fastcall actAlignBottomExecute(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
private:        // private user declarations
    Projeto *ProjetoPrincipal;

    void __fastcall CriaModelo(int Type, AnsiString Model);
    void MontaArvoreProjeto();
    void NovoDominio();

    TreeNodeData* NovoNode(bool folder, int itemType, ItemProjeto *item);
    TTreeNode* GetPastaProjeto(AnsiString type);
    TTreeNode* BuscaPastaFrameWork(int DiagramType);
    bool FrameWorkNode(TTreeNode*);

    void AbreDiagrama(TTreeNode *node);
    void ExpandeCaminho(TTreeNode *node);

    void __fastcall ObjetoIncluido(Objeto *novoObjeto);
    void __fastcall ConectorIncluido(Connector *novoConector);    

    int GetImageIndexTipo(ItemProjeto *item);
    int GetImageIndexTipoDiagrama(ItemProjeto *item);
    int GetImageIndexTipoObjeto(ItemProjeto *item);
    int GetImageIndexTipoConector(ItemProjeto *item);

    bool PodeInserirObjetoProjeto(Objeto *objeto);    
public:         // public user declarations
	__fastcall TBase(TComponent* Owner);
    __fastcall TBase(TComponent* AOwner, int Dummy);
};
//---------------------------------------------------------------------------
extern TBase *Base;
//---------------------------------------------------------------------------
#endif
