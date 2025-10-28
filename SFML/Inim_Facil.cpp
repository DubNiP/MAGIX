#include "Inim_facil.hpp"
#include <cmath>

Inim_facil::Inim_facil(Vector2f pos, float vel, Jogador* pJog) :
	Inimigo(pos, vel, pJog),
	raio(100.f)
{
	destruicao = 7;
	//carregarSprite();
	executar();
}

Inim_facil::~Inim_facil()
{
}

void Inim_facil::danificar() {
	if (pJog) {
		pJog->tomarDano(destruicao);
	}
}

void Inim_facil::tomarDano(int dano) {
	if (dano > 0) {
		{
			int vidas = getVidas() - dano;
			if (vidas < 0) vidas = 0;
			setVidas(vidas);
		}
	}
}

void Inim_facil::mover() {
	if (pJog) {

		Vector2f posJog = pJog->getPos();
		Vector2f posInim = getPos();

		if (fabs(posJog.x - posInim.x) > raio) {
			if (posJog.x > posInim.x) {
				posInim.x = posInim.x + vel;
				setPos(posInim);
			}
			else
			{
				posInim.x = posInim.x - vel;
				setPos(posInim);
			}
		}
	}
	for (int i = 0; i < 4; i++) {

		i > 1 ? moverDireita() : moverEsquerda();
	}
}

void Inim_facil::moverEsquerda() {
	Vector2f novaPos = getPos();
	novaPos.x -= vel;
	setPos(novaPos);
}

void Inim_facil::moverDireita() {
	Vector2f novaPos = getPos();
	novaPos.x += vel;
	setPos(novaPos);
}


void Inim_facil::perseguir(Vector2f posicaoJog, Vector2f posicaoInim) {
	if (posicaoJog.x < posicaoInim.x) {
		moverEsquerda();
	}
	else if (posicaoJog.x > posicaoInim.x) {
		moverDireita();
	}
}

void Inim_facil::executar() {
	mover();
	attPos();
}

void Inim_facil::carregarSprite() {                          //MODIFICAR NO FUTURO!!
	if (!carregarTexturaSprite("Textures/InimigoFacil.png", false, false)) {
		throw "Deu merda aqui";
	}
	setScale(Vector2f(1.5f, 1.5f));
	setPos(pos);
}

//void salvar() {}	