#include "ListaEntidades.hpp"

#include <iostream>
using namespace std;

ListaEntidades::ListaEntidades() : LEs()
{
}

ListaEntidades::~ListaEntidades()
{
	limpar();
}

void ListaEntidades::incluir(Entidade* pE)
{
	if (pE != nullptr)
		LEs.inserir(pE);

}

void ListaEntidades::excluir(Entidade* pE)
{
	if (pE != nullptr)
		LEs.deletar(pE);
}

void ListaEntidades::limpar()
{
	LEs.limpar();
}
