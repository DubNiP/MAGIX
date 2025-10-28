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



class GerenciadorColisoes {
private:
    vector<Inimigo*>  LIs;
    list<Obstaculo*>  LOs;
    set<Projetil*>    LPs;  
    Jogador* pJog1;
    RenderWindow* window;
public:
    GerenciadorColisoes(Jogador* pJog = NULL,RenderWindow* window = NULL);
    ~GerenciadorColisoes();

    const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;                  //conferir se está no diagrama.
    void colidiu(Entidade* pe1, Entidade* pe2, FloatRect jog, FloatRect obs);

    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsInimgs();
    void tratarColisoesJogsProjeteis();

    void incluirInimigo(Inimigo* pInimigo);
    void incluirObstaculo(Obstaculo* pObstaculo);
    void incluirProjetil(Projetil* pProjetil);

    void limparObstaculos();
    void limparInimigos();
    void limparProjetis();

    void executar();

    void setJog(Jogador* pJog);
    void setWindow(RenderWindow* win);

    void limiteDeTela();
    void limiteDeTelaJogador(int X, int Y);
    void limiteDeTelaProjeteis(int X, int Y);
};