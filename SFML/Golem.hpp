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
            Golem(Vector2f pos, float vel, Jogador* pJog);
            ~Golem();

            void danificar();
            void tomarDano(int dano);    //Discutir depois

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