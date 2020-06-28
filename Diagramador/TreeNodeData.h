#include "Diagrama.h"
#include "ItemProjeto.h"

#ifndef TreeNodeDataH
#define TreeNodeDataH

// Tipos de item de projeto:
#define ItemDIAGRAMA  101
#define ItemOBJETO    102
#define ItemCONECTOR  103

class TreeNodeData
{
	private:
        // Variavel que indica se o item é uma pasta
        bool *Folder;

        // Tipo de item
        int *ItemType;

        // Item do Projeto associado ao Nó
        ItemProjeto *Item;
    public:
    	TreeNodeData()
        {
        	Folder = new bool;
            ItemType = new int;
        }
        ~TreeNodeData()
        {
            delete Folder, ItemType;
        }

    	bool IsFolder();
        void SetFolder(bool folder);

        int GetItemType();
        void SetItemType(int type);

        void SetItemProjeto(ItemProjeto *item);
        ItemProjeto* GetItemProjeto();
};
bool TreeNodeData::IsFolder()
{
	return *Folder;
}
void TreeNodeData::SetFolder(bool folder)
{
	*Folder = folder;
}
int TreeNodeData::GetItemType()
{
	return *ItemType;
}
void TreeNodeData::SetItemType(int type)
{
	*ItemType = type;
}
void TreeNodeData::SetItemProjeto(ItemProjeto *item)
{
	Item = item;
}
ItemProjeto* TreeNodeData::GetItemProjeto()
{
	return Item;
}

#endif
