#include "Inimigo.hpp"

Inimigo::Inimigo(Vector2f pos, float vel, Jogador* jog) :
	Personagem(pos, vel),
	nivel_maldade(3),
	moverAleatorio(-1),
	pJog(jog)
{
}

Inimigo::~Inimigo() {

}

