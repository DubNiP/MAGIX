#include "Chefao.hpp"

Chefao::Chefao(Vector2f pos, float vel, Jogador* pJog) : 
	Inimigo(pos, vel, pJog),
	raio(100.f), 
	LProjs()
{
	destruicao = 15;
	//carregarSprite();
	executar();


}

Chefao::~Chefao()
{
	vector<Projetil*>::iterator it;                          //mudar no futuro
	for (it = LProjs.begin(); it != LProjs.end(); ++it) {
		delete* it;
	}
}


void Chefao::danificar() {
	if (pJog) {
		pJog->tomarDano(destruicao);
	}
}

void Chefao::tomarDano(int dano) {
	if (dano > 0) {
		{
			int vidas = getVidas() - dano;
			if (vidas < 0) {
				vidas = 0;
			}
			setVidas(vidas);
		}
	}
}

void Chefao::mover() {
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

void Chefao::moverEsquerda() {
	Vector2f novaPos = getPos();
	novaPos.x -= vel;
	setPos(novaPos);
}

void Chefao::moverDireita() {
	Vector2f novaPos = getPos();
	novaPos.x += vel;
	setPos(novaPos);
}


void Chefao::perseguir(Vector2f posicaoJog, Vector2f posicaoInim) {
	if (posicaoJog.x < posicaoInim.x) {
		moverEsquerda();
	}
	else if (posicaoJog.x > posicaoInim.x) {
		moverDireita();
	}
}

void Chefao::executar() {
	mover();
	attPos();
}
 
void Chefao::carregarSprite() {                                                //MUDAR NO FUTURO!!!
	if (!carregarTexturaSprite("Textures/Chefao.png", false, false)) {
		throw "Deu merda aqui";
	}
	setScale(Vector2f(2.2f, 2.2f));
	setPos(pos);
}

//void salvar() {}	