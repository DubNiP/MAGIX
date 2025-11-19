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
            int moverAleatorio;
            float velocidadeInicialX;
			fases::Fase* faseAtual;

        public:
            MagoNegro(Vector2f pos, Mago* pJog, Vector2f vel);
            ~MagoNegro();

            void setFaseAtual(fases::Fase* f);

            void danificar();
            void tomarDano(int dano, bool bondade);

            void mover();
            void moverEsquerda();
            void moverDireita();
            void movimentoAleatorio();
            void pular();

            void executar();
            void salvar();
            void salvarDataBuffer();
            void carregarSprite();

        };

    }
}