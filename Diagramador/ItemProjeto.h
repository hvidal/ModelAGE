#ifndef ItemProjetoH
#define ItemProjetoH

class ItemProjeto
{
	private:
        AnsiString *Parent;
        int *ItemType;
    protected:
    public:
        ItemProjeto()
        {
            Parent = new AnsiString;
            ItemType = new int;
        }
        ~ItemProjeto()
        {
            delete Parent, ItemType;
        }

        AnsiString GetParent()
        {
            return *Parent;
        }
        void SetParent(AnsiString parent)
        {
            *Parent = parent;
        }
        AnsiString GetStringParent()
        {
        	return ("(From " + *Parent + ")");
        }
        int GetItemType()
        {
            return *ItemType;
        }
        void SetItemType(int type)
        {
            *ItemType = type;
        }
};

#endif
