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
            Clock relogioPulo;
            Vector2f posInicial;
            bool bondade;
            int moverAleatorio;
            float velocidadeInicialX;  // Novo atributo

        public:
            Golem(Vector2f pos, Jogador* pJog, Vector2f vel);
            ~Golem();

            void danificar();
            void tomarDano(int dano, bool bondade);

            void mover();
            void moverEsquerda();
            void moverDireita();
            void movimentoAleatorio();
            void pular();

            void executar();
            void posicaoBarra();
            void carregarSprite();

            //void salvar() {  }

        };
    }
}