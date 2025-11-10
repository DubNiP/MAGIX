#pragma once

#include "Jogador.hpp"
#include "Entidade.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

namespace entidades {
	namespace obstaculos {

		class Obstaculo : public Entidade {
		protected:
			bool danoso;

			//COMENTAR COM O PROFESSOR
			float largura;
			float altura;

		public:
			Obstaculo(Vector2f pos, Vector2f tam, bool dano = false);
			~Obstaculo();
			//void salvarDataBuffer();
			virtual void executar() = 0;
			//virtual void salvar() = 0;
			virtual void obstaculizar(entidades::personagens::Jogador* p) = 0;                 //está sem relação tanto no nosso diagrama quanto no do professor.

			const bool getDanoso() const;
		};

	} 
}