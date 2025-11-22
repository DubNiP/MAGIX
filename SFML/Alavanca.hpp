#pragma once
#include "Plataforma.hpp"
#include "Obstaculo.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace entidades {
	namespace obstaculos {
		class Alavanca : public Obstaculo {
		private:
			Plataforma* p;
			bool acionada;
		public:
			Alavanca(Vector2f pos, Vector2f tam, Plataforma* pPlat = NULL);
			~Alavanca();
			
			void executar();
			void salvar();
			void salvarDataBuffer();
			void carregar(float l, float a, bool dano, bool acionad);

			void obstaculizar(entidades::personagens::Mago* p);
			void carregarSprite();
		};
	}
}