#include "Jogador.hpp"

Jogador::Jogador(Vector2f pos, float vel) :
	Personagem(pos, vel),
	pontos(0)
{
	setCorShape(Color::Red);
}

Jogador::~Jogador() {

}

//void Jogador::colidir(Inimigo* pIn) {}

void Jogador::executar() {
	processarInput(); 
	mover();
}

//void Jogador::salvar() {}

void Jogador::mover() {
	attPos();
}

void Jogador::processarInput() {
	float deltaTime = 1.0f / 60.0f;        //OLHAR DPS
	float movimento = vel * deltaTime;

	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
		pos.y -= movimento;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
		pos.y += movimento;
	}
	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
		pos.x -= movimento;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
		pos.x += movimento;
	}
}

int Jogador::getPontos() const { 
	return pontos;
}

void Jogador::adicionarPontos(int pts) { 
	pontos += pts; 
}

void Jogador::reseta(Vector2f posicao, int vidas, int pts) {
	setPos(posicao);
	num_vidas = vidas;
	pontos = pts;
}