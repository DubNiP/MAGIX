#pragma once

#include "Entidade.hpp"
#include "Jogador.hpp"
//#include "Inimigo.hpp"
#include "Obstaculo.hpp"
//#include "Projetil.hpp"
#include <vector>
#include <list>
#include <set>

using namespace std;

class GerenciadorColisoes {
private:
    //vector<Inimigo*>  LIs;   // lista de inimigos
    list<Obstaculo*>  LOs;
    //set<Projetil*>    LPs;   // conjunto de projéteis
    Jogador* pJog1;
    RenderWindow* window;

public:
    GerenciadorColisoes(Jogador* pJog = NULL,RenderWindow* window = NULL);
    ~GerenciadorColisoes();

    const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;

    void tratarColisoesJogsObstaculos();
    // void tratarColisoesJogsInimigos();
    // void tratarColisoesJogsProjeteis();

    // void incluirInimigo(Inimigo* pInimigo);
    void incluirObstaculo(Obstaculo* pObstaculo);
    // void incluirProjetil(Projetil* pProjetil);

    void limparObstaculos();

    void executar();

    void setJog(Jogador* pJog);
    void setWindow(RenderWindow* win);

    void limiteDeTela();
};