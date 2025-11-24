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
			float tempoSalvo;
			bool ativa;
			Clock tempo;
		public:
			Plataforma(Vector2f pos, Vector2f tam, bool dano = false, float amplitude = 100.f, float periodo = 2.f);
			~Plataforma();
		 
			void executar();
			void salvar();
			void salvarDataBuffer();
			void carregar(float l, float a, bool dano, float ampl, float per, float yin, float yant, bool ativ, float t);
			void obstaculizar(entidades::personagens::Mago* p);
			bool esmagou(entidades::personagens::Personagem* p) const;
			void setTempo(float t);
			void setAtiva();
			void carregarSprite();
		};
	} 
}