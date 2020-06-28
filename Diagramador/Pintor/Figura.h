
#ifndef FiguraH

// Valores Default para Pintura
#define LINECOLOR       clMaroon
#define FILLCOLOR       RGB(239, 239, 239)
#define FONTCOLOR       clNavy
#define FONTSIZE        8
#define FONTNAME        "Arial"

class Figura
{
	private:
        bool *isSelected;
    protected:
    public:
    	Figura()
        {
             isSelected = new bool;
             *isSelected = false;
        }
    	~Figura()
        {
             delete isSelected;
        }

		void SetSelection(bool selecao);
};
void Figura::SetSelection(bool selecao)
{
	*isSelected = selecao;
}
#define FiguraH
#endif
