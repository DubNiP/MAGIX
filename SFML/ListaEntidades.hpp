#pragma once
#include "Lista.hpp"
#include "Entidade.hpp"

class ListaEntidades
{
private:
    Lista<Entidade> LEs;

public:
    ListaEntidades();
    ~ListaEntidades();

    void incluir(Entidade* pE);
    void excluir(Entidade* pE);
    void getItem(int pos);
    void limpar();
};
