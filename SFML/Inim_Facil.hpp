#pragma once
#include "Inimigo.hpp"
#include "Jogador.hpp"

class Inim_facil : public Inimigo {
private:
    float raio;
    int destruicao;
public:
    Inim_facil(Vector2f pos, float vel, Jogador* pJog);

    ~Inim_facil();

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