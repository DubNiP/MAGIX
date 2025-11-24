#pragma once
#include "Obstaculo.hpp"


namespace entidades {
	namespace obstaculos {

		class Saida : public Obstaculo {
		private:
			bool aberta;
			float raio;
			Texture Tfechada;
			Texture Taberta;
		public:
			Saida(Vector2f pos, Vector2f tam);
			~Saida();
			void executar();
			void salvar();
			void salvarDataBuffer();
			void carregar(float larg, float alt, bool dano, bool abert, float r);
			void obstaculizar(entidades::personagens::Mago* p);
			void setSprite();
			void aplicarSpriteEstado();
			void atualizarPorRaio(const FloatRect& bMago);
		};
	}
}