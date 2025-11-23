#pragma once
#include "Inimigo.hpp"
#include "Mago.hpp"

namespace entidades {
    namespace personagens {

        class Golem : public Inimigo {
        private:
            int tamanho;

        public:
            Golem(Vector2f pos, Mago* pJog, Vector2f vel);
            ~Golem();

            void danificar(Mago* pJog);
            void tomarDano(int dano, bool bondade);

            void mover();
            void moverEsquerda();
            void moverDireita();
            void movimentoAleatorio();

            void executar();
            void salvar();
			void salvarDataBuffer();
            void carregar(int num, int m, Mago* jog, short mA, Vector2f pI,
				int d, int tam);
            void carregarSprite();

        };
    }
}