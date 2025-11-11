#pragma once

#include "Obstaculo.hpp"

namespace entidades {
	namespace obstaculos {

		class Teia :public Obstaculo {
		private:
			int vida;
			bool ativo;
		public:
			Teia(Vector2f pos, Vector2f tam);
			~Teia();

			void executar();
			void obstaculizar(entidades::personagens::Mago* p);
			void carregarSprite();

			void setVida(int vida);
			const int getVida() const;
			const bool getAtivo() const;
		};
	} 
}