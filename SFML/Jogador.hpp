#pragma once
#include "Personagem.hpp"
#include "ListaEntidades.hpp"
#include <SFML/System/Clock.hpp>
#include "Projetil.hpp"

namespace Gerenciadores {
	class GerenciadorColisoes;
}

using namespace sf;

namespace entidades { 
	namespace personagens{

		class Jogador: public Personagem {
		protected:
			int pontos;
			float invencibilidade;
			Clock danoClock;
			Clock ataqueClock;
			bool naTeia;
			bool apto;
			listas::ListaEntidades* listaEntidades;
			Gerenciadores::GerenciadorColisoes* GC;

		public:
			Jogador(Vector2f pos, Vector2f vel);
			~Jogador();

			void incluirListaEntidades(listas::ListaEntidades* pLEnt);

			void incluirGerenciadorColisoes(Gerenciadores::GerenciadorColisoes* pGC);

			void executar();
			//void salvar();
			void mover();

			void processarInput();

			const int getPontos() const;
			void adicionarPontos(int pts);

			void reseta(Vector2f pos,int vidas, int pontos);
			void tomarDano(int dano, bool bond);
			void posicaoBarra();
			void carregarSprite();
			void setNaTeia(bool t);
			void criarProjetil();
		};
	} 
}