#include "Inimigo.hpp"

Inimigo::Inimigo(Vector2f pos, float vel, Jogador* jog) :
	Personagem(pos, vel),
	nivel_maldade(3),
	pJog(jog)
{
}

Inimigo::~Inimigo() {

}

