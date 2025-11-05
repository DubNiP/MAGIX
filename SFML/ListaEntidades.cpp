#include "ListaEntidades.hpp"

using namespace std;

namespace listas {

ListaEntidades::ListaEntidades() : LEs()
{
}

ListaEntidades::~ListaEntidades()
{
	limpar();
}

void ListaEntidades::incluir(Entidade* pE)
{
	if (pE)
		LEs.incluir(pE);

}

void ListaEntidades::excluir(Entidade* pE)
{
	if (pE)
		LEs.deletar(pE);
}

void ListaEntidades::limpar()                                       
{
    for (int i = 0; i < LEs.getSize(); ++i) {
        Entidade* e = LEs.getItem(i);
        if (e) {
            delete e;
        }
    }
	LEs.limpar();
}

void ListaEntidades::limparPreservando(Entidade* keep) {                  //isso é zoado, é bom dar um jeito de remover isso...
    for (int i = 0; i < LEs.getSize(); i++) {
        Entidade* e = LEs.getItem(i);
        if (e && e != keep) {
            delete e;
        }
    }
    LEs.limpar();
}


void ListaEntidades::executarTodos() {
    for (int i = 0; i < LEs.getSize(); i++) {
        Entidade* e = LEs.getItem(i);
        if (e) e->executar();
    }

    removerProjetis();
    removerMorto();
}

void ListaEntidades::removerProjetis() {
    int i = 0;
    while (i < LEs.getSize()) {
        Entidade* e = LEs.getItem(i);
        if (e) {
            Projetil* proj = dynamic_cast<Projetil*>(e);
            if (proj && !proj->getAtivo()) {
                LEs.deletar(e);
                delete e;
                continue;
            }
        }
        i++;
    }
}

void ListaEntidades::removerMorto() {
    int i = 0;
    while (i < LEs.getSize()) {
        Entidade* e = LEs.getItem(i);
        if (e) {
            if (auto* ini = dynamic_cast<entidades::personagens::Inimigo*>(e)) {
                if (ini->getVidas() <= 0) {
                    LEs.deletar(e);
                    delete e;
                    continue;
                }
            }
        }
        i++;
    }
}


void ListaEntidades::desenharTodos() {
    for (int i = 0; i < LEs.getSize(); i++) {
        Entidade* e = LEs.getItem(i);
        if (e) e->desenhar();
    }
}

Entidade* ListaEntidades::getItem(int pos) const {
    return LEs.getItem(pos);
}

}
