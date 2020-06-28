#include "FuncoesBasicas.h"
#include "ItemProjeto.h"

#ifndef ObjetoH

class Objeto : public ItemProjeto
{
  private:
    int *Type;
    int *Id;
    AnsiString *Name;
    TStringList *Documentation;

  public:
    Objeto(int _Type, int _Id) : ItemProjeto()
    {
        Aloca();
        *Id = _Id;
        *Type = _Type;
    }
    ~Objeto()
    {
        delete Id, Name;
        delete Type;
        delete Documentation;
    }
    void Aloca();

    void SetName(AnsiString name);
    AnsiString GetName();
    int GetId();
    void SetId(int newId);
    int GetType();
    void SetType(int newType);
    TStringList* GetDocumentation();
    void SetDocumentation(TStringList *newDocumentation);

	void SalvaObjeto(int Ordem, TIniFile *INITIAL);
    virtual void Salva(int Ordem, TIniFile *INITIAL)=0;

	void CarregaObjeto(int Ordem, TIniFile *INITIAL);
    virtual void Carrega(int Ordem, TIniFile *INITIAL)=0;
};

void Objeto::SetName(AnsiString name)
{
    *Name = name;
}
AnsiString Objeto::GetName()
{
    return *Name;
}
TStringList* Objeto::GetDocumentation()
{
	return Documentation;
}
void Objeto::SetDocumentation(TStringList *newDocumentation)
{
	Documentation->Assign(newDocumentation);
}
void Objeto::Aloca()
{
    Name = new AnsiString();
    Id = new int;
    Type = new int;
    Documentation = new TStringList();
}
int Objeto::GetId()
{
    return *Id;
}
void Objeto::SetId(int newId)
{
	*Id = newId;
}
int Objeto::GetType()
{
    return *Type;
}
void Objeto::SetType(int newType)
{
	*Type = newType;
}

void Objeto::SalvaObjeto(int Ordem, TIniFile *INITIAL)
{
/*	AnsiString Linha;

    Linha = *Type;
    Linha += " ";
    Linha += *Id;

    INITIAL->WriteString("Objeto" + AnsiString(Ordem),"chave", Linha);

    Linha = *Xpos;
    Linha += " ";
    Linha += *Ypos;
    Linha += " ";
    Linha += *Height;
    Linha += " ";
    Linha += *Width;
    Linha += " ";
    Linha += *Align;

    INITIAL->WriteString("Objeto" + AnsiString(Ordem),"basico", Linha);

    Linha = *Label;

    INITIAL->WriteString("Objeto" + AnsiString(Ordem),"label", Linha);

    Linha = AnsiString(*FillColor);
    Linha += " ";
    Linha += AnsiString(*LineColor);

    INITIAL->WriteString("Objeto" + AnsiString(Ordem),"Color", Linha);

    Linha = TextFont->Name;
    INITIAL->WriteString("Objeto" + AnsiString(Ordem),"FontName", Linha);
    Linha = AnsiString(TextFont->Size);
    INITIAL->WriteString("Objeto" + AnsiString(Ordem),"FontSize", Linha);
    Linha = AnsiString(TextFont->Color);
    INITIAL->WriteString("Objeto" + AnsiString(Ordem),"FontColor", Linha);
*/
}
void Objeto::CarregaObjeto(int Ordem, TIniFile *INITIAL)
{
/*    char LinhaArray[200];
    AnsiString Linha;
	int _Xpos, _Ypos, _Width, _Height, _Align;

    Linha = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "basico", ""));

    strcpy(LinhaArray, Linha.c_str());

	// Configurável - Deve-se adicionar ou remover os parâmetros que quizer.
    sscanf(LinhaArray, "%d %d %d %d %d", &_Xpos, &_Ypos, &_Height, &_Width, &_Align);

    Linha = IniStrToStr(INITIAL->ReadString("objeto" + AnsiString(Ordem), "label", ""));
    Restaura(_Xpos, _Ypos, _Height, _Width, Linha, _Align);

    Linha = IniStrToStr(INITIAL->ReadString("objeto" + AnsiString(Ordem), "Color", ""));
    strcpy(LinhaArray, Linha.c_str());
    sscanf(LinhaArray, "%d %d", FillColor, LineColor);

    TextFont->Name = IniStrToStr(INITIAL->ReadString("objeto" + AnsiString(Ordem), "FontName", ""));
    TextFont->Size = INITIAL->ReadInteger("objeto" + AnsiString(Ordem), "FontSize", 8);
    TextFont->Color = (TColor)INITIAL->ReadInteger("objeto" + AnsiString(Ordem), "FontColor", 0);
*/
}

#define ObjetoH
#endif
