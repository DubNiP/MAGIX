#include "Inim_Medio.hpp"

Inim_Medio::Inim_Medio(Vector2f pos, float vel, Jogador* pJog) : 
	Inimigo(pos, vel, pJog),
	raio(500.f)
{
	destruicao = 1;
	carregarSprite();
	executar();
}

Inim_Medio::~Inim_Medio()
{
}


void Inim_Medio::danificar() {
	if (pJog) {
		pJog->tomarDano(destruicao);
	}
}

void Inim_Medio::tomarDano(int dano) {
	if (dano > 0) {
		{
			int vidas = getVidas() - dano;
			if (vidas < 0) vidas = 0;
			setVidas(vidas);
		}
	}
}

void Inim_Medio::mover() {
	if (pJog) {
		Vector2f posJog = pJog->getPos();
		Vector2f posInim = getPos();

		if (fabs(posJog.x - posInim.x) < raio) {
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

void Inim_Medio::moverEsquerda() {
	Vector2f novaPos = getPos();
	novaPos.x -= vel;
	setPos(novaPos);
}

void Inim_Medio::moverDireita() {
	Vector2f novaPos = getPos();
	novaPos.x += vel;
	setPos(novaPos);
}


void Inim_Medio::perseguir(Vector2f posicaoJog, Vector2f posicaoInim) {
	if (posicaoJog.x < posicaoInim.x) {
		moverEsquerda();
	}
	else if (posicaoJog.x > posicaoInim.x) {
		moverDireita();
	}
}

void Inim_Medio::executar() {
	mover();
	attPos();
}

void Inim_Medio::carregarSprite() {
	if (!carregarTexturaSprite("Textures/Golem_idle1.png", false, false)) {
		throw "Deu merda aqui";
	}
	setScale(Vector2f(2.f, 2.f));
	setPos(pos);
}

//void salvar() {}	