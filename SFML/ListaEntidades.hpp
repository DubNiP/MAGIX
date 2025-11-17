#pragma once
#include "Lista.hpp"
#include "Entidade.hpp"
#include "Inimigo.hpp"
#include "Projetil.hpp"
#include "Teia.hpp"

namespace listas {

    class ListaEntidades
    {
    private:
        Lista<Entidade> LEs;

    public:
        using Iterator = Lista<Entidade>::Iterator;
        ListaEntidades();
        ~ListaEntidades();

        void incluir(Entidade* pE);
        void excluir(Entidade* pE);
        void limpar();
        void limparPreservando(Entidade* keep);

        void executarTodos();
        void desenharTodos();
        void retomarTodos();
        void removerProjetis();
        void removerMorto();

        Iterator begin() { return LEs.begin(); }
        Iterator end() { return LEs.end(); }
    };

}
