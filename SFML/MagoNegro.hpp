#pragma once
#include "Inimigo.hpp"
#include "Jogador.hpp"
#include "ListaEntidades.hpp"
#include <SFML/System/Clock.hpp>
#include "Projetil.hpp"

namespace entidades {
    namespace personagens {

        class MagoNegro : public Inimigo {
        private:
            int tamanho;
            int destruicao;
            Clock relogio;
            Clock relogioPulo;
            Clock ataqueClock;
            Vector2f posInicial;
            bool bondade;
            bool apto;
            int moverAleatorio;
            float velocidadeInicialX;
            listas::ListaEntidades* listaEntidades;
            Gerenciadores::GerenciadorColisoes* GC;

        public:
            MagoNegro(Vector2f pos, Jogador* pJog, Vector2f vel);
            ~MagoNegro();

            void incluirListaEntidades(listas::ListaEntidades* pLEnt);
            void incluirGerenciadorColisoes(Gerenciadores::GerenciadorColisoes* pGC);

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

            void criarProjetil();

        };

    }
}