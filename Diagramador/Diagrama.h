#include <vcl\IniFiles.hpp>

#include "Projeto.h"
#include "ItemProjeto.h"

#include "Fabricas\FabricaSemantica.h"
#include "Fabricas\FabricaViews.h"
#include "Fabricas\FabricaControlador.h"
#include "Fabricas\FabricaGerenteConexao.h"

#include "Interfaces\IControladorObjeto.h"
#include "Interfaces\IControladorConector.h"

#include "ListaViewObjetos.h"
#include "ListaViewConectores.h"
#include "FuncoesBasicas.h"

#include<dos.h>
#include <stdio.h>
#include <math.h>

#ifndef DiagramaH

#define MinHorizontalSize 400
#define MinVerticalSize 400

// Model Types:
#define ClassDiagram         1
#define UseCaseDiagram       2
#define StateChartDiagram    3
#define ActivityDiagram      4
#define SequenceDiagram      5
#define CollaborationDiagram 6
#define ComponentDiagram     7
#define DeploymentDiagram    8

#define OntologyDiagram      21

// Alignments:
#define alignLeft            51
#define alignRight           52
#define alignTop             53
#define alignBottom          54

// Zoom
#define ZOOMSTEP             0.10
#define ZOOMMAX              1.20 // 120%
#define ZOOMMIN              0.30 // 30%

String IniStrToStr(const String Str);
AnsiString StrToIniStr(const AnsiString Str);

class Diagrama : public ItemProjeto
{
  private:
    Projeto *Project;

    // Lista de pontos que são formados conforme o usuário inicia a conexão
    // e vai costurando o diagrama até chegar ao objeto destino.
    TList *pontosReta;

  protected:

    AnsiString *ModelName;
    int *ModelType;

    ListaViewConectores ListaViewConectores, GrupoConn;

    bool *Down;
    bool *DownConnector;
    bool *DownGroup;

    bool *SelectGroup;

    int *WillConnect;
    int *WillResize;
    int *WillInsert;
    bool *ExisteOrigem;
    bool *DownOffsetA;
    bool *DownOffsetB;
    bool *Modified;

    // Variavel que será usada para indicar a primeira chamada ao evento mouse
    // move do arraste de algum item de modelo.
    bool *FirstMove;

    // Lista que armazena todos os pontos de quebra dos conectores do diagrama.
    // Os pontos armazenados são os mesmos apontados pelos seus respectivos
    // conectores.
    TList *ListaPontosConectores;

    // Lista que armazena os pontos de quebra que foram selecionados pelo usuário.
    TList *ListaPontosSelecionados;

    // Ponto que será usado como base quando o usuário selecionar uma região da
    // tela. Este ponto será a posição onde o usuário realizou o mouse down inicial.
    TPoint *Base;

    // Lista que contém as distâncias relativas entre o ponto do clique do usuário
    // na tela até cada objeto selecionado.
    TList *Distancias;

    // Lista que contém as distâncias relativas entre o ponto do clique do usuário
    // na tela até cada ponto de quebra selecionado.
    TList *DistanciasPontos;

    // Ponto do conector que está sendo movido pelo usuário.
    PontoQuebra *PontoSelecionado;
    void CopiaPontosConector(TList *lista);

    float *ZoomFactor;

    ViewObjeto *Origem, *Redimensionado, *Selecionado;
    ViewConector *SelecionadoConn;
    int *Xant, *Yant, *XOffset, *YOffset, *XFinal, *YFinal;
    int *HorizontalSize, *VerticalSize;

    bool *ScreenUpdateLock;

    void EsvaziaLista(TList *lista);
                                         
    void SetaCursor(TPaintBox *Board, float X, float Y);
    void Redimensiona(TPaintBox *Board, float X, float Y);
    void MovePontoConector(TPaintBox *Board, float X, float Y);
    void SoltaPontoSelecionado(TPaintBox *Board, float X, float Y);
    void AcertaNovoTamanho(TPaintBox *Board);
    ViewConector* BuscaViewConector(float X, float Y);
    void FinalizaConexao(TPaintBox *Board, float X, float Y);
    void Arrasta(TPaintBox *Board, float X, float Y);
    void ArrastaGrupo(TPaintBox *Board, float X, float Y);
    void AgrupaObjetos(TPaintBox *Board, float X, float Y);
    void setAllVisible(TPaintBox *Board);

    bool PreparaArrastaGrupo(TPaintBox *Board, float X, float Y);
    void NewObjectView(ViewObjeto *Novo);
    void Desaloco();

    void DeleteObjectView(ViewObjeto *VaiMorrer, TPaintBox *Board);
    void DeleteSelection(TPaintBox *Board);
    void DeleteViewConector(TPaintBox *Board);

    void NewViewConector(ViewConector *Novo);

  public:
    ListaViewObjetos ListaViewObjetos, GrupoObj;

    AnsiString GetTime();
    AnsiString *LastModified;
    AnsiString *Descricao;

    AnsiString *ModelFileName;

    Diagrama() : ItemProjeto()
    {
        //Tipo do Modelo:
        ModelType = new int;

        WillConnect = new int;
        WillResize = new int;
        WillInsert = new int;
        Down = new bool;
        DownConnector = new bool;
        DownGroup = new bool;
        SelectGroup = new bool;
        ExisteOrigem = new bool;
        DownOffsetA = new bool;
        DownOffsetB = new bool;
        Xant = new int;
        Yant = new int;
        Base = new TPoint;
        XOffset = new int;
        YOffset = new int;
        XFinal = new int;
        YFinal = new int;
        ModelFileName = new AnsiString;
        Modified = new bool;
        ModelName = new AnsiString;
        ScreenUpdateLock = new bool;
        LastModified = new AnsiString;
        Descricao = new AnsiString;
        HorizontalSize = new int;
        VerticalSize = new int;
        Distancias = new TList;
        DistanciasPontos = new TList;
        ZoomFactor = new float;

        ListaPontosConectores = new TList;
        ListaPontosSelecionados = new TList;

        FirstMove = new bool;

        *ScreenUpdateLock = false;

        *WillConnect = 0;
        *WillResize = 0;
        *WillInsert = 0;
        *Down = false;
        *FirstMove = false;
        *DownGroup = false;
        *SelectGroup = false;
        *ExisteOrigem = false;
        *DownOffsetA = false;
        *DownOffsetB = false;
        *ModelFileName = "";
        Redimensionado = NULL;
        Selecionado = NULL;
        SelecionadoConn = NULL;

        PontoSelecionado = NULL;
        pontosReta = NULL;

        *HorizontalSize = 1000;
        *VerticalSize = 1000;

        *ZoomFactor = 1;

        *Modified = false;
    }
    ~Diagrama()
    {
        FilaObjetos p, q;
        FilaConectores c, d;
        Desaloco();
        delete WillConnect, ExisteOrigem, Origem, Down, Xant, Yant, XFinal, YFinal;
        delete ModelFileName, ModelName, Modified, XOffset, YOffset, Redimensionado;
        delete WillInsert, LastModified, Descricao, HorizontalSize, VerticalSize;
        delete SelectGroup, Base, Distancias, DownGroup, DownOffsetA, DownOffsetB;
        delete DistanciasPontos, ModelType, ZoomFactor, DownConnector, FirstMove;
        delete ListaPontosSelecionados, ListaPontosConectores;
    }

    void SetProject(Projeto *owner);
    Projeto* GetProject();

    int Modificado();
    void setModified(bool newValue)
    {
    	*Modified = newValue;
    }
    int TemNome();
    bool ScreenUpdateIsLocked();
    int GetType();

    // Zoom
    void SetZoomFactor(float newZoomFactor);
    float GetZoomFactor();
    void SetZoomMode(TCanvas *Board);
    bool ZoomIn();
    bool ZoomOut();

    AnsiString GetDiagramName();
	void SetDiagramName(AnsiString newName);

    int GetHorizontalSize();
    int GetVerticalSize();

    void SetType(int thisType);
    void SetBounds(int H, int V);
    void Delete(TPaintBox *Board);
    void Paint(TCanvas *Board);

    ViewObjeto* getSelectedObject();
    ViewConector* getSelectedConnector();
    bool IsGroupSelected();

    // Reseta as variáveis de estado do Diagrama
    void Reset(TCanvas *Board);

    void Refresh(TCanvas *Board);

    void MoveConexao(TPaintBox *Board, int X, int Y, int dx, int dy, bool origem);

    // Eventos básicos
	void SelectAll();
    void PrepareConnection(int ConnId);
    void PrepareToInsert(int ConnId);
    void MouseDown(TPaintBox *Board, float X, float Y, TMouseButton Button, TShiftState Shift);
    void MouseMove(TPaintBox *Board, float X, float Y);
    void MouseUp(TPaintBox *Board, float X, float Y);
	void SelecionaGrupo(TPaintBox *Board, float X, float Y);
    ViewObjeto* CriaViewObjeto(int Type, float Xpos, float Ypos, TPaintBox *Board);
    void NewModel(AnsiString Nome);

    // Alinhamento
    void AlignGroup(int type);
    void SetGroupFillColor(TColor color);
    void SetGroupLineColor(TColor color);
    void SetGroupFont(TFont *font);

    // Trabalha com Arquivos
	void ExportaModelo(AnsiString PathFile);
    void ImportaModelo(AnsiString PathFile);

    // Erros
    void importError()
    {
    	MessageBox(0, "Import Error", "Currupted file.", MB_OK);
    }

    // Interface Janelas
    void AbrePropriedades(TPaintBox *Board);
};

void Diagrama::SetProject(Projeto *owner)
{
    Project = owner;
}
Projeto* Diagrama::GetProject()
{
    return Project;
}
int Diagrama::TemNome()
{
    return (*ModelFileName != "");
}
bool Diagrama::ScreenUpdateIsLocked()
{
	return (*ScreenUpdateLock);
}
int Diagrama::GetType()
{
    return *ModelType;
}
void Diagrama::SetZoomFactor(float newZoomFactor)
{
    if (newZoomFactor < 0.1) return;
    if (newZoomFactor > 2.0) return;
    *ZoomFactor = newZoomFactor;
}
float Diagrama::GetZoomFactor()
{
    return *ZoomFactor;
}
bool Diagrama::ZoomIn()
{
    if(*ZoomFactor == ZOOMMAX) return false;

    *ZoomFactor += ZOOMSTEP;
    if (*ZoomFactor > ZOOMMAX)
        *ZoomFactor = ZOOMMAX;
    return true;
}
bool Diagrama::ZoomOut()
{
    if(*ZoomFactor == ZOOMMIN) return false;

    *ZoomFactor -= ZOOMSTEP;
    if (*ZoomFactor < ZOOMMIN)
        *ZoomFactor = ZOOMMIN;
    return true;
}
void Diagrama::SetZoomMode(TCanvas *Board)
{
    SetMapMode( Board->Handle, MM_ANISOTROPIC );
    SetWindowExtEx(Board->Handle, Screen->PixelsPerInch, Screen->PixelsPerInch, NULL);
    SetViewportExtEx(Board->Handle, ceil(Screen->PixelsPerInch * (*ZoomFactor)), ceil(Screen->PixelsPerInch * (*ZoomFactor)), NULL);
}
int Diagrama::GetHorizontalSize()
{
    return *HorizontalSize;
}
int Diagrama::GetVerticalSize()
{
    return *VerticalSize;
}
AnsiString Diagrama::GetDiagramName()
{
    return *ModelName;
}
void Diagrama::SetDiagramName(AnsiString newName)
{
    *ModelName = newName;
}
void Diagrama::SetType(int thisType)
{
    *ModelType = thisType;
}
int Diagrama::Modificado()
{
    return (*Modified == true);
}
bool Diagrama::IsGroupSelected()
{
	return !GrupoObj.ListaVazia();
}
void Diagrama::Refresh(TCanvas *Board)
{
    Board->Pen->Mode = pmCopy;
    Board->Pen->Color = clWhite;
    Board->Pen->Style = psSolid;
    Board->Brush->Color = clWhite;
    Board->Brush->Style = bsSolid;
    Board->Rectangle(0, 0, 2*(*HorizontalSize), 2*(*VerticalSize));
}
void Diagrama::EsvaziaLista(TList *lista)
{
    // Esvazio a lista de ponteiros, sem desalocar os objetos...
    for(int i=0; i<lista->Count; i++)
    {
        lista->Items[i] = NULL;
    }
    // Apago todos os NULLs
    lista->Pack();
}
void Diagrama::SetBounds(int H, int V)
{
	// Pega o maior entre os valores...
	H = (H<MinHorizontalSize)?MinHorizontalSize:H;
    V = (V<MinVerticalSize)?MinVerticalSize:V;
	*HorizontalSize = H;
    *VerticalSize = V;
}
void Diagrama::PrepareConnection(int ConnId)
{
    *WillConnect = ConnId;
    if(SelecionadoConn != 0)
	    SelecionadoConn->SetSelection(false);
	SelecionadoConn = 0;
    *WillInsert = 0;
    *Modified = true;
}
void Diagrama::PrepareToInsert(int ObjId)
{
    *WillInsert = ObjId;
    *WillConnect = 0;
    *Modified = true;
    *Xant = -2000;
    *Yant = -2000;
}
void Diagrama::Desaloco()
{
    // Desaloco todo mundo

	ListaViewObjetos.Clear();
    GrupoObj.Clear();
    ListaViewConectores.Clear();
    GrupoConn.Clear();
}
void Diagrama::Reset(TCanvas *Board)
{
    // Zero todas as variáveis de controle da classe Diagrama
    if(Selecionado != 0)
        *Selecionado->isSelected = false;
    Selecionado = 0;

    if(SelecionadoConn != 0)
        SelecionadoConn->SetSelection(false);
    SelecionadoConn = 0;

    *WillConnect = 0;
    *WillInsert = 0;
    *WillResize = 0;
    *ExisteOrigem = false;
    *DownOffsetA = false;
    *DownOffsetB = false;

    Origem = 0;
    *Down = false;
    *DownConnector = false;
    *DownGroup = false;
    *SelectGroup = false;
    *FirstMove = false;
    GrupoObj.Esvazia();
    GrupoConn.Esvazia();
    EsvaziaLista(ListaPontosSelecionados);    

    Board->Pen->Mode = pmCopy;
}
void Diagrama::NewModel(AnsiString Nome)
{
    Desaloco();

    //Reseto as configurações

    *WillConnect = 0;
    *Down = false;
    *DownConnector = false;
    *ExisteOrigem = false;
    *FirstMove = false;
    *ModelFileName = "";
    *ModelName = Nome;
    *LastModified = GetTime();
    *Descricao = "";

    *Modified = true;
}
void Diagrama::CopiaPontosConector(TList *lista)
{
    // Clono a lista de pontos, copiando os pontos que existem
    // dentro da lista passada como parâmentro.
    for (int i=0; i<lista->Count; i++)
    {
        ListaPontosConectores->Add(lista->Items[i]);
    }
    ListaPontosConectores->Pack();
}
AnsiString Diagrama::GetTime()
{
    AnsiString Time, Data;
    AnsiString hora, min, seg, dia, mes, ano;
    struct  time t;
    struct date d;
    gettime(&t);
    getdate(&d);

    hora = AnsiString((int)t.ti_hour);
    min = AnsiString((int)t.ti_min);
    seg = AnsiString((int)t.ti_sec);

    dia = AnsiString((int)d.da_day);
    mes = AnsiString((int)d.da_mon);
    ano = AnsiString((int)d.da_year);

    if((int)t.ti_hour < 10) hora = AnsiString("0") + AnsiString((int)t.ti_hour);
    if((int)t.ti_min < 10) min = AnsiString("0") + AnsiString((int)t.ti_min);
    if((int)t.ti_sec < 10) seg = AnsiString("0") + AnsiString((int)t.ti_sec);

    if((int)d.da_day < 10) dia = AnsiString("0") + AnsiString((int)d.da_day);
    if((int)d.da_mon < 10) mes = AnsiString("0") + AnsiString((int)d.da_mon);
    if((int)d.da_year < 10) ano = AnsiString("0") + AnsiString((int)d.da_year);

    Time = hora + AnsiString(":") + min + AnsiString(":") + seg;
    Data = dia + AnsiString("/") + mes + AnsiString("/") + ano;
    return (AnsiString(Time) + AnsiString(" - ") + AnsiString(Data));
}
void Diagrama::NewObjectView(ViewObjeto *Novo)
{
    ListaViewObjetos.InsereLista(Novo);
    *WillConnect = 0;
}
ViewObjeto* Diagrama::getSelectedObject()
{
	return Selecionado;
}
ViewConector* Diagrama::getSelectedConnector()
{
	return SelecionadoConn;
}

ViewObjeto* Diagrama::CriaViewObjeto(int Type, float Xpos, float Ypos, TPaintBox *Board)
{
    Objeto *corpo;
    ViewObjeto *Temp;
    FabricaViews fabrica;

    Temp = fabrica.FabricaViewObjetos(Type);

    // Pego o objeto no projeto
    corpo = (Objeto*)Project->GetObjeto("", Type);
    corpo->SetParent(GetParent());
    // Faço a view apontar para o objeto
    Temp->SetCorpo(corpo);

    Temp->Inicializa(Xpos, Ypos);
    Temp->AjustaNome(Board);

    NewObjectView(Temp);
    *Modified = true;
    return Temp;
}
void Diagrama::NewViewConector(ViewConector *Novo)
{
    ListaViewConectores.InsereLista(Novo);

    *ExisteOrigem = false;
    *WillConnect = 0;
    *Modified = true;
}
void Diagrama::DeleteObjectView(ViewObjeto *VaiMorrer, TPaintBox *Board)
{
	// Apaga o objeto apontado por VaiMorrer e todos os
	// conectores ligados à ele...

    ListaViewConectores.RemovePorViewObjeto(VaiMorrer);
	ListaViewObjetos.RemoveLista(VaiMorrer);

	*Modified = true;
    VaiMorrer = 0;
}
void Diagrama::SelectAll()
{
	GrupoObj.Esvazia();
    GrupoConn.Esvazia();
    EsvaziaLista(ListaPontosSelecionados);    

    FilaConectores c;
    FilaObjetos p;

    if(!ListaViewConectores.ListaVazia())
    {
        for(c = ListaViewConectores.listaPTR; c!=0; c = c->Next)
        {
            GrupoConn.InsereLista(c->Conn);
        }
    }

    if(!ListaViewObjetos.ListaVazia())
    {
        for(p = ListaViewObjetos.listaPTR; p!=0; p = p->Next)
        {
            GrupoObj.InsereLista(p->Obj);
            p->Obj->Agrupa();
        }
    }
}
void Diagrama::DeleteSelection(TPaintBox *Board)
{
	// Apaga todos os objetos selecionados...

    FilaObjetos p;

	for(p = GrupoObj.listaPTR; p!=0; p = p->Next)
    {
	    ListaViewConectores.RemovePorViewObjeto(p->Obj);
		ListaViewObjetos.RemoveLista(p->Obj);
    }

    GrupoObj.Esvazia();

	*Modified = true;
}
void Diagrama::DeleteViewConector(TPaintBox *Board)
{
    if (SelecionadoConn != NULL)
    {
        if (SelecionadoConn->GetViewPointingAtMe() != NULL)
        {
            SelecionadoConn->GetViewPointingAtMe()->SetConectorViewEndLine(NULL);
            ListaViewConectores.Apaga(SelecionadoConn->GetViewPointingAtMe());
            SelecionadoConn->SetViewPointingAtMe(NULL);
        }

        if (SelecionadoConn->GetConectorViewEndLine() != NULL)
        {
            SelecionadoConn->GetConectorViewEndLine()->SetViewPointingAtMe(NULL);
        }

        ListaViewConectores.Apaga(SelecionadoConn);
        SelecionadoConn = NULL;
        *Modified = true;
    }
}
void Diagrama::Delete(TPaintBox *Board)
{
    if(*WillConnect != 0)
    {
        *WillConnect = 0;
        Refresh(Board->Canvas);
        Paint(Board->Canvas);
        return;
    }

    int Resp;

    Resp = MessageBox(0, "Are you sure you want to delete your selection?", "Attention", MB_YESNO | MB_ICONQUESTION);
    if(Resp == 7)
    {
        return;
    }

    *Modified = true;

    if(Selecionado != 0)
	    DeleteObjectView(Selecionado, Board);
    else if(!GrupoObj.ListaVazia())
	    DeleteSelection(Board);

    DeleteViewConector(Board);

    Refresh(Board->Canvas);
    Paint(Board->Canvas);
}
void Diagrama::SetGroupFillColor(TColor color)
{
    FilaObjetos p;

    if(!GrupoObj.ListaVazia())
    {
        for(p = GrupoObj.listaPTR; p!=0; p = p->Next)
        {
           	p->Obj->SetFillColor(color);
        }
        setModified(true);
    }
}
void Diagrama::SetGroupLineColor(TColor color)
{
    FilaObjetos p;

    if(!GrupoObj.ListaVazia())
    {
        for(p = GrupoObj.listaPTR; p!=0; p = p->Next)
        {
           	p->Obj->SetLineColor(color);
        }
        setModified(true);
    }
}
void Diagrama::SetGroupFont(TFont *font)
{
    FilaObjetos p;

    if(!GrupoObj.ListaVazia())
    {
        for(p = GrupoObj.listaPTR; p!=0; p = p->Next)
        {
           	p->Obj->SetFont(font);
        }
	    setModified(true);
    }
}
void Diagrama::Paint(TCanvas *Board)
{
    FilaConectores c;
    FilaObjetos p;

    Board->Pen->Mode = pmCopy;

    SetZoomMode(Board);

    if(!ListaViewConectores.ListaVazia())
    {
        for(c = ListaViewConectores.listaPTR; c!=0; c = c->Next)
        {
            (c->Conn)->Paint(Board, clBlack);
        }
    }

    if(!ListaViewObjetos.ListaVazia())
    {
        for(p = ListaViewObjetos.FinalListaPTR; p!=0; p = p->Prior)
        {
            (p->Obj)->Paint(Board);
        }
    }

    // Pinto os quadradinhos da seleção do conector que está selecionado
    if(SelecionadoConn != NULL)
    {
        SelecionadoConn->PintaSelecao(Board, SelecionadoConn->GetCorpo()->GetConectorEndLine() != NULL);
    }
    else if (ListaPontosSelecionados->Count > 0)
    {
        Board->Pen->Mode = pmCopy;
        Board->Pen->Color = clBlack;
        Board->Pen->Style = psSolid;
        Board->Brush->Color = clBlack;
        Board->Brush->Style = bsSolid;

        TPoint *ponto;
        for (int i=0; i<ListaPontosSelecionados->Count; i++)
        {
            ponto = (TPoint*)ListaPontosSelecionados->Items[i];
            Board->Rectangle(ponto->x - 2, ponto->y - 2 , ponto->x + 3, ponto->y + 3);
        }
    }
}
void Diagrama::MouseDown(TPaintBox *Board, float X, float Y, TMouseButton Button, TShiftState Shift)
{
    FilaObjetos p;
    bool acheiObjeto = false;

    Selecionado = 0;

    SetZoomMode(Board->Canvas);

    // Se não vai conectar nada nem inserir nada,
    // mas há objetos selecionados, então...
    if(!GrupoObj.ListaVazia() && !(*WillConnect) && !(*WillInsert))
    {
        // ...Se clicou sobre algum dos objetos selecionados, então...
    	if(PreparaArrastaGrupo(Board, X, Y))
        {
            *Down = false;
            *DownGroup = true;

            // Apago os quadradinhos dos pontos de quebra selecionados...
            if (ListaPontosSelecionados->Count > 0)
            {
                Board->Canvas->Pen->Mode = pmCopy;
                Board->Canvas->Pen->Color = clWhite;
                Board->Canvas->Pen->Style = psSolid;
                Board->Canvas->Brush->Color = clWhite;
                Board->Canvas->Brush->Style = bsSolid;

                TPoint *ponto;
                for (int i=0; i<ListaPontosSelecionados->Count; i++)
                {
                    ponto = (TPoint*)ListaPontosSelecionados->Items[i];
                    Board->Canvas->Rectangle(ponto->x - 2, ponto->y - 2 , ponto->x + 3, ponto->y + 3);
                }
            }

            ArrastaGrupo(Board, X, Y);
    	    return;
        }
        else
        {
    	    GrupoObj.Esvazia();
            GrupoConn.Esvazia();

            EsvaziaLista(ListaPontosSelecionados);
        }
    }
    else
    {
    	GrupoObj.Esvazia();
        GrupoConn.Esvazia();
        EsvaziaLista(ListaPontosSelecionados);        
    }

    if(SelecionadoConn != NULL)    // Se há um conector selecionado...
    {
        // Trato a locomoção do ponto base da reta selecionada...

    	int X1, Y1, X2, Y2;

        X1 = *SelecionadoConn->ViewA->Xpos + *SelecionadoConn->ViewA->Width/2 - *SelecionadoConn->AXOffset;
        Y1 = *SelecionadoConn->ViewA->Ypos - *SelecionadoConn->ViewA->Height/2 - *SelecionadoConn->AYOffset;

        if (SelecionadoConn->GetConectorViewEndLine() == NULL)
        {
    	    X2 = *SelecionadoConn->ViewB->Xpos + *SelecionadoConn->ViewB->Width/2 - *SelecionadoConn->BXOffset;
    	    Y2 = *SelecionadoConn->ViewB->Ypos - *SelecionadoConn->ViewB->Height/2 - *SelecionadoConn->BYOffset;
        }

        if(InsideRect(X, Y, X1 - 2, Y1 - 2 , X1 + 3, Y1 + 3, 0))
        {
            *Modified = true;
            *DownOffsetA = true;
            *DownOffsetB = false;
    	    *Xant = -2000;
    	    *Yant = -2000;

            SelecionadoConn->SetSelection(false);
            SelecionadoConn->Paint(Board->Canvas, clWhite);
            SelecionadoConn->SetSelection(true);
            SelecionadoConn->SetDragging(true);

            if(SelecionadoConn->GetViewPointingAtMe() != 0)
            {
                SelecionadoConn->GetViewPointingAtMe()->SetSelection(false);
                SelecionadoConn->GetViewPointingAtMe()->Paint(Board->Canvas, clWhite);
                SelecionadoConn->GetViewPointingAtMe()->SetSelection(true);
                SelecionadoConn->GetViewPointingAtMe()->SetDragging(true);
            }

            SelecionadoConn->ViewA->Paint(Board->Canvas);

            MoveConexao(Board, X, Y, *SelecionadoConn->BXOffset, *SelecionadoConn->BYOffset, true);
            return;
        }
        else if(InsideRect(X, Y, X2 - 2, Y2 - 2 , X2 + 3, Y2 + 3, 0) && SelecionadoConn->GetConectorViewEndLine() == NULL)
        {
            *Modified = true;
            *DownOffsetB = true;
            *DownOffsetA = false;
    	    *Xant = -2000;
    	    *Yant = -2000;

            SelecionadoConn->SetSelection(false);
            SelecionadoConn->Paint(Board->Canvas, clWhite);
            SelecionadoConn->SetSelection(true);
            SelecionadoConn->SetDragging(true);

            if(SelecionadoConn->GetViewPointingAtMe() != 0)
            {
                SelecionadoConn->GetViewPointingAtMe()->SetSelection(false);
                SelecionadoConn->GetViewPointingAtMe()->Paint(Board->Canvas, clWhite);
                SelecionadoConn->GetViewPointingAtMe()->SetSelection(true);
                SelecionadoConn->GetViewPointingAtMe()->SetDragging(true);
            }

            SelecionadoConn->ViewB->Paint(Board->Canvas);

            MoveConexao(Board, X, Y, *SelecionadoConn->AXOffset, *SelecionadoConn->AYOffset, false);
            return;
        }
    }
    else
        SelecionadoConn = 0;

    if(!(*WillConnect) && !(*WillInsert))   // Se não vai conectar nem inserir, então...
    {
        *ScreenUpdateLock = true;

        if(!ListaViewObjetos.ListaVazia())
        {
            for(p = ListaViewObjetos.listaPTR; p!=0; p = p->Next)
            {
                // Busca o Objeto na Posição (X,Y)

                if(p->Obj->isHere(X,Y) == true && !acheiObjeto)
                {
                    Selecionado = p->Obj;

                    acheiObjeto = true;
                    *Down = true;
                    *DownGroup = false;

                    *Xant = -2000;
                    *Yant = -2000;

                    *WillResize = p->Obj->isResize(X,Y);
                    if(*WillResize != 0 && *p->Obj->isSelected)
                    {
                         // O objeto será redimensionado...
                         Redimensionado = p->Obj;
                         *ScreenUpdateLock = false;
                         Redimensiona(Board, X, Y);
                         return;
                    }

                    Refresh(Board->Canvas);

                    ListaViewConectores.UnSelectAllConnectors();

                    *WillResize = 0;
                    p->Obj->Selected();
                    *p->Obj->Visible = false;

                    Board->Canvas->Pen->Mode = pmCopy;
					Board->Canvas->Pen->Color = clBlack;
                    Board->Canvas->Pen->Style = psSolid;
                    Board->Canvas->Font = p->Obj->TextFont;

                    p->Obj->Drag(Board, *p->Obj->Xpos + *p->Obj->Width/2, *p->Obj->Ypos - *p->Obj->Height/2);

                    // Deslocamento em relação ao centro do Objeto arrastado:
                    *XOffset = X - (*p->Obj->Xpos + *p->Obj->Width/2);
                    *YOffset = Y - (*p->Obj->Ypos - *p->Obj->Height/2);

                    *Modified = true;
                }
                else
                {
                    *(p->Obj->isSelected) = false;
                    *(p->Obj->Visible) = true;
                }
            }
            if(!acheiObjeto)
            {
                ListaViewConectores.UnSelectAllConnectors();

                // Procuro por um conector na posição (X, Y)
                SelecionadoConn = BuscaViewConector(X, Y);
                if(SelecionadoConn == 0)
                {
                    *SelectGroup = true;
                    // Esvazia e tiro a seleção de todos os
                    // objetos da lista GrupoObj
                    GrupoObj.Esvazia();
                    GrupoConn.Esvazia();
                    EsvaziaLista(ListaPontosSelecionados);
                    
                    Base->x = X;
                    Base->y = Y;
                    *Xant = -2000;
                    *Yant = -2000;

                    *Down = false;
                }
                else
                {
                    *DownConnector = true;
                    *FirstMove = true;

                    // Procuro por algum ponto sob o clique...
                    PontoSelecionado = SelecionadoConn->GetPontoAt(X, Y);

                    if (PontoSelecionado == NULL)
                    {
                        PontoSelecionado = new PontoQuebra();
                        PontoSelecionado->SetIdDono(SelecionadoConn->GetCorpo()->GetId());
                        
                        PontoSelecionado->x = -2000;
                        PontoSelecionado->y = -2000;
                    }
                }
                Refresh(Board->Canvas);
            }

            Paint(Board->Canvas);
            *ScreenUpdateLock = false;
        }
    }
    else if (*WillConnect && !*ExisteOrigem)
    {
        bool Taqui, achei = false;
        // Haverá uma conexão

        FabricaGerenteConexao fabrica;
        ISemanticaConexao *gerente;
        gerente = fabrica.FabricaGerente(*WillConnect);

        for(p = ListaViewObjetos.listaPTR; p!=0; p = p->Next)
        {
            // Busca o Objeto na Posição (X,Y)
            Taqui = p->Obj->isHere(X,Y);
            if(Taqui && gerente->CanStartAtObject(p->Obj->GetCorpo()->GetType()))
            {
                Origem = p->Obj;
                p->Obj->Selected();
                Selecionado = p->Obj;
                *ExisteOrigem = true;
                *Xant = *p->Obj->Xpos + *p->Obj->Width/2;
                *Yant = *p->Obj->Ypos - *p->Obj->Height/2;
                achei = true;
                break;
            }
            else if(Taqui && !gerente->CanStartAtObject(p->Obj->GetCorpo()->GetType()))
            {
                *WillConnect = 0;
                *ExisteOrigem = false;
                p->Obj->Selected();
            }
            else
                *p->Obj->isSelected = false;
        }
        if(!achei)
        {
            *WillConnect = 0;
            *ExisteOrigem = false;
        }
        *Modified = true;
        delete gerente;
    }
    else if(*WillConnect && *ExisteOrigem)
    {
        bool Achei = false;

        *ScreenUpdateLock = true;

        // Fechando a conexão
        FabricaGerenteConexao fabrica;
        ISemanticaConexao *gerente;
        gerente = fabrica.FabricaGerente(*WillConnect);

        if (gerente->CanPointToObject())
        {
            for(p = ListaViewObjetos.listaPTR; p!=0; p = p->Next)
            {
                // Busca o Objeto na Posição (X,Y)
                if(p->Obj->isHere(X,Y)==true && p->Obj != Origem)
                {
                    if(ListaViewConectores.ExisteConexao(Origem, p->Obj))
                    {
                         *WillConnect = 0;
                         *ExisteOrigem = false;
                         MessageBox(0, "Only one conection can exist between two objects at the same time.", "Attention", MB_OK | MB_ICONEXCLAMATION);
                         Achei = true;
                         break;
                    }
                    else if (!gerente->CanEndAtObject(p->Obj->GetCorpo()->GetType()))
                    {
                         *WillConnect = 0;
                         *ExisteOrigem = false;
                         Achei = true;
                         break;
                    }

                    ViewConector *view;
                    Connector *conector;
                    FabricaViews fabrica;

                    conector = (Connector*)Project->GetConector(Origem->GetCorpo(), p->Obj->GetCorpo(), *WillConnect);
                    view = fabrica.FabricaViewConectores(*WillConnect);
                    view->SetCorpo(conector);
                    view->ConnectViews(Origem,p->Obj);

                    if (pontosReta != NULL)
                    {
                        view->ClonePontos(pontosReta);
                        CopiaPontosConector(pontosReta);

                        // Apago a lista de pontos para garantir que ninguém mais utilizará
                        // estes meus pontos.
                        delete pontosReta;
                        pontosReta = NULL;
                    }

                    NewViewConector(view);
                    Achei = true;
                    *Origem->isSelected = false;
                    p->Obj->Selected();
                    Selecionado = p->Obj;
                    break;
                }
            }
        }

        if (gerente->CanPointToConnector() && !Achei)   // Pode apontar para outros conectores
        {
            ViewConector *Fim;
            Fim = BuscaViewConector(X, Y);
            if(Fim == 0)
            {
            	Achei = false;
            }
            else if(gerente->CanPointToConnector(Fim->GetCorpo()->GetType())) // Se pode apontar para o conector Fim...
            {
                if(Fim->GetViewPointingAtMe() != NULL)
                {
                    AnsiString Msg;
                    Msg = "The association between ";
                    Msg += Fim->ViewA->GetCorpo()->GetName();
                    Msg += " and ";
                    Msg += Fim->ViewB->GetCorpo()->GetName();
                    Msg += " already has an association class: ";
                    Msg += Fim->GetViewPointingAtMe()->ViewA->GetCorpo()->GetName();
                    MessageBox(0, Msg.c_str(), "Error", MB_OK);
                }
                else
                {
                    ViewConector *view;
                    FabricaViews fabrica;
                    Connector *conector;

                    conector = (Connector*)Project->GetConector(Origem->GetCorpo(), Fim->GetCorpo(), *WillConnect);

	                view = fabrica.FabricaViewConectores(*WillConnect);
                    view->SetCorpo(conector);
                    view->ConnectViews(Origem, NULL);
                    view->SetConectorViewEndLine(Fim);

                    if (pontosReta != NULL)
                    {
                        view->ClonePontos(pontosReta);
                        CopiaPontosConector(pontosReta);

                        // Apago a lista de pontos para garantir que ninguém mais utilizará
                        // estes meus pontos.
                        delete pontosReta;
                        pontosReta = NULL;
                    }

	                Fim->SetViewPointingAtMe(view);
                    Fim->GetCorpo()->pointingAtMe = view->GetCorpo();

                    NewViewConector(view);
                    Achei = true;
                    *Origem->isSelected = false;
                }
            }
        }

        // Verifica se clicou no background
        if(!Achei)
        {
            if (Button == mbLeft)
            {
                if (pontosReta == NULL)
                    pontosReta = new TList();

                PontoQuebra *novo;
                novo = new PontoQuebra();
                novo->x = X;
                novo->y = Y;

                pontosReta->Add(novo);

                *ScreenUpdateLock = false;
                return;
            }
            else
            {
                *WillConnect = 0;
                *ExisteOrigem = false;
            }
        }
        *Modified = true;

        Board->Canvas->Pen->Mode = pmCopy;
        Board->Canvas->Pen->Color = clWhite;
        Board->Canvas->Brush->Color = clWhite;
        Refresh(Board->Canvas);
        Paint(Board->Canvas);
        *ScreenUpdateLock = false;
        delete gerente;
    }
    else if(*WillInsert)
    {
         AnsiString Name = "";
         int Xa, Ya;
         Xa = X;
         Ya = Y;
         Board->Canvas->Pen->Mode = pmCopy;
         Board->Canvas->Pen->Mode = pmXor;
         Board->Canvas->Rectangle(Xa - 15, Ya + 15, Xa + 15, Ya - 15);
         Board->Canvas->Pen->Mode = pmCopy;

         ViewObjeto *Novo;
         bool Inseriu;

         Novo = CriaViewObjeto(*WillInsert, X - 15, Y - 15, Board);

         FabricaControlador fabrica;
         IControladorObjeto *controller;
         controller = fabrica.CriaControladorObjeto(Novo->GetCorpo()->GetType());
         Inseriu = controller->Execute(Novo->GetCorpo());

         if(!Inseriu)
             DeleteObjectView(Novo, Board);
         else
         {
             controller->EfetuaAjustesView(Novo, Board);
             Project->NotificaInclusaoObjeto((TObject*)Novo->GetCorpo());
         }

         *WillInsert = 0;

         Board->Cursor = crArrow;

	     Refresh(Board->Canvas);
    	 Paint(Board->Canvas);
    }
}
void Diagrama::MouseMove(TPaintBox *Board, float X, float Y)
{
    SetaCursor(Board, X, Y);

    // Busco a ação do usuário:

    SetZoomMode(Board->Canvas);

    if(*Down)  // Estou arrastando um objeto
    {
        if(*WillResize != 0)
        {
            Redimensiona(Board, X, Y);
        }
        else
        {
            Arrasta(Board, X, Y);
        }
    }
    else if(*DownGroup)
    {
        ArrastaGrupo(Board, X, Y);
    }
    else if(*DownConnector)
    {
        MovePontoConector(Board, X, Y);
    }
    else if(*SelectGroup)
    {
        SelecionaGrupo(Board, X, Y);
    }
    else if(*WillConnect != 0 && *ExisteOrigem == true)
    {
        FinalizaConexao(Board, X, Y);
    }
    else if(*WillInsert)
    {
        Board->Canvas->Pen->Mode = pmXor;
        Board->Canvas->Pen->Color = clWhite;
        Board->Canvas->Pen->Style = psDot;
        Board->Canvas->Brush->Color = clBlack;

        Board->Canvas->Rectangle(*Xant, *Yant, *Xant + 30, *Yant - 30);
        *Xant = X - 15;
        *Yant = Y + 15;
        Board->Canvas->Rectangle(*Xant, *Yant, *Xant + 30, *Yant - 30);
    }
    else if(*DownOffsetA || *DownOffsetB)
    {
	if(*DownOffsetA)
        {
            if(X > (*SelecionadoConn->ViewA->Xpos + *SelecionadoConn->ViewA->Width - 1))
            	X = (*SelecionadoConn->ViewA->Xpos + *SelecionadoConn->ViewA->Width - 1);
            if(X < (*SelecionadoConn->ViewA->Xpos + 1))
            	X = (*SelecionadoConn->ViewA->Xpos + 1);
            if(Y < (*SelecionadoConn->ViewA->Ypos - *SelecionadoConn->ViewA->Height + 1))
            	Y = (*SelecionadoConn->ViewA->Ypos - *SelecionadoConn->ViewA->Height + 1);
            if(Y > (*SelecionadoConn->ViewA->Ypos - 1))
            	Y = (*SelecionadoConn->ViewA->Ypos - 1);

            MoveConexao(Board, X, Y, *SelecionadoConn->BXOffset, *SelecionadoConn->BYOffset, true);
        }
        else
        {
            if(X > (*SelecionadoConn->ViewB->Xpos + *SelecionadoConn->ViewB->Width - 1))
            	X = (*SelecionadoConn->ViewB->Xpos + *SelecionadoConn->ViewB->Width - 1);
            if(X < (*SelecionadoConn->ViewB->Xpos + 1))
               	X = (*SelecionadoConn->ViewB->Xpos + 1);
            if(Y < (*SelecionadoConn->ViewB->Ypos - *SelecionadoConn->ViewB->Height + 1))
            	Y = (*SelecionadoConn->ViewB->Ypos - *SelecionadoConn->ViewB->Height + 1);
            if(Y > (*SelecionadoConn->ViewB->Ypos - 1))
            	Y = (*SelecionadoConn->ViewB->Ypos - 1);

            MoveConexao(Board, X, Y, *SelecionadoConn->AXOffset, *SelecionadoConn->AYOffset, false);
        }
    }
}
void Diagrama::MouseUp(TPaintBox *Board, float X, float Y)
{
    SetZoomMode(Board->Canvas);

    if(*Down)
    {
        if(*WillResize != 0)
        {
            AcertaNovoTamanho(Board);
        }
        if(*Xant == -2000) // Não moveu o objeto selecionado
        {
            Board->Canvas->Pen->Mode = pmCopy;
            *Selecionado->Visible = true;
	        Selecionado->Paint(Board->Canvas);
            *Down = false;
        }
        else
        {
            setAllVisible(Board);
        }
    }
    else if(*DownConnector)
    {
        SoltaPontoSelecionado(Board, X, Y);
    }
    else if(*SelectGroup)
    {
        AgrupaObjetos(Board, X, Y);
    }
    else if(*DownGroup)
    {
    	FilaConectores c;

		*DownGroup = false;

	    if(!GrupoConn.ListaVazia())
    	{
        	for(c = GrupoConn.listaPTR; c!=0; c = c->Next)
          	{
                c->Conn->SetDragging(false);
	        }
    	}

	    Board->Canvas->Pen->Mode = pmCopy;
        Refresh(Board->Canvas);
        Paint(Board->Canvas);
    }
    else if(*DownOffsetA || *DownOffsetB)
    {
		*DownOffsetA = false;
        *DownOffsetB = false;
        SelecionadoConn->SetDragging(false);
        if(SelecionadoConn->GetViewPointingAtMe() != 0)
        {
	        SelecionadoConn->GetViewPointingAtMe()->SetSelection(false);
	        SelecionadoConn->GetViewPointingAtMe()->SetDragging(false);
        }
        Origem = 0;
        Refresh(Board->Canvas);
        Paint(Board->Canvas);
    }
}
void Diagrama::AgrupaObjetos(TPaintBox *Board, float X, float Y)
{
    bool Pinta = true;

    Selecionado = NULL;
    SelecionadoConn = NULL;

    // Apaga o último retângulo desenhado
    if(*Xant != -2000)
        Board->Canvas->Rectangle(Base->x, Base->y, *Xant, *Yant);
    else
        Pinta = false;

    Board->Canvas->Pen->Mode = pmCopy;

    if(!Pinta)
    {
        *SelectGroup = false;
        return;
    }

    // Os pontos do retângulo são:
    // Superior: Base.x e Base.y
    // Inferior: *Xant e *Yant

    FilaObjetos p, r;
    FilaConectores c;

    // A, B, C e D são os pontos das quinas
    // do Objeto
    //    B-----C
    //    |     |
    //    A-----D
    TPoint A, B, C, D;

    Pinta = false;
    for(p = ListaViewObjetos.listaPTR; p != 0; p = p->Next)
    {
        A.x = *p->Obj->Xpos;
        A.y = *p->Obj->Ypos;
        B.x = *p->Obj->Xpos;
        B.y = *p->Obj->Ypos - *p->Obj->Height;
        C.x = *p->Obj->Xpos + *p->Obj->Width;
        C.y = *p->Obj->Ypos - *p->Obj->Height;
        D.x = *p->Obj->Xpos + *p->Obj->Width;
        D.y = *p->Obj->Ypos;

        // Os quatro pontos do Objeto devem estar dentro o
        // retângulo que o usuário traçou...
        if(InsideRect(A.x, A.y, Base->x, Base->y, *Xant, *Yant, 1.0) &&
          InsideRect(B.x, B.y, Base->x, Base->y, *Xant, *Yant, 1.0) &&
          InsideRect(C.x, C.y, Base->x, Base->y, *Xant, *Yant, 1.0) &&
          InsideRect(D.x, D.y, Base->x, Base->y, *Xant, *Yant, 1.0))
        {
            GrupoObj.InsereLista(p->Obj);
            p->Obj->Agrupa();
            Pinta = true;
        }
        *p->Obj->isSelected = false;
    }

    // Procuro pelos pontos de quebra dentro do quadrado:
    PontoQuebra *ponto;

    TStringList *ListaConectores;
    ListaConectores = new TStringList();
    // Para cada ponto existente...   
    for (int i=0; i<ListaPontosConectores->Count; i++)
    {
        ponto = (PontoQuebra*)ListaPontosConectores->Items[i];
        // ...se estiver dentro dos limites do quadrado, então...
        if (InsideRect(ponto->x, ponto->y, Base->x, Base->y, *Xant, *Yant, 1.0))
        {
            ListaPontosSelecionados->Add(ponto);
            if (ListaConectores->IndexOf(AnsiString((int)ponto->GetIdDono())) == -1)
            {
                ListaConectores->Add(AnsiString(ponto->GetIdDono()));
            }
        }
    }

    // Buscar conectores e colocá-los na lista GrupoConn
    int indice;

    if(Pinta) // Se algum objeto estiver dentro do retângulo, então...
    {
        for(c = ListaViewConectores.listaPTR; c != 0; c = c->Next)
        {
            p = GrupoObj.listaPTR;
            r = GrupoObj.FinalListaPTR;

            // Busca bidirecional:
            for(; p != r && p!=r->Next; p = p->Next, r = r->Prior)
            {
                if(c->Conn->ViewA == p->Obj || c->Conn->ViewB == p->Obj || c->Conn->ViewA == r->Obj || c->Conn->ViewB == r->Obj)
                {
                    GrupoConn.InsereLista(c->Conn);

                    // Se o conector em questão (c->Conn) já existir na lista dos donos dos pontos
                    // então preciso apagá-lo porque ele já foi inserido.
                    indice = ListaConectores->IndexOf(AnsiString(c->Conn->GetCorpo()->GetId()));
                    if (indice != -1)
                        ListaConectores->Delete(indice);

                    // Se existir algum conector apontando para o conector c->Conn, então este também precisa
                    // ser inserido.
                    if(c->Conn->GetViewPointingAtMe() != NULL && !GrupoObj.buscaObjeto(c->Conn->GetViewPointingAtMe()->ViewA->GetCorpo()->GetId()))
                    {
                        GrupoConn.InsereLista(c->Conn->GetViewPointingAtMe());

                        // Se o conector em questão (c->Conn->GetViewPointingAtMe()) já existir na
                        // lista dos donos dos pontos então preciso apagá-lo porque ele já foi inserido.
                        indice = ListaConectores->IndexOf(AnsiString(c->Conn->GetViewPointingAtMe()->GetCorpo()->GetId()));
                        if (indice != -1)
                            ListaConectores->Delete(indice);
                    }
                    break;
                }
            }
            if(p == r) // Só há um elemento em GrupoObj...
            {
                if(c->Conn->ViewA == p->Obj || c->Conn->ViewB == p->Obj || c->Conn->ViewA == r->Obj || c->Conn->ViewB == r->Obj)
                {
                    GrupoConn.InsereLista(c->Conn);

                    // Se o conector em questão (c->Conn) já existir na lista dos donos dos pontos
                    // então preciso apagá-lo porque ele já foi inserido.
                    indice = ListaConectores->IndexOf(AnsiString(c->Conn->GetCorpo()->GetId()));
                    if (indice != -1)
                        ListaConectores->Delete(indice);

                    // Se existir algum conector apontando para o conector c->Conn, então este também precisa
                    // ser inserido.
                    if(c->Conn->GetViewPointingAtMe() != NULL && !GrupoObj.buscaObjeto(c->Conn->GetViewPointingAtMe()->ViewA->GetCorpo()->GetId()))
                    {
                        GrupoConn.InsereLista(c->Conn->GetViewPointingAtMe());

                        // Se o conector em questão (c->Conn->GetViewPointingAtMe()) já existir na
                        // lista dos donos dos pontos então preciso apagá-lo porque ele já foi inserido.
                        indice = ListaConectores->IndexOf(AnsiString(c->Conn->GetViewPointingAtMe()->GetCorpo()->GetId()));
                        if (indice != -1)
                            ListaConectores->Delete(indice);
                    }
                    continue;
                }
            }
        }

        // Se existir algum conector que não possui nenhum objeto no grupo dos selecionados, então...
        if (ListaConectores->Count > 0)
        {
            for (int i=0; i < ListaConectores->Count; i++)
            {
                for(c = ListaViewConectores.listaPTR; c != 0; c = c->Next)
                {
                    if (c->Conn->GetCorpo()->GetId() == (ListaConectores->Strings[i]).ToInt())
                    {
                        GrupoConn.InsereLista(c->Conn);
                        break;
                    }
                }
            }
        }

        Refresh(Board->Canvas);
        Paint(Board->Canvas);
    }
    delete ListaConectores;
    *SelectGroup = false;
}
void Diagrama::MoveConexao(TPaintBox *Board, int X, int Y, int dx, int dy, bool origem)
{
    Board->Canvas->Pen->Mode = pmXor;
    Board->Canvas->Pen->Color = clWhite;
    Board->Canvas->Pen->Style = psDot;
    Board->Canvas->Brush->Color = clWhite;
    Board->Canvas->Brush->Style = bsClear;

    SetZoomMode(Board->Canvas);

    if(*Xant != -2000)
    {
        SelecionadoConn->Paint(Board->Canvas, clWhite);
        if(SelecionadoConn->GetViewPointingAtMe() != NULL)
            SelecionadoConn->GetViewPointingAtMe()->Paint(Board->Canvas, clWhite);
    }

    // Transfiro o ponto antigo para o novo
    *Xant = X;
    *Yant = Y;

    // Meio do objeto...
    int X1, Y1;
    if(origem)
    {
        X1 = *SelecionadoConn->ViewA->Xpos + *SelecionadoConn->ViewA->Width/2;
        Y1 = *SelecionadoConn->ViewA->Ypos - *SelecionadoConn->ViewA->Height/2;
    }
    else
    {
        X1 = *SelecionadoConn->ViewB->Xpos + *SelecionadoConn->ViewB->Width/2;
        Y1 = *SelecionadoConn->ViewB->Ypos - *SelecionadoConn->ViewB->Height/2;
    }

    SelecionadoConn->setOffset(X1-X, Y1-Y, origem);

    SelecionadoConn->Paint(Board->Canvas, clWhite);

    if(SelecionadoConn->GetViewPointingAtMe() != 0)
        SelecionadoConn->GetViewPointingAtMe()->Paint(Board->Canvas, clWhite);
}
void Diagrama::FinalizaConexao(TPaintBox *Board, float X, float Y)
{
    // Linha entre o Objeto Origem e o Mouse

    Board->Canvas->Pen->Mode = pmXor;
    Board->Canvas->Pen->Color = clWhite;
    Board->Canvas->Pen->Style = psDot;
    Board->Canvas->Brush->Color = clBlack;

    SetZoomMode(Board->Canvas);

    TPoint origem, destino;

    if (pontosReta == NULL)
    {
        origem.x = *Origem->Xpos + *Origem->Width/2;
        origem.y = *Origem->Ypos - *Origem->Height/2;
    }
    else
    {
        origem.x = ((TPoint*)pontosReta->Items[pontosReta->Count-1])->x;
        origem.y = ((TPoint*)pontosReta->Items[pontosReta->Count-1])->y;
    }

    Board->Canvas->MoveTo(origem.x, origem.y);
    Board->Canvas->LineTo(*Xant, *Yant);

    // Transfiro o ponto antigo para o novo
    *Xant = X;
    *Yant = Y;

    Board->Canvas->MoveTo(origem.x, origem.y);
    Board->Canvas->LineTo(X,Y);
}

ViewConector* Diagrama::BuscaViewConector(float X, float Y)
{
    FilaConectores c;
    if(!ListaViewConectores.ListaVazia())
    {
        float diff;
        for(c = ListaViewConectores.listaPTR; c!=0; c = c->Next)
        {
            if(c->Conn->GetCorpo()->GetConectorEndLine() == NULL)
            {
                // Se não estiver ligado a outro
                // Conector, então...
	        diff = c->Conn->DistanciaAoPonto(X, Y);
            }
            else
            {
	        diff = c->Conn->DistanciaAoPonto(X, Y);
            }

            if(diff <= 4.0)
            {
                return c->Conn;
            }
        }
    }
    return 0;
}
void Diagrama::Arrasta(TPaintBox *Board, float X, float Y)
{
    FilaConectores c;

    *Selecionado->Visible = true;
    Board->Canvas->Pen->Mode = pmXor;
    Board->Canvas->Pen->Color = clWhite;
    Board->Canvas->Pen->Style = psSolid;
    Board->Canvas->Brush->Color = clBlack;

    SetZoomMode(Board->Canvas);

    // Pinto os Conectores ligados a ele
    if(*Xant == -2000) // Apaga o primeiro arraste
    {
         Board->Canvas->Pen->Mode = pmWhite;
    }

    if(!ListaViewConectores.ListaVazia())
    {
        for(c = ListaViewConectores.listaPTR; c!=0; c = c->Next)
        {
            *c->Conn->Visible = true;
            if(c->Conn->ViewA == Selecionado || c->Conn->ViewB == Selecionado)
            {
                c->Conn->Paint(Board->Canvas, clWhite);
                if(c->Conn->GetViewPointingAtMe() != NULL)
                {
                    c->Conn->GetViewPointingAtMe()->Paint(Board->Canvas, clWhite);
                }
            }
        }
    }

    if(*Xant != -2000) // Não mostra o primeiro arraste
    {
        // Apago com o XOR
        Board->Canvas->Pen->Style = psDot;
        Board->Canvas->Brush->Style = bsClear;

        Board->Canvas->Font = Selecionado->TextFont;
        Selecionado->Drag(Board, *Xant, *Yant);
    }
    else
    {
        // Apago o objeto em sua posição antes do arraste...
        Board->Canvas->Pen->Style = psSolid;
        Board->Canvas->Font = Selecionado->TextFont;
        Selecionado->Drag(Board, *Selecionado->Xpos + *Selecionado->Width/2, *Selecionado->Ypos - *Selecionado->Height/2);
        Board->Canvas->Pen->Mode = pmWhite;
        if(!ListaViewConectores.ListaVazia())
        {
            for(c = ListaViewConectores.listaPTR; c!=0; c = c->Next)
            {
                if(c->Conn->ViewA == Selecionado || c->Conn->ViewB == Selecionado)
                {
                     c->Conn->SetDragging(true);
                     c->Conn->Paint(Board->Canvas, clWhite);
                     if(c->Conn->GetViewPointingAtMe() != NULL)
                     {
                         c->Conn->GetViewPointingAtMe()->SetDragging(true);
                         c->Conn->GetViewPointingAtMe()->Paint(Board->Canvas, clWhite);
                     }
                }
            }
        }
        Board->Canvas->Pen->Style = psDot;
        Board->Canvas->Brush->Style = bsClear;
        Board->Canvas->Pen->Mode = pmXor;
    }

    // Transfiro o ponto antigo para o novo
    *Xant = X - *XOffset;
    *Yant = Y - *YOffset;

    // Mantém o Objeto visível dentro da tela
    if(*Xant < 0) *Xant = 0;
    if(*Yant < 0) *Yant = 0;
    if(*Xant > Board->Width) *Xant = Board->Width;
    if(*Yant > Board->Height) *Yant = Board->Height;

    // Pinto o Objeto Fantasma
    Board->Canvas->Font = Selecionado->TextFont;
    Selecionado->Drag(Board, *Xant, *Yant);

    // Repinto os conectores
    if(!ListaViewConectores.ListaVazia())
    {
        for(c = ListaViewConectores.listaPTR; c!=0; c = c->Next)
        {
            if(c->Conn->ViewA == Selecionado || c->Conn->ViewB == Selecionado)
            {
                c->Conn->Paint(Board->Canvas, clWhite);
                if(c->Conn->GetViewPointingAtMe() != 0)
                {
           	    c->Conn->GetViewPointingAtMe()->Paint(Board->Canvas, clWhite);
                }
            }
        }
    }
}
void Diagrama::SoltaPontoSelecionado(TPaintBox *Board, float X, float Y)
{
    if (PontoSelecionado->x != -2000) // Se o ponto foi movido, então...
    {
        Board->Canvas->Pen->Mode = pmXor;
        Board->Canvas->Pen->Color = clWhite;
        Board->Canvas->Pen->Style = psSolid;
        Board->Canvas->Brush->Color = clBlack;

        // Apago a posição anterior repintando-a...
        SelecionadoConn->Paint(Board->Canvas, clWhite);

        // Move o ponto para a nova localização, proibindo a sua saída da tela.
        if(X < 10) X = 10;
        if(Y < 10) Y = 10;
        if(X > Board->Width - 10) X = Board->Width - 10;
        if(Y > Board->Height - 10) Y = Board->Height - 10;

        PontoSelecionado->x = X;
        PontoSelecionado->y = Y;

        SelecionadoConn->VerificaPontoSobreReta(PontoSelecionado);
    }
    else
    {
        delete PontoSelecionado;
    }

    SelecionadoConn->SetDragging(false);
    SelecionadoConn->SetSelection(true);

    // repinta o conector
    Board->Refresh();
    Paint(Board->Canvas);

    PontoSelecionado = NULL;
    *DownConnector = false;
}
void Diagrama::ArrastaGrupo(TPaintBox *Board, float X, float Y)
{
    FilaConectores c;
    FilaObjetos p;

    // contOFFSET é o contador usado para acessar
    // a distância do ponto (X,Y) ao objeto cujo indice
    // também vale contOFFSET na lista GrupoObj...
    int contOFFSET;

    TPoint *Dist;

    Board->Canvas->Pen->Mode = pmXor;
    Board->Canvas->Pen->Color = clWhite;
    Board->Canvas->Pen->Style = psSolid;
    Board->Canvas->Brush->Color = clBlack;

    SetZoomMode(Board->Canvas);

    // Pinto os Conectores ligados a ele
    if(*Xant == -2000) // Apaga o primeiro arraste
    {
        Board->Canvas->Pen->Mode = pmWhite;
    }

    if(!GrupoConn.ListaVazia())
    {
        for(c = GrupoConn.listaPTR; c!=0; c = c->Next)
        {
            c->Conn->Paint(Board->Canvas, clWhite);
        }
    }

    if(*Xant != -2000) // Não mostra o primeiro arraste
    {
        // Apago com o XOR
        Board->Canvas->Pen->Style = psDot;
        Board->Canvas->Brush->Style = bsClear;

        if(!GrupoObj.ListaVazia())
        {
            contOFFSET = 0;
            for(p = GrupoObj.listaPTR; p!=0; p = p->Next)
            {
                Dist = (TPoint *)Distancias->Items[contOFFSET];
                contOFFSET++;

                Board->Canvas->Font = p->Obj->TextFont;
                p->Obj->Drag(Board, *Xant - Dist->x, *Yant - Dist->y);
            }
        }
    }
    else
    {
        Board->Canvas->Pen->Style = psSolid;
        if(!GrupoObj.ListaVazia())
        {
           for(p = GrupoObj.listaPTR; p!=0; p = p->Next)
           {
               *p->Obj->Visible = true;
               Board->Canvas->Font = p->Obj->TextFont;
               p->Obj->Drag(Board, *p->Obj->Xpos + *p->Obj->Width/2, *p->Obj->Ypos - *p->Obj->Height/2);
           }
        }

        Board->Canvas->Pen->Mode = pmWhite;
        if(!GrupoConn.ListaVazia())
        {
            for(c = GrupoConn.listaPTR; c!=0; c = c->Next)
            {
                c->Conn->SetDragging(true);
                c->Conn->Paint(Board->Canvas, clWhite);
            }
        }
        Board->Canvas->Pen->Style = psDot;
        Board->Canvas->Brush->Style = bsClear;

        Board->Canvas->Pen->Mode = pmXor;
    }

    // Pinto o Objeto Fantasma

    contOFFSET = 0;

    if(!GrupoObj.ListaVazia())
    {
 	    for(p = GrupoObj.listaPTR; p!=0; p = p->Next)
        {
	        // Transfiro o ponto antigo para o novo
            Dist = (TPoint *)Distancias->Items[contOFFSET];
            contOFFSET++;

            Board->Canvas->Font = p->Obj->TextFont;
 	        p->Obj->Drag(Board, X - Dist->x, Y - Dist->y);
        }
    }
                             
    // Repinto os conectores

    if(!GrupoConn.ListaVazia())
    {
        TPoint *ponto;

        for (int i=0; i<ListaPontosSelecionados->Count;i++)
        {
	        // Transfiro o ponto antigo para o novo
            Dist = (TPoint *)DistanciasPontos->Items[i];
            ponto = (TPoint*)ListaPontosSelecionados->Items[i];

            ponto->x = X - Dist->x;
            ponto->y = Y - Dist->y;
        }

        for(c = GrupoConn.listaPTR; c!=0; c = c->Next)
        {
            c->Conn->Paint(Board->Canvas, clWhite);
        }
    }

    *Xant = X;
    *Yant = Y;
}
void Diagrama::SelecionaGrupo(TPaintBox *Board, float X, float Y)
{
    Board->Canvas->Pen->Mode = pmXor;
    Board->Canvas->Pen->Color = clWhite;
    Board->Canvas->Pen->Style = psDot;
    Board->Canvas->Brush->Color = clBlack;

    SetZoomMode(Board->Canvas);

    if(*Xant != -2000)
    {
    	Board->Canvas->Rectangle(Base->x, Base->y, *Xant, *Yant);
    }
    *Xant = X;
    *Yant = Y;
    Board->Canvas->Rectangle(Base->x, Base->y, *Xant, *Yant);
}
bool Diagrama::PreparaArrastaGrupo(TPaintBox *Board, float X, float Y)
{
    // Esta função retorna true se existe um objeto
    // do grupo sob o ponto (X,Y)...

    FilaObjetos s;
    bool achei = false;

    *ScreenUpdateLock = true;

    Refresh(Board->Canvas);
    Board->Canvas->Pen->Color = clBlack;
    Board->Canvas->Brush->Color = clBlack;

    SetZoomMode(Board->Canvas);

    Distancias->Clear();
    DistanciasPontos->Clear();

    TPoint *Dist;

    // Calculo e armazeno a distância de todos os pontos de quebra
    // selecionados até o ponto (X,Y).
    for(int i=0; i<ListaPontosSelecionados->Count; i++)
    {
    	Dist = new TPoint;
	    Dist->x = X - ((TPoint*)ListaPontosSelecionados->Items[i])->x;
        Dist->y = Y - ((TPoint*)ListaPontosSelecionados->Items[i])->y;
        DistanciasPontos->Add(Dist);
    }

    // Calculo e armazeno a distância de todos os
    // objetos selecionados até o ponto (X,Y)
    for(s = GrupoObj.listaPTR; s!=0; s = s->Next)
    {
    	Dist = new TPoint;
	    Dist->x = X - (*s->Obj->Xpos + *s->Obj->Width/2);
        Dist->y = Y - (*s->Obj->Ypos - *s->Obj->Height/2);
        Distancias->Add(Dist);

	    if(s->Obj->isHere(X, Y) == true)
        {
            achei = true;
        }
        *s->Obj->Visible = false;
        Board->Canvas->Font = s->Obj->TextFont;
        s->Obj->Drag(Board, *s->Obj->Xpos + *s->Obj->Width/2, *s->Obj->Ypos - *s->Obj->Height/2);
    }
    Paint(Board->Canvas);
    *ScreenUpdateLock = false;

    if(achei) // Se achei algum OBJETO, então...
    {
	    *Xant = -2000;
        *Yant = -2000;
        *Modified = true;
    	return true;
    }
    else
    {
    	Distancias->Clear();
        DistanciasPontos->Clear();
	    return false;
    }
}
void Diagrama::setAllVisible(TPaintBox *Board)
{
    FilaConectores c;

    *ScreenUpdateLock = true;
    Board->Canvas->Pen->Mode = pmCopy;

    // Zero todos os conectores
    if(!ListaViewConectores.ListaVazia())
    {
        for(c = ListaViewConectores.listaPTR; c!=0; c = c->Next)
        {
            *c->Conn->Visible = true;
            c->Conn->SetDragging(false);
    	}
    }
    *Selecionado->Visible = true;
    *Down = false;
    Paint(Board->Canvas);
    *ScreenUpdateLock = false;
}
void Diagrama::MovePontoConector(TPaintBox *Board, float X, float Y)
{
    Board->Canvas->Pen->Mode = pmXor;
    Board->Canvas->Pen->Color = clWhite;
    Board->Canvas->Pen->Style = psDot;
    Board->Canvas->Brush->Color = clWhite;
    Board->Canvas->Brush->Style = bsClear;

    if (*FirstMove)
    {
        Board->Canvas->Pen->Mode = pmCopy;
        SelecionadoConn->SetDragging(false);
        SelecionadoConn->SetSelection(false);
        SelecionadoConn->Paint(Board->Canvas, clWhite);
        SelecionadoConn->SetSelection(true);
        SelecionadoConn->SetDragging(true);
        Board->Canvas->Pen->Mode = pmXor;

        *FirstMove = false;
    }                        
    else
    {
        // Apago a posição anterior repintando-a...
        SelecionadoConn->Paint(Board->Canvas, clWhite);
    }
                                      
    if (PontoSelecionado->x == -2000)
    {
        PontoSelecionado->SetIdDono(SelecionadoConn->GetCorpo()->GetId());
        SelecionadoConn->GetPontos()->Insert(SelecionadoConn->GetTrechoSelecionado()+1, PontoSelecionado);
        ListaPontosConectores->Add(PontoSelecionado);
    }

    // Move o ponto para a nova localização, proibindo a sua saída da tela.
    if(X < 10) X = 10;
    if(Y < 10) Y = 10;
    if(X > Board->Width - 10) X = Board->Width - 10;
    if(Y > Board->Height - 10) Y = Board->Height - 10;

    PontoSelecionado->x = X;
    PontoSelecionado->y = Y;

    // repinta o conector
    SelecionadoConn->Paint(Board->Canvas, clWhite);
}
void Diagrama::AcertaNovoTamanho(TPaintBox *Board)
{
    *ScreenUpdateLock = true;

    SetZoomMode(Board->Canvas);

    switch(*WillResize)
    {
        case 1:
            *Redimensionado->Width = *Redimensionado->Width + (*Redimensionado->Xpos - *XFinal);
            *Redimensionado->Height = *Redimensionado->Height + (*YFinal - *Redimensionado->Ypos);
            *Redimensionado->Xpos = *XFinal;
            *Redimensionado->Ypos = *YFinal;
            break;

        case 2:
            *Redimensionado->Height = *Redimensionado->Height + (*YFinal - *Redimensionado->Ypos);
            *Redimensionado->Ypos = *YFinal;
            break;

        case 3:
            *Redimensionado->Width = *XFinal - *Redimensionado->Xpos;
            *Redimensionado->Height = *Redimensionado->Height + (*YFinal - *Redimensionado->Ypos);
            *Redimensionado->Ypos = *YFinal;
            break;

        case 4:
            *Redimensionado->Width = *XFinal - *Redimensionado->Xpos;
            break;

        case 5:
            *Redimensionado->Width = *XFinal - *Redimensionado->Xpos;
            *Redimensionado->Height = *Redimensionado->Ypos - *YFinal;
            break;

        case 6:
            *Redimensionado->Height = *Redimensionado->Ypos - *YFinal;
            break;

        case 7:
            *Redimensionado->Width = *Redimensionado->Xpos + *Redimensionado->Width - *XFinal;
            *Redimensionado->Height = *Redimensionado->Ypos - *YFinal;
            *Redimensionado->Xpos = *XFinal;
            break;

        case 8:
            *Redimensionado->Width = *Redimensionado->Xpos + *Redimensionado->Width - *XFinal;
            *Redimensionado->Xpos = *XFinal;
            break;
    }
    *WillResize = 0;
    *Down = false;
    Refresh(Board->Canvas);
    Board->Canvas->Pen->Mode = pmCopy;
    Paint(Board->Canvas);
    *ScreenUpdateLock = false;
}
void Diagrama::Redimensiona(TPaintBox *Board, float X, float Y)
{
    Board->Canvas->Pen->Mode = pmXor;
    Board->Canvas->Pen->Color = clWhite;
    Board->Canvas->Pen->Style = psDot;
    Board->Canvas->Brush->Color = clBlack;

    SetZoomMode(Board->Canvas);

    // Primeiro eu apago o retangulo antigo...
    switch(*WillResize)
    {
         case 1:
             if(X >= (*Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MinWidth()))
                  X = *Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MinWidth();
             if(Y <= (*Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MinHeight()))
                  Y = *Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MinHeight();
             if(X <= (*Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MaxWidth()))
                  X = *Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MaxWidth();
             if(Y >= (*Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MaxHeight()))
                  Y = *Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MaxHeight();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos + *Redimensionado->Width, *Redimensionado->Ypos - *Redimensionado->Height, *Xant, *Yant);
             }

             *Xant = X;
             *Yant = Y;
             break;

         case 2:
             if(Y <= (*Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MinHeight()))
                  Y = *Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MinHeight();
             if(Y >= (*Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MaxHeight()))
                  Y = *Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MaxHeight();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos + *Redimensionado->Width, *Redimensionado->Ypos - *Redimensionado->Height, *Xant, *Yant);
             }

             *Xant = *Redimensionado->Xpos;
             *Yant = Y;
	     break;

         case 3:
             if(X <= (*Redimensionado->Xpos + Redimensionado->MinWidth()))
                  X = *Redimensionado->Xpos + Redimensionado->MinWidth();
             if(Y <= (*Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MinHeight()))
                  Y = *Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MinHeight();
             if(X >= (*Redimensionado->Xpos + Redimensionado->MaxWidth()))
                  X = *Redimensionado->Xpos + Redimensionado->MaxWidth();
             if(Y >= (*Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MaxHeight()))
                  Y = *Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MaxHeight();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos, *Redimensionado->Ypos - *Redimensionado->Height, *Xant, *Yant);
             }

             *Xant = X;
             *Yant = Y;
	     break;

         case 4:
             if(X <= (*Redimensionado->Xpos + Redimensionado->MinWidth()))
                  X = *Redimensionado->Xpos + Redimensionado->MinWidth();
             if(X >= (*Redimensionado->Xpos + Redimensionado->MaxWidth()))
                  X = *Redimensionado->Xpos + Redimensionado->MaxWidth();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos, *Redimensionado->Ypos - *Redimensionado->Height, *Xant, *Yant);
             }

             *Xant = X;
             *Yant = *Redimensionado->Ypos;
	     break;

         case 5:
             if(X <= (*Redimensionado->Xpos + Redimensionado->MinWidth()))
                  X = *Redimensionado->Xpos + Redimensionado->MinWidth();
             if(Y >= (*Redimensionado->Ypos - Redimensionado->MinHeight()))
                  Y = *Redimensionado->Ypos - Redimensionado->MinHeight();
             if(X >= (*Redimensionado->Xpos + Redimensionado->MaxWidth()))
                  X = *Redimensionado->Xpos + Redimensionado->MaxWidth();
             if(Y <= (*Redimensionado->Ypos - Redimensionado->MaxHeight()))
                  Y = *Redimensionado->Ypos - Redimensionado->MaxHeight();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos, *Redimensionado->Ypos, *Xant, *Yant);
             }

             *Xant = X;
             *Yant = Y;
	     break;

         case 6:
             if(Y >= (*Redimensionado->Ypos - Redimensionado->MinHeight()))
                  Y = *Redimensionado->Ypos - Redimensionado->MinHeight();
             if(Y <= (*Redimensionado->Ypos - Redimensionado->MaxHeight()))
                  Y = *Redimensionado->Ypos - Redimensionado->MaxHeight();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos, *Redimensionado->Ypos, *Xant, *Yant);
             }

             *Xant = *Redimensionado->Xpos + *Redimensionado->Width;
             *Yant = Y;
	     break;

         case 7:
             if(X >= (*Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MinWidth()))
                  X = *Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MinWidth();
             if(Y >= (*Redimensionado->Ypos - Redimensionado->MinHeight()))
                  Y = *Redimensionado->Ypos - Redimensionado->MinHeight();
             if(X <= (*Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MaxWidth()))
                  X = *Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MaxWidth();
             if(Y <= (*Redimensionado->Ypos - Redimensionado->MaxHeight()))
                  Y = *Redimensionado->Ypos - Redimensionado->MaxHeight();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos + *Redimensionado->Width, *Redimensionado->Ypos, *Xant, *Yant);
             }

             *Xant = X;
             *Yant = Y;
             break;

         case 8:
             if(X >= (*Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MinWidth()))
                  X = *Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MinWidth();
             if(X <= (*Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MaxWidth()))
                  X = *Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MaxWidth();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos + *Redimensionado->Width, *Redimensionado->Ypos, *Xant, *Yant);
             }

             *Xant = X;
             *Yant = *Redimensionado->Ypos - *Redimensionado->Height;
	     break;

    }

    // Desenho o retangulo atual...

    // O primeiro ponto do desenho do retangulo muda de lugar
    // quando eu redimensiono de cima para baixo ou de baixo
    // para cima...por isso devo ver de onde ele vem...
    if(*WillResize == 1 || *WillResize == 2)
    	Board->Canvas->Rectangle(*Redimensionado->Xpos + *Redimensionado->Width, *Redimensionado->Ypos - *Redimensionado->Height, *Xant, *Yant);
    else if(*WillResize == 3 || *WillResize == 4)
	Board->Canvas->Rectangle(*Redimensionado->Xpos, *Redimensionado->Ypos - *Redimensionado->Height, *Xant, *Yant);
    else if(*WillResize == 5 || *WillResize == 6)
	Board->Canvas->Rectangle(*Redimensionado->Xpos, *Redimensionado->Ypos, *Xant, *Yant);
    else if(*WillResize == 7 || *WillResize == 8)
	Board->Canvas->Rectangle(*Redimensionado->Xpos + *Redimensionado->Width, *Redimensionado->Ypos, *Xant, *Yant);

    *XFinal = *Xant;
    *YFinal = *Yant;
}
void Diagrama::SetaCursor(TPaintBox *Board, float X, float Y)
{
    // Tenho que Verificar qual o cursor que devo colocar
    int wCursor = 0;

    if(Selecionado != NULL)
        wCursor = Selecionado->isResize(X,Y);
    else if(SelecionadoConn != NULL)
    {
        if (SelecionadoConn->IsBasePoint(X,Y))
            wCursor = 9;
    }
    else if(*WillInsert)
    {
        Board->Cursor = crCross;
        return;
    }
    else if(*WillConnect)
    {
        Board->Cursor = crCross;
        return;
    }
    else
    {
    	Board->Cursor = crArrow;
        return;
    }

    switch(wCursor)
    {
        case 0:
                // seta Default
                Board->Cursor = crArrow;
                break;
        case 1:
                // seta Diagonal Secundária (/)
                Board->Cursor = crSizeNESW;
                break;
        case 2:
                // seta Vertical
                Board->Cursor = crSizeNS;
                break;
        case 3:
                // seta Diagonal Principal (\)
                Board->Cursor = crSizeNWSE;
                break;
        case 4:
                // seta Horizontal
                Board->Cursor = crSizeWE;
                break;
        case 5:
                // seta Diagonal Secundária (/)
                Board->Cursor = crSizeNESW;
                break;
        case 6:
                // seta Vertical
                Board->Cursor = crSizeNS;
                break;
        case 7:
                // seta Diagonal Principal (\)
                Board->Cursor = crSizeNWSE;
                break;
        case 8:
                // seta Horizontal
                Board->Cursor = crSizeWE;
                break;
        case 9:
                // seta para as quatro direções
                Board->Cursor = crSizeAll;
                break;
    }
}
void Diagrama::AlignGroup(int type)
{
    FilaObjetos p;
    int most;

    if(!GrupoObj.ListaVazia())
    {
        p = GrupoObj.listaPTR;

        if(type == alignLeft)
	    	most = *p->Obj->Xpos;
        else if(type == alignRight)
	    	most = (*p->Obj->Xpos + *p->Obj->Width);
        else if(type == alignTop)
	    	most = (*p->Obj->Ypos - *p->Obj->Height);
        else if(type == alignBottom)
	    	most = (*p->Obj->Ypos);

        p = p->Next;

        for(; p!=0; p = p->Next)
        {
            if(type == alignLeft && *p->Obj->Xpos < most)
            	most = *p->Obj->Xpos;
            else if(type == alignRight && (*p->Obj->Xpos + *p->Obj->Width) > most)
            	most = *p->Obj->Xpos + *p->Obj->Width;
            else if(type == alignTop && (*p->Obj->Ypos - *p->Obj->Height) < most)
            	most = *p->Obj->Ypos - *p->Obj->Height;
            else if(type == alignBottom && *p->Obj->Ypos > most)
            	most = *p->Obj->Ypos;
        }

        for(p = GrupoObj.listaPTR; p!=0; p = p->Next)
        {
            if(type == alignLeft)
                *p->Obj->Xpos = most;
            else if(type == alignRight)
                *p->Obj->Xpos = most - *p->Obj->Width;
            else if(type == alignTop)
                *p->Obj->Ypos = most + *p->Obj->Height;
            else if(type == alignBottom)
                *p->Obj->Ypos = most;
        }
    }
}
/*************************************************************************/
void Diagrama::ExportaModelo(AnsiString PathFile)
{
    /***************************************\
    	Gravação do Modelo no Arquivo
    \***************************************/
/*    FilaObjetos p;
    FilaConectores c;
    int cont;
    AnsiString Linha;

    *ModelFileName = PathFile;

    TIniFile* INITIAL;
    INITIAL = new TIniFile(PathFile);

    *LastModified = GetTime();

    // Zera o Arquivo passado como parâmetros
    INITIAL->EraseSection("Features");
    INITIAL->EraseSection("Descricao");

    // Apago as seções dos Objetos
	cont = INITIAL->ReadInteger("Qtd","Obj", 0);

    for(int i = 1; i <= cont; i++)
    {
		INITIAL->EraseSection("Objeto" + AnsiString(i));
    }

    // Apago as seções dos conectores
	cont = INITIAL->ReadInteger("Qtd","Conn", 0);

    for(int i = 1; i <= cont; i++)
    {
		INITIAL->EraseSection("Conector" + AnsiString(i));
    }

    INITIAL->EraseSection("Qtd");

    // Gravo os objetos...
    cont = 1;
    for(p = ListaViewObjetos.listaPTR; p!=0; p = p->Next)
    {
		p->Obj->Salva(cont, INITIAL);
        cont++;
    }

    INITIAL->WriteString("Qtd","obj", AnsiString(cont-1));

    // Gravo os conectores...
    cont = 1;
    for(c = ListaViewConectores.listaPTR; c!=0; c = c->Next)
    {
        c->Conn->Salva(cont, INITIAL);
        cont++;
    }

    INITIAL->WriteString("Qtd","Conn", AnsiString(cont-1));

    // Gravo os detalhes do modelo...

    INITIAL->WriteString("Features","Nome", *ModelName);
    INITIAL->WriteString("Features","Type", *ModelType);
    INITIAL->WriteString("Features","LastModified", *LastModified);

    // Bounds
    INITIAL->WriteString("Features","HSize", *HorizontalSize);
    INITIAL->WriteString("Features","VSize", *VerticalSize);

    // Descrição
    int index, count;
    INITIAL->WriteString("Descricao","NumLinhas", AnsiString(Descricao->Length() % 80));
    for(cont = 0; cont < (Descricao->Length() % 80); cont++)
    {
        index = (Descricao->Length() % 80) * cont;
        count = 80;
		INITIAL->WriteString("Descricao","L" + AnsiString(cont), Descricao->SubString(index, count));
    }

    delete INITIAL;
    *Modified = false;
*/
}

void Diagrama::ImportaModelo(AnsiString PathFile)
{
    /***************************************\
    	Recuperação do Modelo no Arquivo
    \***************************************/
/*    FilaObjetos p;
    int cont, i, TotalLinhas;
    Objeto *Temp, *Origem, *Destino;
    AnsiString Linha, Qtd;
    FabricaSemantica fabrica;
    int Type, ID;
    int A, B;
    char LinhaArray[200];

    TList *ListaConn, *ListaID;
    ListaConn = new TList;
    ListaID = new TList;

    TIniFile* INITIAL;
    INITIAL = new TIniFile(PathFile);

    GrupoObj.Esvazia();
    GrupoConn.Esvazia();
    EsvaziaLista(ListaPontosSelecionados);
        
    Distancias->Clear();
    DistanciasPontos->Clear();

    NewModel("");
    *ModelFileName = PathFile;

    Selecionado = 0;
    // Restaura os Objetos
    *ModelName = IniStrToStr(INITIAL->ReadString("Features","Nome", ""));
    *ModelType = INITIAL->ReadInteger("Features", "Type", 1);
    *LastModified = IniStrToStr(INITIAL->ReadString("Features","LastModified", ""));

    // Bounds
    *HorizontalSize = IniStrToStr(INITIAL->ReadString("Features","HSize", "")).ToInt();
    *VerticalSize = IniStrToStr(INITIAL->ReadString("Features","VSize", "")).ToInt();

    // Descrição
    *Descricao = "";
    Qtd = IniStrToStr(INITIAL->ReadString("Descricao","NumLinhas", ""));
    TotalLinhas = Qtd.ToInt();
    for(cont = 0; cont <= TotalLinhas-1; cont++)
    {
        *Descricao += (IniStrToStr(INITIAL->ReadString("Descricao","L" + AnsiString(cont), "")));
    }

    // Carrega os Objetos
    cont = INITIAL->ReadInteger("Qtd","Obj", 0);

    for(i=1; i<=cont; i++)
    {
        Linha = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(i), "chave", ""));

        strcpy(LinhaArray, Linha.c_str());

        sscanf(LinhaArray, "%d %d", &Type, &ID);

        Temp = fabrica.FabricaObjetos(Type, ID);

        Temp->Carrega(i, INITIAL);
        NewObjectView(Temp);
    }

    // Restaura os Conectores
    cont = INITIAL->ReadInteger("Qtd","Conn", 0);

    for(i=1; i<=cont; i++)
    {
        Linha = IniStrToStr(INITIAL->ReadString("Conector" + AnsiString(i), "chave", ""));

        strcpy(LinhaArray, Linha.c_str());

        sscanf(LinhaArray, "%d", &ID);

	    Connector *Temp;

        Temp = fabrica.FabricaConectores(ID);

        Linha = IniStrToStr(INITIAL->ReadString("Conector" + AnsiString(i), "basico", ""));

        strcpy(LinhaArray, Linha.c_str());

        sscanf(LinhaArray, "%d %d", &A, &B);

        // Busco os Objetos Alocados para fazer a conexão
        for(p = ListaViewObjetos.listaPTR; p!=0; p=p->Next)
        {
            if(p->Obj->GetId() == A)
            {
                Origem = p->Obj;
            }
            else if(p->Obj->GetId() == B)
            {
                Destino = p->Obj;
            }
        }

        if(ID == cAssociativo)
        {
            int *IDReta;
            IDReta = new int;
			*IDReta = INITIAL->ReadInteger("Conector" + AnsiString(i), "end", 0);
            // Guardo para atualizar quando todos os conectores já estiverem na memória
            ListaID->Add(IDReta);
            ListaConn->Add(Temp);
            Destino = 0;
        }
        else
        {
	        NewConnector(Temp);
        }
        Temp->Connect(Origem,Destino);
        Temp->Carrega(i, INITIAL);
    }

    // Re-ligo os conectores que estavam ligados a uma
    // associação. Tenho que fazer isso no final da função
    // porque só aqui todos os conectores já estão na memória
    if(ListaConn->Count != 0)
    {
    	ConnAssociativo *RetaA;
        ConnAssociacao *Dest;
        FilaConectores c;
        int *ID;
        for(int i=0; i < ListaConn->Count; i++)
        {
			RetaA = (ConnAssociativo *)ListaConn->Items[i];
            ID = (int *)ListaID->Items[i];

	        for(c = ListaViewConectores.listaPTR; c!=0; c=c->Next)
	        {
				if(c->Conn->GetId() == *ID)
                {
                	RetaA->SetConectorEndLine(c->Conn);
                    Dest = (ConnAssociacao*)c->Conn;
                    if(Dest->pointingAtMe != 0)
                    {
                    	importError();
                        return;
                    }
                    Dest->pointingAtMe = RetaA;
                    NewConnector(RetaA);
                    break;
                }
    		}
        }
    }
    delete INITIAL;
    *Modified = false;
*/
}
void Diagrama::AbrePropriedades(TPaintBox *Board)
{
     ViewObjeto *ObjView;
     ViewConector *ConnView;

     ObjView = getSelectedObject();
     ConnView = getSelectedConnector();

     if(ObjView != 0)
     {
         FabricaControlador fabrica;
         IControladorObjeto *controller;
         controller = fabrica.CriaControladorObjeto(ObjView->GetCorpo()->GetType());
         controller->Execute(ObjView->GetCorpo());
         controller->EfetuaAjustesView(ObjView, Board);
     }
     else if(ConnView != 0)
     {
         FabricaControlador fabrica;
         IControladorConector *controller;
         controller = fabrica.CriaControladorConector(ConnView->GetCorpo()->GetType());
         controller->Execute(ConnView->GetCorpo(), Board);
     }

     Refresh(Board->Canvas);
     Paint(Board->Canvas);
}
#define DiagramaH
#endif
