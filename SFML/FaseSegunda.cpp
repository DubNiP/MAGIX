#include "FaseSegunda.hpp"
#include "MagoNegro.hpp"
#include "Bloco.hpp"
#include "Saida.hpp"
#include "Plataforma.hpp"
#include "Alavanca.hpp"

using namespace fases;

FaseSegunda::FaseSegunda(entidades::personagens::Jogador* pJog) :
	Fase(pJog),
	maxChefoes(1)
{
}

FaseSegunda::~FaseSegunda() {
}

void FaseSegunda::criarInimigos() {
	criarChefoes();
}

void FaseSegunda::criarObstaculo() {
	criarObsMedios();

}


void FaseSegunda::criarChefoes() {

	entidades::personagens::MagoNegro* pM = new entidades::personagens::MagoNegro(Vector2f(900.f, 600.f), jog, Vector2f(3.f, 50.f));
	criaEntidade(pM);
	pM->incluirGerenciadorColisoes(&GC);
	pM->incluirListaEntidades(&lista_ents);

}


void FaseSegunda::criarObsMedios() {

}


void FaseSegunda::criarBlocos() {


	criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 700.f),	Vector2f(1280.f, 20.f)));

	criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 0.f), Vector2f(20.f, 720.f) ));

	criaEntidade(new entidades::obstaculos::Bloco(Vector2f(1260.f, 0.f), Vector2f(20.f, 720.f)));

	criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 0.f), Vector2f(1280.f, 20.f)));

}


void FaseSegunda::carregarFundo() {
	textFundo = new Texture();

	if (!textFundo->loadFromFile("Textures/background 2.png")) {
		throw "textura não carregada";
	}

	spriteFundo = new Sprite(*textFundo);

	Vector2u tam = textFundo->getSize();
	float escX = 1280.f / tam.x;
	float escY = 720.f / tam.y;

	spriteFundo->setScale(escX, escY);
}
