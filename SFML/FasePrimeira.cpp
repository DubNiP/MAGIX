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
	Inimigo* in1 = new Inim_Medio(Vector2f(200.f, 600.f), 1.f, jog);                   //substituir por algo no futuro..
	GC.incluirInimigo(in1);
	lista_ents.incluir(in1);
	Projetil* proj = new Projetil(Vector2f(50.f, 500.f), 1);
	lista_ents.incluir(proj);
	GC.incluirProjetil(proj);
}


void FasePrimeira::criarObsMedios() {
	Obstaculo* obs1 = new ObstDificil(Vector2f(400.f, 300.f), Vector2f(400.f, 40.f), false);     //substituir por algo no futuro..
	GC.incluirObstaculo(obs1);
	lista_ents.incluir(obs1);
	Obstaculo* chao = new ObstDificil(Vector2f(0.f, 680.f), Vector2f(1280.f, 40.f), false);
	GC.incluirObstaculo(chao);
	lista_ents.incluir(chao);

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