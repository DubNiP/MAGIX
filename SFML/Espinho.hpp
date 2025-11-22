#pragma once
#include "Obstaculo.hpp"
#include "Mago.hpp"

namespace entidades {
	namespace obstaculos {

		class Espinho : public Obstaculo {
		private:
			short int danosidade;
		public:
			Espinho(Vector2f pos, Vector2f tam, int quantDano = 1);
			~Espinho();
			void salvarDataBuffer();
			void salvar();
			void carregar(float l, float a, bool dano, int quantDano);
			void executar();
			void obstaculizar(entidades::personagens::Mago* p);
			const int getDanosidade() const;
			void carregarSprite();
		};
	} 
}


