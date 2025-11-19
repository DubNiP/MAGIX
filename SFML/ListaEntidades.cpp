#include "ListaEntidades.hpp"
#include <filesystem> // Para manipulação de sistemas de arquivos
#include <fstream> // Para operações de arquivo

using namespace std;


//OBS: TEM ALGUNS METODOS QUE ENVOLVEM EXCLUSÃO QUE TEM UMA COMPLEXIDADE ALTA ACREDITO EU


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
        Lista<Entidade>::Iterator it = LEs.begin();
        while (it != LEs.end()) {
            Entidade* e = *it;
            if (e) {
                delete e;
            }
            ++it;
        }
        LEs.limpar();
    }

    void ListaEntidades::limparPreservando(Entidade* keep) {                  //isso é zoado, é bom dar um jeito de remover isso...
        Lista<Entidade>::Iterator it = LEs.begin();
        while(it != LEs.end()) {
            Entidade* e = *it;
            if (e && e != keep) {
                delete e;
            }
            ++it;
        }
        LEs.limpar();
    }


    void ListaEntidades::executarTodos() {
        Lista<Entidade>::Iterator it = LEs.begin();
        while(it != LEs.end()) {
            Entidade* e = *it;
            if (e) e->executar();
            ++it;
        }

        removerProjetis();
        removerMorto();
    }

    void ListaEntidades::removerProjetis() {
        Lista<Entidade>::Iterator it = LEs.begin();
        while (it != LEs.end()) {
            Entidade* e = *it;
            if (e) {
                if (auto* proj = dynamic_cast<entidades::Projetil*>(e)) {
                    if (!proj->getAtivo()) {
                        LEs.deletar(e);
                        delete e;
                        it = LEs.begin();
                        continue;
                    }
                }

            }
            ++it;
        }
    }

    void ListaEntidades::removerMorto() {
        Lista<Entidade>::Iterator it = LEs.begin();
        while (it != LEs.end()) {
            Entidade* e = *it;
            if (e) {
                if (auto* ini = dynamic_cast<entidades::personagens::Inimigo*>(e)) {
                    if (ini->getVidas() <= 0) {
                        LEs.deletar(e);
                        delete e;
                        it = LEs.begin();
                        continue;
                    }
                }
                if (auto* teia = dynamic_cast<entidades::obstaculos::Teia*>(e)) {
                    if (!teia->getAtivo()) {
                        LEs.deletar(e);
                        delete e;
                        it = LEs.begin();
                        continue;
                    }
                }
            }
            ++it;
        }
    }


    void ListaEntidades::desenharTodos() {
        Lista<Entidade>::Iterator it = LEs.begin();
        while (it != LEs.end()) {
            Entidade* e = *it;
            if (e) e->desenhar();
            ++it;
        }
    }

    void ListaEntidades::salvarTodos() {
        
        try {
            std::filesystem::create_directories("Save");
        } catch (...) {
        }

        {
            std::ofstream out("Save/save.txt", std::ios::out | std::ios::trunc);
            if (!out.is_open()) {
                std::cerr << "Erro: nao foi possivel abrir Save/save.txt para salvar." << std::endl;
                return;
            }
        }

        Lista<Entidade>::Iterator it = LEs.begin();
        int count = 0;
        while (it != LEs.end()) {
            Entidade* e = *it;
            if (e) {
                ++count;
                e->salvar();
            }
            ++it;
        }
        std::cout << "ListaEntidades::salvarTodos() -> entidades salvas = " << count << std::endl;
    }

    void ListaEntidades::retomarTodos() {
        Lista<Entidade>::Iterator it = LEs.begin();
        while(it != LEs.end()) {
            Entidade* e = *it;
            if (e) {
                e->retomar();
            }
            ++it;
        }
    }
}