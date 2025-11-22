#pragma once
#include "Inimigo.hpp"
#include "Mago.hpp"
#include <SFML/System/Clock.hpp>
#include "Projetil.hpp"

namespace entidades {
    namespace personagens {

        class MagoNegro : public Inimigo {
        private:
            int tamanho;
            Clock ataqueClock;
            bool apto;
			fases::Fase* faseAtual;

        public:
            MagoNegro(Vector2f pos, Mago* pJog, Vector2f vel);
            ~MagoNegro();

            void setFaseAtual(fases::Fase* f);

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
				int d, float tS, float tP, int t, bool apt);
            void carregarSprite();

        };

    }
}