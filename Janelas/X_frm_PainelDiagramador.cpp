//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop         

#include "X_frm_PainelDiagramador.h"
//#include "X_frmPrintPreview.h"

#include "math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPainelDiagramador *frmPainelDiagramador;
//---------------------------------------------------------------------------
__fastcall TfrmPainelDiagramador::TfrmPainelDiagramador(TComponent* Owner)
        : TForm(Owner)
{
}
void TfrmPainelDiagramador::SetDiagrama(Diagrama *thisDiagrama)
{
    H = thisDiagrama;
    ControlPanelVisibilityByType(H->GetType());
}
void TfrmPainelDiagramador::SetBoardBounds(int HSize, int VSize)
{
    BBoard->Width = HSize;
    BBoard->Height = VSize;
}
Diagrama* TfrmPainelDiagramador::GetDiagrama()
{
    return H;
}
void TfrmPainelDiagramador::ControlPanelVisibilityByType(int DiagramType)
{
    if(DiagramType == ClassDiagram)
    {
    	pnlClass->Visible =  true;
        pnlUseCases->Visible = false;
        pnlSequence->Visible = false;
        pnlEstados->Visible = false;
    }
    else if(DiagramType == UseCaseDiagram)
    {
    	pnlClass->Visible =  false;
        pnlUseCases->Visible = true;
        pnlSequence->Visible = false;
        pnlEstados->Visible = false;
    }
    else if(DiagramType == StateChartDiagram)
    {
    	pnlClass->Visible =  false;
        pnlUseCases->Visible = false;
        pnlSequence->Visible = false;
        pnlEstados->Visible = true;
    }
    else if(DiagramType == SequenceDiagram)
    {
    	pnlClass->Visible =  false;
        pnlUseCases->Visible = false;
        pnlSequence->Visible = true;
        pnlEstados->Visible = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPainelDiagramador::FormClose(TObject *Sender, TCloseAction &Action)
{
    Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPainelDiagramador::BBoardMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    H->SetZoomMode(BBoard->Canvas);

    TPoint p[1], Scroll;

    Scroll.x = sbArea->HorzScrollBar->Position;
    Scroll.y = sbArea->VertScrollBar->Position;

    p[0].x = X - Scroll.x;
    p[0].y = Y - Scroll.y;

    DPtoLP(BBoard->Canvas->Handle, p, 1);

    H->MouseDown(BBoard, p[0].x, p[0].y, Button, Shift);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::BBoardMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    H->SetZoomMode(BBoard->Canvas);

    TPoint p[1], Scroll;

    Scroll.x = sbArea->HorzScrollBar->Position;
    Scroll.y = sbArea->VertScrollBar->Position;

    p[0].x = X - Scroll.x;
    p[0].y = Y - Scroll.y;

    DPtoLP(BBoard->Canvas->Handle, p, 1);

    // Escrevo X e Y na status bar
    stb_Info->Panels->Items[2]->Text = AnsiString(p[0].x);
    stb_Info->Panels->Items[4]->Text = AnsiString(p[0].y);

    H->MouseMove(BBoard, p[0].x, p[0].y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPainelDiagramador::BBoardMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    H->SetZoomMode(BBoard->Canvas);

    TPoint p[1], Scroll;

    Scroll.x = sbArea->HorzScrollBar->Position;
    Scroll.y = sbArea->VertScrollBar->Position;

    p[0].x = X - Scroll.x;
    p[0].y = Y - Scroll.y;

    DPtoLP(BBoard->Canvas->Handle, p, 1);
                                                   
    H->MouseUp(BBoard, p[0].x, p[0].y);

    AbrePopupMenuDiagrama(Button);
}
//---------------------------------------------------------------------------
void TfrmPainelDiagramador::AbrePopupMenuDiagrama(TMouseButton Button)
{
    ViewObjeto *ViewObjeto;
    ViewConector *ViewConector;

    ViewObjeto = H->getSelectedObject();
    ViewConector = H->getSelectedConnector();

    if(Button == mbRight && ViewObjeto != 0)
    {
        BBoard->PopupMenu = pmPropriedadesObjeto;
    }
    else if (Button == mbRight && ViewConector != 0)
    {
        BBoard->PopupMenu = pmPropriedadesConector;
    }
    else if (Button == mbRight && H->IsGroupSelected())
    {
        BBoard->PopupMenu = pmPropriedadesGrupo;
    }
    else
    {
        BBoard->PopupMenu = pmPropriedadesGerais;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPainelDiagramador::BBoardPaint(TObject *Sender)
{
    H->SetZoomMode(BBoard->Canvas);
    if(!H->ScreenUpdateIsLocked())
    {
        H->Paint(BBoard->Canvas);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPainelDiagramador::btnApplyClick(TObject *Sender)
{
    AnsiString A, B;
    A = ed_HSize->Text;
    B = ed_VSize->Text;

    try
    {
    	H->SetBounds(ed_HSize->Text.ToInt(), ed_VSize->Text.ToInt());
        SetBoardBounds(ed_HSize->Text.ToInt(), ed_VSize->Text.ToInt());
    	H->setModified(true);
    }
    catch(...)
    {
    	H->SetBounds(A.ToInt(), B.ToInt());
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPainelDiagramador::FormCreate(TObject *Sender)
{
    pc_Diagram->ActivePage = ts_Diagram;
    BBoard->Left = 0;
    BBoard->Top = 0;
    sbArea->HorzScrollBar->Position = 0;
    sbArea->VertScrollBar->Position = 0;
    stb_Info->Panels->Items[1]->Text = "X:";
    stb_Info->Panels->Items[3]->Text = "Y:";
}
//---------------------------------------------------------------------------
void __fastcall TfrmPainelDiagramador::actOpenSpecificationExecute(
      TObject *Sender)
{
    H->AbrePropriedades(BBoard);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actResetPointerExecute(
      TObject *Sender)
{
    H->Reset(BBoard->Canvas);
    H->Refresh(BBoard->Canvas);
    H->Paint(BBoard->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actInsereObjetoClasseExecute(
      TObject *Sender)
{
     H->PrepareToInsert(oClasse);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actInsereObjetoComentarioExecute(
      TObject *Sender)
{
     H->PrepareToInsert(oComentario);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actInsereObjetoEstadoExecute(
      TObject *Sender)
{
     H->PrepareToInsert(oEstado);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actInsereObjetoEstadoInicialExecute(
      TObject *Sender)
{
     H->PrepareToInsert(oEstadoInicial);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actInsereObjetoEstadoFinalExecute(
      TObject *Sender)
{
     H->PrepareToInsert(oEstadoFinal);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actInsereObjetoAtorExecute(
      TObject *Sender)
{
     H->PrepareToInsert(oAtor);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actInsereConectorHerancaExecute(
      TObject *Sender)
{
    H->PrepareConnection(cHeranca);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actInsereConectorAssociacaoExecute(
      TObject *Sender)
{
    H->PrepareConnection(cAssociacao);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actInsereConectorDependenciaExecute(
      TObject *Sender)
{
    H->PrepareConnection(cDependencia);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actInsereConectorAssociativoExecute(
      TObject *Sender)
{
    H->PrepareConnection(cAssociativo);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actInsereConectorAgregacaoExecute(
      TObject *Sender)
{
    H->PrepareConnection(cAgregacao);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actInsereConectorTransicaoExecute(
      TObject *Sender)
{
    H->PrepareConnection(cTransicao);
}
//---------------------------------------------------------------------------









void __fastcall TfrmPainelDiagramador::actZoomInExecute(TObject *Sender)
{
    if(H->ZoomIn())
    {
        H->Refresh(BBoard->Canvas);
        H->Paint(BBoard->Canvas);
        stb_Info->Panels->Items[0]->Text = "Zoom: " + AnsiString((int)ceil(H->GetZoomFactor()*100)) + "%";
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actZoomOutExecute(TObject *Sender)
{
    if(H->ZoomOut())
    {
        H->Refresh(BBoard->Canvas);
        H->Paint(BBoard->Canvas);
        stb_Info->Panels->Items[0]->Text = "Zoom: " + AnsiString((int)ceil(H->GetZoomFactor()*100)) + "%";
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actPrintExecute(TObject *Sender)
{
/*    TfrmPrintPreview *printPreview;
    printPreview = new TfrmPrintPreview(Application);
    printPreview->Prn->BeginDoc();
    printPreview->Prn->Title = "ModelAGE - " + H->GetDiagramName();
    printPreview->Canvas->Assign(BBoard->Canvas);
    printPreview->Prn->EndDoc();
    printPreview->ShowModal();
*/
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actAlignLeftExecute(TObject *Sender)
{
    H->AlignGroup(alignLeft);
    H->Refresh(BBoard->Canvas);
	H->Paint(BBoard->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actAlignRightExecute(
      TObject *Sender)
{
    H->AlignGroup(alignRight);
    H->Refresh(BBoard->Canvas);
	H->Paint(BBoard->Canvas);    
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actAlignTopExecute(TObject *Sender)
{
    H->AlignGroup(alignTop);
    H->Refresh(BBoard->Canvas);
	H->Paint(BBoard->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actAlignBottomExecute(
      TObject *Sender)
{
    H->AlignGroup(alignBottom);
    H->Refresh(BBoard->Canvas);
	H->Paint(BBoard->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actFormatFillColorObjectExecute(
      TObject *Sender)
{
	ColorDialog->Color = H->getSelectedObject()->GetFillColor();
	if(ColorDialog->Execute())
    {
    	H->getSelectedObject()->SetFillColor(ColorDialog->Color);
        H->setModified(true);
        H->Refresh(BBoard->Canvas);
        H->Paint(BBoard->Canvas);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actFormatLineColorObjectExecute(
      TObject *Sender)
{
	ColorDialog->Color = H->getSelectedObject()->GetLineColor();
	if(ColorDialog->Execute())
    {
    	H->getSelectedObject()->SetLineColor(ColorDialog->Color);
        H->setModified(true);
        H->Refresh(BBoard->Canvas);
        H->Paint(BBoard->Canvas);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actFormatLineColorConnectorExecute(
      TObject *Sender)
{
	ColorDialog->Color = H->getSelectedConnector()->GetLineColor();
	if(ColorDialog->Execute())
    {
    	H->getSelectedConnector()->SetLineColor(ColorDialog->Color);
        H->setModified(true);
        H->Refresh(BBoard->Canvas);
        H->Paint(BBoard->Canvas);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actFormatFillColorGroupExecute(
      TObject *Sender)
{
	if(ColorDialog->Execute())
    {
    	H->SetGroupFillColor(ColorDialog->Color);
        H->Refresh(BBoard->Canvas);
        H->Paint(BBoard->Canvas);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actFormatLineColorGroupExecute(
      TObject *Sender)
{
	if(ColorDialog->Execute())
    {
    	H->SetGroupLineColor(ColorDialog->Color);
        H->Refresh(BBoard->Canvas);
        H->Paint(BBoard->Canvas);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actFormatFontGroupExecute(
      TObject *Sender)
{
	if(FontDialog->Execute())
    {
    	H->SetGroupFont(FontDialog->Font);
        H->Refresh(BBoard->Canvas);
        H->Paint(BBoard->Canvas);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actFormatFontObjectExecute(
      TObject *Sender)
{
    FontDialog->Font = H->getSelectedObject()->GetFont();
	if(FontDialog->Execute())
    {
    	H->getSelectedObject()->SetFont(FontDialog->Font);
        H->setModified(true);
        H->Refresh(BBoard->Canvas);
        H->Paint(BBoard->Canvas);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPainelDiagramador::actDeleteFromDiagramaExecute(
      TObject *Sender)
{
    H->Delete(BBoard);
}
//---------------------------------------------------------------------------
                                                                                                        


void __fastcall TfrmPainelDiagramador::actSelectAllExecute(TObject *Sender)
{
     H->SelectAll();
     H->Paint(BBoard->Canvas);
}
//---------------------------------------------------------------------------

