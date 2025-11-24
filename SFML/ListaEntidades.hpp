#pragma once
#include "Lista.hpp"
#include "Entidade.hpp"
#include "Inimigo.hpp"
#include "Projetil.hpp"
#include "Teia.hpp"


//É na lista de entidades que todas as entidades são salvas, excluídas , desenhadas e executadas.

namespace listas {

    class ListaEntidades
    {
    private:
        Lista<Entidade> LEs;

    public:
        ListaEntidades();
        ~ListaEntidades();

        void incluir(Entidade* pE);
        void excluir(Entidade* pE);
        void limpar();
        void limparPreservando(Entidade* J1, Entidade* J2);

        void executarTodos();
        void desenharTodos();
		void salvarTodos();
        void retomarTodos();
        void removerProjetis();
        void removerMorto();

        Lista<Entidade>::Iterator begin() { return LEs.begin(); }
        Lista<Entidade>::Iterator end() { return LEs.end(); }
    };

}
