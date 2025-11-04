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
			Clock relogioDePulo;
            float intervaloPulo;
        public:
            Sapo(Vector2f pos, Jogador* pJog, Vector2f vel);

            ~Sapo();

            void danificar();
            void tomarDano(int dano);

            void mover();
            void moverEsquerda();
            void moverDireita();
            void movimentoAleatorio();

            void executar();

            void carregarSprite();

            //void salvar() {  }

        };

    } 
}