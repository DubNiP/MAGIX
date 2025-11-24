#include "ListaEntidades.hpp"
#include "Mago.hpp"   // para dynamic_cast e getters do jogador
#include <filesystem> // Para manipulação de sistemas de arquivos
#include <fstream> // Para operações de arquivo
#include <sstream>
#include <system_error>

using namespace std;

//Padrão de projeto Iterator usado em todos os iteradores.

//OBS: TEM ALGUNS METODOS QUE ENVOLVEM EXCLUSÃO QUE TEM UMA COMPLEXIDADE ALTA ACREDITO EU.


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


    void ListaEntidades::limparPreservando(Entidade* J1,Entidade* J2) {                  //isso é zoado, é bom dar um jeito de remover isso...
        Lista<Entidade>::Iterator it = LEs.begin();                           //POSSIVEL SOLUCAO: COLOCAR DYNAMIC CAST PRA JOGADOR E N EXCLUIR SE FOR,
        while (it != LEs.end()) {                                             //MAS PODE DAR MERDA COM OS JOGADORES 1 E 2.
            Entidade* e = *it;
            if (e && e != J1 && e !=J2) {
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
            filesystem::create_directories("Save");
        }
        catch (const filesystem::filesystem_error& e) {
            cerr << "Aviso: nao foi possivel criar o diretorio Save/: "
                << e.what() << endl;
            return;
        }

        string nomeStr = "";
        int pontos = 0;
        int numFase = 0;

        entidades::personagens::Mago* m = NULL;

        Lista<Entidade>::Iterator itFind = LEs.begin();
        while (itFind != LEs.end()) {
            Entidade* e = *itFind;
            if (e) {
                if (auto* mago = dynamic_cast<entidades::personagens::Mago*>(e)) {
                    m = mago;
                    nomeStr = m->getNome() ? m->getNome() : "";
                    pontos = m->getPontos();
                    numFase = m->getNumFase();
                    break;
                }
            }
            ++itFind;
        }
        if (!m) {
            cerr << "Erro: Mago não encontrado na lista de entidades." << endl;
            return;
        }


        const string rankingPath = "Save/ranking.txt";

        vector<tuple<string,int,int>> ranking;
        {
            ifstream in(rankingPath);
            if (in.is_open()) {
                string n;
                int p;
                int f;
                while (in >> n >> p >> f) {
                    ranking.emplace_back(n, p, f);
                }
                in.close();
            }
        }

        bool atualizado = false;
        for (auto& t : ranking) {
            if (get<0>(t) == nomeStr) {
                get<1>(t) = pontos;
                get<2>(t) = numFase;
                atualizado = true;
                break;
            }
        }
        if (!atualizado) {
            ranking.emplace_back(nomeStr, pontos, numFase);
        }

        sort(ranking.begin(), ranking.end(),
            [](const auto& a, const auto& b) {
                return get<0>(a) < get<0>(b);
            });

        ofstream outRanking;
        outRanking.open(rankingPath, ios::out | ios::trunc);
        if (!outRanking.is_open()) {
            cerr << "Erro: nao foi possivel abrir " << rankingPath << " para salvar ranking." << std::endl;
           
        } else {
            for (const auto& t : ranking) {
                outRanking << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;
            }
            outRanking.close();
        }

        ofstream outPlayer;
        outPlayer.open(m->getCaminho(), ios::out | ios::trunc);
        if (!outPlayer.is_open()) {
            cerr << "Erro: nao foi possivel abrir " << m->getCaminho() << " para salvar." << std::endl;
			fflush(stdin);
        } else {
            outPlayer << nomeStr << " " << pontos << " " << numFase << endl;
            outPlayer.close();
        }

        Lista<Entidade>::Iterator it = LEs.begin();
        while (it != LEs.end()) {
            Entidade* e = *it;
            if (e) {
                e->salvar();
            }
            ++it;
        }
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