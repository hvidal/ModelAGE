//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Splash.h"               
#include "Sobre.h"                
                                           
#include "X_frm_PainelDiagramador.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TBase *Base;
//---------------------------------------------------------------------------
__fastcall TBase::TBase(TComponent* Owner)
	: TForm(Owner)
{
}
//----------------------------------------------------------------------------
__fastcall TBase::TBase(Classes::TComponent* AOwner, int Dummy)
	: TForm(AOwner, Dummy)
{
}
//----------------------------------------------------------------------------
void __fastcall TBase::FormCreate(TObject *Sender)
{
    ProjetoPrincipal = new Projeto();
    // Links dos Eventos
    ProjetoPrincipal->SetNotificacaoInclusaoObjeto(ObjetoIncluido);
    ProjetoPrincipal->SetNotificacaoInclusaoConector(ConectorIncluido);

    OpenDialog->InitialDir = DirInicial->Directory;
    SaveDialog->InitialDir = DirInicial->Directory;

    MontaArvoreProjeto();
}
//---------------------------------------------------------------------------
void __fastcall TBase::FormShow(TObject *Sender)
{
//    frmSplash->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TBase::CriaModelo(int Type, AnsiString Model)
{
    Diagrama *thisDiagram;
    thisDiagram = new Diagrama();

    thisDiagram->SetProject(ProjetoPrincipal);
    thisDiagram->NewModel(Model);
    thisDiagram->SetBounds(1000, 1000);
    *thisDiagram->Descricao = "";
    thisDiagram->SetType(Type);

    TTreeNode *ParentNode, *NewNode;
    ParentNode = BuscaPastaFrameWork(Type);

    NewNode = ProjectTree->Items->AddChildObject(ParentNode, thisDiagram->GetDiagramName(), (void*)NovoNode(false, ItemDIAGRAMA, thisDiagram));
    ExpandeCaminho(NewNode);
    NewNode->EditText();
}
//---------------------------------------------------------------------------
TreeNodeData* TBase::NovoNode(bool folder, int itemType, ItemProjeto *item)
{
    TreeNodeData *Ret;
    Ret = new TreeNodeData();

    Ret->SetFolder(folder);
    Ret->SetItemType(itemType);
    if (item != NULL)
        item->SetItemType(itemType);
    Ret->SetItemProjeto(item);

    return Ret;
}
//---------------------------------------------------------------------------
void TBase::ExpandeCaminho(TTreeNode *node)
{
    while(node->Parent != NULL)
    {
        node = node->Parent;
        node->Expand(false);
    }
}
//---------------------------------------------------------------------------
void __fastcall TBase::ObjetoIncluido(Objeto *novoObjeto)
{
    if(PodeInserirObjetoProjeto(novoObjeto))
    {
        TTreeNode *ParentNode, *NewNode;
        ParentNode = BuscaPastaFrameWork(1);
        NewNode = ProjectTree->Items->AddChildObject(ParentNode, novoObjeto->GetName(), (void*)NovoNode(false, ItemOBJETO, novoObjeto));
        ExpandeCaminho(NewNode);
    }
}
//---------------------------------------------------------------------------
void __fastcall TBase::ConectorIncluido(Connector *novoConector)
{
    TTreeNode *ParentNode, *NewNode;
    ParentNode = BuscaPastaFrameWork(1);
    NewNode = ProjectTree->Items->AddChildObject(ParentNode, "XXX", (void*)NovoNode(false, ItemCONECTOR, novoConector));
    ExpandeCaminho(NewNode);
}
//---------------------------------------------------------------------------
bool TBase::PodeInserirObjetoProjeto(Objeto *objeto)
{
    // Se o objeto for um dos abaixo, então este deve ser mostrado na árvore.
    if(objeto->GetType() == oClasse   ||
       objeto->GetType() == oAtor     ||
       objeto->GetType() == oConceito ||
       objeto->GetType() == oEstado)
        return true;
    return false;
}
//---------------------------------------------------------------------------
TTreeNode* TBase::GetPastaProjeto(AnsiString type)
{
    int i;
    for(i = 0; i < Base->ProjectTree->Items->Count; i++)
    {
    	if(Base->ProjectTree->Items->Item[i]->Text == type)
           	break;
    }
    return Base->ProjectTree->Items->Item[i];
}
//---------------------------------------------------------------------------
void TBase::AbreDiagrama(TTreeNode *node)
{
    TfrmPainelDiagramador *DiagramaAtivo;

    TreeNodeData *dados = (TreeNodeData*)node->Data;
                                                     
    DiagramaAtivo = new TfrmPainelDiagramador(Application);
              
    Diagrama *thisDiagram;
    thisDiagram = (Diagrama*)dados->GetItemProjeto();

    DiagramaAtivo->SetDiagrama(thisDiagram);

    DiagramaAtivo->mm_Description->Text = *thisDiagram->Descricao;
    DiagramaAtivo->lb_LastModified->Caption = *thisDiagram->LastModified;
    DiagramaAtivo->SetBoardBounds(thisDiagram->GetHorizontalSize(), thisDiagram->GetVerticalSize());

    DiagramaAtivo->Caption = thisDiagram->GetDiagramName();
}
//---------------------------------------------------------------------------
bool TBase::FrameWorkNode(TTreeNode *node)
{
	// Função que retorna true se o "node" pertencer ao
    // framework da ferramenta. Os nós que pertencem ao framework
    // são aqueles que estão no nível 0 e 1 da árvore...
	if (node->Level == 1 || node->Level == 0)
    	return true;
    return false;
}
//---------------------------------------------------------------------------
TTreeNode* TBase::BuscaPastaFrameWork(int DiagramType)
{
	if(DiagramType == ClassDiagram)
    	return GetPastaProjeto("Logical View");
	else if(DiagramType == UseCaseDiagram)
    	return GetPastaProjeto("Use Case View");
	else if(DiagramType == StateChartDiagram)
    	return GetPastaProjeto("Logical View");
	else if(DiagramType == SequenceDiagram)
    	return GetPastaProjeto("Logical View");
    else
        return NULL;
}
//---------------------------------------------------------------------------
int TBase::GetImageIndexTipo(ItemProjeto *item)
{
    if (item->GetItemType() == ItemOBJETO)
        return GetImageIndexTipoObjeto(item);
    else if (item->GetItemType() == ItemDIAGRAMA)
        return GetImageIndexTipoDiagrama(item);

    return GetImageIndexTipoConector(item);
}
//---------------------------------------------------------------------------
int TBase::GetImageIndexTipoDiagrama(ItemProjeto *item)
{
    int indice, tipo;
    Diagrama *diagrama;
    diagrama = (Diagrama*)item;
    tipo = diagrama->GetType();

	if(tipo == UseCaseDiagram)
		indice = 2;
    else if(tipo == ClassDiagram)
		indice = 3;
    else if(tipo == SequenceDiagram)
		indice = 4;
    else if(tipo == StateChartDiagram)
		indice = 5;
    else if(tipo == OntologyDiagram)
		indice = 6;

    return indice;
}
//---------------------------------------------------------------------------
int TBase::GetImageIndexTipoObjeto(ItemProjeto *item)
{
    int indice, tipo;
    Objeto *objeto;
    objeto = (Objeto*)item;
    tipo = objeto->GetType();

	if(tipo == oClasse)
    {
        ObjClasse *classe;
        classe = (ObjClasse *)objeto;
        if(classe->GetStereotype().LowerCase() == "boundary")
            indice =12;
        else if(classe->GetStereotype().LowerCase() == "control")
            indice =13;
        else if(classe->GetStereotype().LowerCase() == "entity")
            indice =14;
        else
    		indice = 8;
    }
    else if(tipo == oConceito)
		indice = 10;
    else if(tipo == oAtor)
		indice = 7;
    else if(tipo == oEstado)
		indice = 9;
    return indice;
}
//---------------------------------------------------------------------------
int TBase::GetImageIndexTipoConector(ItemProjeto *item)
{
    return 15;
}
//---------------------------------------------------------------------------
void TBase::MontaArvoreProjeto()
{
    ProjectTree->Items->Clear();
    TTreeNode *raizProjeto = ProjectTree->Items->AddObject(ProjectTree->Selected, "New Project", (void*)NovoNode(true, -1, NULL));

	ProjectTree->Items->AddChildObject(raizProjeto, "Use Case View", (void*)NovoNode(true, -1, NULL));
	ProjectTree->Items->AddChildObject(raizProjeto, "Logical View", (void*)NovoNode(true, -1, NULL));
	ProjectTree->Items->AddChildObject(raizProjeto, "Dynamic View", (void*)NovoNode(true, -1, NULL));
  	ProjectTree->Items->AddChildObject(raizProjeto, "Component View", (void*)NovoNode(true, -1, NULL));
    raizProjeto->Expand(false);
}
//---------------------------------------------------------------------------
void TBase::NovoDominio()
{
    TTreeNode *raizDominio = ProjectTree->Items->AddObject(ProjectTree->Selected, "New Domain", (void*)NovoNode(true, -1, NULL));

	ProjectTree->Items->AddChildObject(raizDominio, "Use Case View", (void*)NovoNode(true, -1, NULL));
	ProjectTree->Items->AddChildObject(raizDominio, "Logical View", (void*)NovoNode(true, -1, NULL));
	ProjectTree->Items->AddChildObject(raizDominio, "Dynamic View", (void*)NovoNode(true, -1, NULL));
  	ProjectTree->Items->AddChildObject(raizDominio, "Component View", (void*)NovoNode(true, -1, NULL));

  	TTreeNode *raizBusiness = ProjectTree->Items->AddChildObject(raizDominio, "Business View", (void*)NovoNode(true, -1, NULL));
  	ProjectTree->Items->AddChildObject(raizBusiness, "Ontology", (void*)NovoNode(true, -1, NULL));
  	ProjectTree->Items->AddChildObject(raizBusiness, "Process", (void*)NovoNode(true, -1, NULL));
    raizDominio->Expand(false);
}
//---------------------------------------------------------------------------
void __fastcall TBase::ProjectTreeDblClick(TObject *Sender)
{
    TreeNodeData *dados = (TreeNodeData*)ProjectTree->Selected->Data;

    if (dados->GetItemType() == ItemDIAGRAMA)
    {
        bool existeAberto;
        TfrmPainelDiagramador *DiagramaAtivo;
        // Vejo se existe alguma MDI aberta com este diagrama
        existeAberto = false;
        for (int i = MDIChildCount-1; i >= 0; i--)
        {
            DiagramaAtivo = (TfrmPainelDiagramador*) MDIChildren[i];
            if(DiagramaAtivo->GetDiagrama() == dados->GetItemProjeto())
            {
                existeAberto = true;
                break;
            }
        }

        if(dados->GetItemProjeto() != NULL && !existeAberto)
        {
            AbreDiagrama(ProjectTree->Selected);
        }
    }
    else if (dados->GetItemType() == ItemOBJETO)
    {
        // Abro a janela de especificação do objeto
        Objeto *objeto;
        objeto = (Objeto*)dados->GetItemProjeto();
        FabricaControlador fabrica;
        IControladorObjeto *controller;
        controller = fabrica.CriaControladorObjeto(objeto->GetType());
        controller->Execute(objeto);
    }
    else
    {
        // Abro a janela de especificação do conector    
    }
}
//---------------------------------------------------------------------------

void __fastcall TBase::ProjectTreeDragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
    TTreeNode *TargetNode, *SourceNode;
    TargetNode = ProjectTree->GetNodeAt(X, Y);
    if (TargetNode != NULL)
    {
    	SourceNode = ProjectTree->Selected;
        SourceNode->MoveTo(TargetNode, naAddChildFirst);
        TargetNode->Expand(false);
        ProjectTree->Selected = TargetNode;
    }        
}
//---------------------------------------------------------------------------

void __fastcall TBase::ProjectTreeDragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
    TTreeNode *TargetNode, *SourceNode;
    TargetNode = ProjectTree->GetNodeAt(X, Y);
    SourceNode = ProjectTree->Selected;
    if (Source == Sender && TargetNode != NULL && !FrameWorkNode(SourceNode))
    {
    	Accept = true;
        while(TargetNode->Parent != NULL && TargetNode != SourceNode)
        {
             TargetNode = TargetNode->Parent;
        }
        if(TargetNode == SourceNode)
        {
             Accept = false;
        }
    }
    else
    	Accept = false;
}
//---------------------------------------------------------------------------

void __fastcall TBase::ProjectTreeEdited(TObject *Sender, TTreeNode *Node,
      AnsiString &S)
{
    TreeNodeData *dados = (TreeNodeData*)ProjectTree->Selected->Data;
    if(dados->GetItemProjeto() != NULL)
    {
    	((Diagrama*)dados->GetItemProjeto())->SetDiagramName(S);
    }
}
//---------------------------------------------------------------------------

void __fastcall TBase::ProjectTreeExpanding(TObject *Sender,
      TTreeNode *Node, bool &AllowExpansion)
{
    TreeNodeData *x = (TreeNodeData*)Node->Data;
    if(Node->Expanded && x->IsFolder())
    	Node->ImageIndex = 0;
    else if(!Node->Expanded && x->IsFolder())
    	Node->ImageIndex = 1;
    else                     
    {                                              
     	Node->ImageIndex = GetImageIndexTipo(x->GetItemProjeto());
    }
}                 
//---------------------------------------------------------------------------

void __fastcall TBase::ProjectTreeGetImageIndex(TObject *Sender,
      TTreeNode *Node)
{
    TreeNodeData *x = (TreeNodeData*)Node->Data;

    if(Node->Expanded && x->IsFolder())
    	Node->ImageIndex = 0;
    else if(!Node->Expanded && x->IsFolder())
    	Node->ImageIndex = 1;
    else
    {
    	Node->ImageIndex = GetImageIndexTipo(x->GetItemProjeto());
    }        
}
//---------------------------------------------------------------------------

void __fastcall TBase::ProjectTreeGetSelectedIndex(TObject *Sender,
      TTreeNode *Node)
{
    TreeNodeData *x = (TreeNodeData*)Node->Data;

    if(Node->Expanded && x->IsFolder())
    	Node->SelectedIndex = 0;
    else if(!Node->Expanded && x->IsFolder())
    	Node->SelectedIndex = 1;
    else
    {
    	Node->SelectedIndex = GetImageIndexTipo(x->GetItemProjeto());
    }
}
//---------------------------------------------------------------------------

void __fastcall TBase::About1Click(TObject *Sender)
{
    TAbout *About = new TAbout(Application);
    About->ShowModal();
    delete About;
}
//---------------------------------------------------------------------------

void __fastcall TBase::actZoomInExecute(TObject *Sender)
{
	TfrmPainelDiagramador *DiagramaAtivo;
    DiagramaAtivo = (TfrmPainelDiagramador*)ActiveMDIChild;

    if(DiagramaAtivo == NULL) return;

  	DiagramaAtivo->actZoomInExecute(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TBase::actZoomOutExecute(TObject *Sender)
{
	TfrmPainelDiagramador *DiagramaAtivo;
    DiagramaAtivo = (TfrmPainelDiagramador*)ActiveMDIChild;

    if(DiagramaAtivo == NULL) return;

  	DiagramaAtivo->actZoomOutExecute(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TBase::actOpenSpecificationExecute(TObject *Sender)
{
    TfrmPainelDiagramador *DiagramaAtivo;
    DiagramaAtivo = (TfrmPainelDiagramador*)ActiveMDIChild;
    if(DiagramaAtivo == NULL) return;
        DiagramaAtivo->actOpenSpecificationExecute(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TBase::actPrintDiagramExecute(TObject *Sender)
{
    TfrmPainelDiagramador *DiagramaAtivo;
    DiagramaAtivo = (TfrmPainelDiagramador*)ActiveMDIChild;
    if(DiagramaAtivo == NULL) return;
        DiagramaAtivo->actPrintExecute(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TBase::actWindowCascadeExecute(TObject *Sender)
{
	Cascade();
}
//---------------------------------------------------------------------------

void __fastcall TBase::actWindowHorizontalTileExecute(TObject *Sender)
{
	TileMode = tbHorizontal;
	Tile();
}
//---------------------------------------------------------------------------

void __fastcall TBase::actWindowVerticalTileExecute(TObject *Sender)
{
	TileMode = tbVertical;
	Tile();
}
//---------------------------------------------------------------------------

void __fastcall TBase::actNewUseCaseDiagramExecute(TObject *Sender)
{
    CriaModelo(UseCaseDiagram, "Use Case Diagram");    
}
//---------------------------------------------------------------------------

void __fastcall TBase::actNewClassDiagramExecute(TObject *Sender)
{
    CriaModelo(ClassDiagram, "Class Diagram");    
}
//---------------------------------------------------------------------------

void __fastcall TBase::actNewStateChartDiagramExecute(TObject *Sender)
{
    CriaModelo(StateChartDiagram, "StateChart Diagram");
}
//---------------------------------------------------------------------------

void __fastcall TBase::actNewSequenceDiagramExecute(TObject *Sender)
{
    CriaModelo(SequenceDiagram, "Sequence Diagram");
}
//---------------------------------------------------------------------------

void __fastcall TBase::actAlignLeftExecute(TObject *Sender)
{
    TfrmPainelDiagramador *DiagramaAtivo;
    DiagramaAtivo = (TfrmPainelDiagramador*)ActiveMDIChild;
    if(DiagramaAtivo == NULL) return;
        DiagramaAtivo->actAlignLeftExecute(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TBase::actAlignRightExecute(TObject *Sender)
{
    TfrmPainelDiagramador *DiagramaAtivo;
    DiagramaAtivo = (TfrmPainelDiagramador*)ActiveMDIChild;
    if(DiagramaAtivo == NULL) return;
        DiagramaAtivo->actAlignRightExecute(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TBase::actAlignTopExecute(TObject *Sender)
{
    TfrmPainelDiagramador *DiagramaAtivo;
    DiagramaAtivo = (TfrmPainelDiagramador*)ActiveMDIChild;
    if(DiagramaAtivo == NULL) return;
        DiagramaAtivo->actAlignTopExecute(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TBase::actAlignBottomExecute(TObject *Sender)
{
    TfrmPainelDiagramador *DiagramaAtivo;
    DiagramaAtivo = (TfrmPainelDiagramador*)ActiveMDIChild;
    if(DiagramaAtivo == NULL) return;
        DiagramaAtivo->actAlignBottomExecute(Sender);    
}
//---------------------------------------------------------------------------

