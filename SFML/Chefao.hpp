#pragma once
#include "Inimigo.hpp"
#include "Jogador.hpp"
#include "projetil.hpp"
#include <vector>

namespace entidades { 
    namespace personagens {

        class Chefao : public Inimigo {
        private:
            float raio;
            short int forca;
        public:
            Chefao(Vector2f pos, Vector2f vel, Jogador* pJog);

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

    } 
}