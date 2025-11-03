#pragma once

#include "Entidade.hpp"
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Obstaculo.hpp"
#include "Projetil.hpp"
#include <vector>
#include <list>
#include <set>

using namespace std;

//POR ENQUANTO A COLISÃO PEGA OS QUADRADOS DOS FORMATOS, VALE A PENA ANALISAR ISSO E MELHORAR NO FUTURO?

namespace Gerenciadores {

    class GerenciadorColisoes {
    private:
        vector<entidades::personagens::Inimigo*>  LIs;
        list<entidades::obstaculos::Obstaculo*>  LOs;
        set<Projetil*>    LPs;  
        entidades::personagens::Jogador* pJog1;
        RenderWindow* window;
    public:
        GerenciadorColisoes(entidades::personagens::Jogador* pJog = NULL,RenderWindow* window = NULL);
        ~GerenciadorColisoes();

        const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;                  //conferir se está no diagrama.
        void colidiu(Entidade* pe1, Entidade* pe2);

        void tratarColisoesJogsObstacs();
        void tratarColisoesJogsInimgs();
        void tratarColisoesJogsProjeteis();

        void tratarColisoesInimgsObstacs();
        void tratarColisoesProjeteisObstacs();
        void tratarColisoesProjeteisInimgs();
        void tratarColisoesInimgs();

        void incluirInimigo(entidades::personagens::Inimigo* pInimigo);
        void incluirObstaculo(entidades::obstaculos::Obstaculo* pObstaculo);
        void incluirProjetil(Projetil* pProjetil);

        void limparObstaculos();
        void limparInimigos();
        void limparProjetis();

        void executar();

        void setJog(entidades::personagens::Jogador* pJog);
        void setWindow(RenderWindow* win);

        void limiteDeTela();
        void limiteDeTelaJogador(int X, int Y);
        void limiteDeTelaProjeteis(int X, int Y);
    };

}