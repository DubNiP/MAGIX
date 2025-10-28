#pragma once
#include "Inimigo.hpp"
#include "Jogador.hpp"
#include "projetil.hpp"
#include <vector>

class Chefao : public Inimigo {
private:
    float raio;
    int destruicao;
    vector<Projetil*> LProjs;               //mover os projeteis para lista entidades?
public:
    Chefao(Vector2f pos, float vel, Jogador* pJog);

    ~Chefao();

    void danificar();
    void tomarDano(int dano);

    void mover();
    void moverEsquerda();
    void moverDireita();
    void perseguir(Vector2f posicaoJog, Vector2f posicaoInim);

    void executar();

    void carregarSprite();

    //void salvar() {  }

};