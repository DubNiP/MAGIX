#pragma once
#include "Inimigo.hpp"
#include "Jogador.hpp"

namespace entidades {
    namespace personagens {

        class Golem : public Inimigo {
        private:
            int tamanho;
            int destruicao;
	        Clock relogio;
            Vector2f posInicial;
        public:
            Golem(Vector2f pos, Jogador* pJog, Vector2f vel);
            ~Golem();

            void danificar();
            void tomarDano(int dano);    //Discutir depois

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