#include "Personagem.hpp"

namespace entidades {
	namespace personagens {

		Personagem::Personagem(Vector2f pos, Vector2f velocidade):
			Entidade(pos, velocidade),
			num_vidas(10)
		{
			barraVida = RectangleShape(Vector2f(30.f, 2.f));
			barraFundo = RectangleShape(Vector2f(30.f, 2.f));
			barraVida.setFillColor(Color::Green);
			barraFundo.setFillColor(Color::Transparent);
			barraFundo.setOutlineThickness(1.f);
			barraFundo.setOutlineColor(Color::Green);
		}

		Personagem::~Personagem() {

		}

		const int Personagem::getVidas() const {
			return num_vidas;
		}

		void Personagem::setVidas(int vidas) { 
			num_vidas = vidas; 
		}

		void Personagem::tomarDano(int dano, bool bond) {
			if (dano > 0) {
				int vidas = getVidas() - dano;
				if (vidas < 0) vidas = 0;
				setVidas(vidas);
			}
		}

		void Personagem::posicaoBarra() {

			FloatRect personagemBounds = getBounds();
			FloatRect barraBounds = barraFundo.getLocalBounds();

			float centroX = pos.x + (personagemBounds.width / 2.0f);

			Vector2f barraPos;
			barraPos.x = centroX - (barraBounds.width / 2.0f);  
			barraPos.y = pos.y - 10.f;  

			barraFundo.setPosition(barraPos);
			barraVida.setPosition(barraPos);

		}

		void Personagem::salvarDataBuffer() {
			Entidade::salvarDataBuffer();

			tempBuffer << num_vidas << " ";
			
		}
	} 
}