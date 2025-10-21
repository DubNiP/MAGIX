#include "Jogador.hpp"

Jogador::Jogador(Vector2f pos) :
	Personagem(pos),
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

void Jogador::limitarMovimento(const Vector2u& windowSize) {            //GERENCIADOR DE COLISOES? (ACHO Q N)
	FloatRect boundJog = shape.getGlobalBounds();

	const int X = windowSize.x - boundJog.width;
	const int Y = windowSize.y - boundJog.height;
	if (pos.x < 0)   pos.x = 0;
	if (pos.y < 0)   pos.y = 0;
	if (pos.x > X) pos.x = X;
	if (pos.y > Y) pos.y = Y;
}

int Jogador::getPontos() const { 
	return pontos;
}
void Jogador::adicionarPontos(int pts) { 
	pontos += pts; 
}