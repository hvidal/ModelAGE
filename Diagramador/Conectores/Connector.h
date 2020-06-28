#include <math.h>
#include <stdio.h>

#include <Objetos\Objeto.h>

#include "ItemProjeto.h"

#ifndef ConnectorH

class Connector : public ItemProjeto
{
  private:
    int *Type;
    int *Id;

    // Conector a quem eu me ligo
   	Connector *end;
  protected:
  public:
    Objeto *A, *B;       

    // Conector que se liga a mim
    Connector *pointingAtMe;

    Connector(int ConnType, int ConnId) : ItemProjeto()
    {
        Type = new int;
        Id = new int;

        *Type = ConnType;
        *Id = ConnId;

       	pointingAtMe = NULL;
        end = NULL;
    }
    ~Connector()
    {
        // Não posso desalocar o A e o B porque os objetos sempre
        // são desalocados primeiros pelo ModelHandler.
        // Se colocá-los aqui vai dar problema!
        delete Type;

        if (pointingAtMe != NULL)
        {
          	pointingAtMe->SetConectorEndLine(NULL);
        }
        if (end != NULL)
        {
            end->pointingAtMe = NULL;
        }
    }
    void Connect(Objeto *AX, Objeto *BX)
    {
        A=AX;
        B=BX;
    }

    // Getters & Setters
    int GetType();
    void SetType(int newType);

    int GetId();

    void SetConectorEndLine(Connector *endLine);
    Connector* GetConectorEndLine();

	void SalvaConector(int Ordem, TIniFile *INITIAL);
    virtual void Salva(int Ordem, TIniFile *INITIAL)=0;

	void CarregaConector(int Ordem, TIniFile *INITIAL);
    virtual void Carrega(int Ordem, TIniFile *INITIAL)=0;

};
int Connector::GetType()
{
    return *Type;
}
void Connector::SetType(int newType)
{
	*Type = newType;
}
int Connector::GetId()
{
    return *Id;
}
void Connector::SetConectorEndLine(Connector *endLine)
{
	end = endLine;
}
Connector* Connector::GetConectorEndLine()
{
	return end;
}
void Connector::SalvaConector(int Ordem, TIniFile *INITIAL)
{
/*	AnsiString Linha;

    Linha = *Type;

    INITIAL->WriteString("Conector" + AnsiString(Ordem), "chave", Linha);

    Linha = A->GetCorpo()->GetType();
    Linha += " ";
    if(B != 0)
	    Linha += B->GetCorpo()->GetType();
    else
	    Linha += "-1";

    INITIAL->WriteString("Conector" + AnsiString(Ordem), "basico", Linha);

    Linha = *Label;
    INITIAL->WriteString("Conector" + AnsiString(Ordem),"label", Linha);

    // Offsets
    Linha = AnsiString(*AXOffset);
    Linha += " ";
    Linha += AnsiString(*AYOffset);
    Linha += " ";
    Linha += AnsiString(*BXOffset);
    Linha += " ";
    Linha += AnsiString(*BYOffset);
    INITIAL->WriteString("Conector" + AnsiString(Ordem),"offset", Linha);

    INITIAL->WriteInteger("Conector" + AnsiString(Ordem),"maior", *Maior);
    INITIAL->WriteInteger("Conector" + AnsiString(Ordem),"position", *Position);

    INITIAL->WriteInteger("Conector" + AnsiString(Ordem),"Color", *LineColor);

    if(pointingAtMe != 0)
    {
	    INITIAL->WriteInteger("Conector" + AnsiString(Ordem),"pointingAtMe", pointingAtMe->GetType());
    }

    INITIAL->WriteInteger("Conector" + AnsiString(Ordem),"end", end->GetType());
*/
}

void Connector::CarregaConector(int Ordem, TIniFile *INITIAL)
{
/*
 	// Carrega a label
    *Label = IniStrToStr(INITIAL->ReadString("Conector" + AnsiString(Ordem), "label", ""));
	Linhas = Break(*Label);
    *Maior = INITIAL->ReadInteger("Conector" + AnsiString(Ordem), "maior", 0);
    *Position = INITIAL->ReadInteger("Conector" + AnsiString(Ordem), "position", 1);

	// offsets
    char LinhaArray[100];
    AnsiString Linha = IniStrToStr(INITIAL->ReadString("Conector" + AnsiString(Ordem), "offset", ""));
    strcpy(LinhaArray, Linha.c_str());
    sscanf(LinhaArray, "%d %d %d %d", AXOffset, AYOffset, BXOffset, BYOffset);

    *LineColor = (TColor)INITIAL->ReadInteger("Conector" + AnsiString(Ordem), "Color", 0);
*/
}
#define ConnectorH
#endif