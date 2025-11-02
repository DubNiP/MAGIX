#pragma once
#include "Inimigo.hpp"
#include "Jogador.hpp"

namespace entidades { 
    namespace personagens {

        class Sapo : public Inimigo {
        private:
            float raio;
            int destruicao;
            Clock relogio;
            Vector2f posInicial;
        public:
            Sapo(Vector2f pos, float vel, Jogador* pJog);

            ~Sapo();

            void danificar();
            void tomarDano(int dano);

            void mover();
            void moverEsquerda();
            void moverDireita();
            void movimentoAleatorio();
            void perseguir(Vector2f posicaoJog, Vector2f posicaoInim);

            void executar();

            void carregarSprite();

            //void salvar() {  }

        };

    } 
}