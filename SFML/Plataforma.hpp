#pragma once

#include "Obstaculo.hpp"
#include "Personagem.hpp"
#include "Mago.hpp"

using namespace sf;

namespace entidades { 
	namespace obstaculos {

		class Plataforma : public Obstaculo {
		private:
			float amplitude;     
			float periodo;        
			float yIn;       
			float yAnt;      
			bool ativa;
			Clock tempo;
		public:
			Plataforma(Vector2f pos, Vector2f tam, bool dano = false, float amplitude = 100.f, float periodo = 2.f);
			~Plataforma();

			void executar();
			void obstaculizar(entidades::personagens::Mago* p);
			bool esmagou(entidades::personagens::Personagem* p) const;
			void setAtiva();
			void carregarSprite();
		};
	} 
}