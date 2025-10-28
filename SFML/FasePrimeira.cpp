#include "FasePrimeira.hpp"

FasePrimeira::FasePrimeira(Jogador* pJog):
	Fase(pJog),
	maxInimMedios(10)
{

}

FasePrimeira::~FasePrimeira() {

}

void FasePrimeira::criarInimigos() {
	//criarInimFaceis();
	criarInimMedios();
}


void FasePrimeira::criarObstaculo() {
	//criarPlataformas();
	criarObsMedios();
}


void FasePrimeira::criarInimMedios() {
	Inimigo* in1 = new Inim_Medio(Vector2f(200.f, 200.f), 1.f, jog);                   //substituir por algo no futuro..
	GC.incluirInimigo(in1);
	lista_ents.incluir(in1);
}


void FasePrimeira::criarObsMedios() {
	Obstaculo* obs1 = new ObstDificil(Vector2f(400.f, 300.f), Vector2f(200.f, 40.f), false, 0);     //substituir por algo no futuro..
	GC.incluirObstaculo(obs1);
	lista_ents.incluir(obs1);
}


void FasePrimeira::carregarFundo() {
    textFundo = new Texture();
    if (!textFundo->loadFromFile("Textures/background 3.png")) {
		throw "Deu merda aqui";
    }
    spriteFundo = new Sprite(*textFundo);
    Vector2u tamTextura = textFundo->getSize();
    float escalaX = 1280.f / tamTextura.x;
    float escalaY = 720.f / tamTextura.y;
    spriteFundo->setScale(escalaX, escalaY);
}