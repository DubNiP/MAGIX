#pragma once
#include "Inimigo.hpp"
#include "Mago.hpp"

namespace entidades { 
    namespace personagens {

        class Sapo : public Inimigo {
        private:
            float raio;
            float intervaloPulo;
        public:
            Sapo(Vector2f pos, Mago* pJog, Vector2f vel);

            ~Sapo();

            void danificar();
            void tomarDano(int dano, bool bondade);

            void mover();
            void moverEsquerda();
            void moverDireita();
            void movimentoAleatorio();

            void executar();
            void posicaoBarra();

            void carregarSprite();

            //void salvar() {  }

        };

    } 
}