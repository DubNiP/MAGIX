#pragma once
#include "Inimigo.hpp"
#include "Jogador.hpp"

class Inim_Medio : public Inimigo {
private:
    int tamanho;
    int destruicao;
public:
    Inim_Medio(Vector2f pos, float vel, Jogador* pJog);
    ~Inim_Medio();

    void danificar();
    void tomarDano(int dano);    //Discutir depois

    void mover();
    void moverEsquerda();
    void moverDireita();
    void perseguir(Vector2f posicaoJog, Vector2f posicaoInim);

    void executar();

    void carregarSprite();

    //void salvar() {  }

};