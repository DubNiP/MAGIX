#include "Gerenciador_Colisoes.hpp"

GerenciadorColisoes::GerenciadorColisoes(Jogador* pJog, RenderWindow* win):
	pJog1(pJog),
	window(win)
{

}

GerenciadorColisoes::~GerenciadorColisoes() {
}

const bool GerenciadorColisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const {
	if (!pe1 || !pe2 || pe1 == pe2) {
		return false;
	}
	return pe1->getBounds().intersects(pe2->getBounds());
}

void GerenciadorColisoes::executar() {
	if (pJog1) {

	}
	else {
		return;
	}
}

void GerenciadorColisoes::setJog(Jogador* pJog) {
	pJog1 = pJog;
}

void GerenciadorColisoes::setWindow(RenderWindow* win) {
	window = win;
}

// Observação:  as demais funções comentadas no .hpp
// não são definidas aqui até que as dependências sejam implementadas