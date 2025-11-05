#pragma once
#include "Obstaculo.hpp"


namespace entidades {
	namespace obstaculos {

		class Saida : public Obstaculo {
		private:
		public:
			Saida(Vector2f pos, Vector2f tam);
			~Saida();
			void executar();
			void obstaculizar(entidades::personagens::Jogador* p);
			void setSprite();
		};
	}
}