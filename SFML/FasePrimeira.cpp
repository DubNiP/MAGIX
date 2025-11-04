#include "FasePrimeira.hpp"
#include "Plataforma.hpp"
#include "Sapo.hpp"
#include "Obst_Medio.hpp"

using namespace fases;

FasePrimeira::FasePrimeira(entidades::personagens::Jogador* pJog):
    Fase(pJog),
    maxGolems(10)
{
}

FasePrimeira::~FasePrimeira() {
}

void FasePrimeira::criarInimigos() {
    criarGolems();
}

void FasePrimeira::criarObstaculo() {
    criarObsMedios();
}

void FasePrimeira::criarGolems() {
	criaEntidade(new entidades::personagens::Golem(Vector2f(200.f, 600.f), jog, Vector2f(1.f, 30.f)));
	criaEntidade(new Projetil(Vector2f(50.f, 500.f), 1));
    criaEntidade(new entidades::personagens::Sapo(Vector2f(300.f, 250.f), jog, Vector2f(50.f, 120.0f)));
}

void FasePrimeira::criarObsMedios() {
    //1280 e 720
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 500.f), Vector2f(400.f, 40.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(600.f, 500.f), Vector2f(680.f, 40.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 280.f), Vector2f(760.f, 40.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(980.f, 0.f), Vector2f(40.f, 350.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(1020.f, 170.f), Vector2f(80.f, 40.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(1020.f, 310.f), Vector2f(80.f, 40.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(1180.f, 380.f), Vector2f(80.f, 40.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(1180.f, 240.f), Vector2f(80.f, 40.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 700.f), Vector2f(1300.f, 20.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 0.f), Vector2f(1280.f, 20.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 0.f), Vector2f(20.f, 720.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(1260.f, 0.f), Vector2f(20.f, 720.f)));


    criaEntidade(new entidades::obstaculos::Espinho(Vector2f(950.f, 690.f), Vector2f(80.f,10.f), 1));
    criaEntidade(new entidades::obstaculos::ObstMedio(Vector2f(800.f, 650.f), Vector2f(60.f, 50.f)));

    // Plataforma de teste
    Vector2f platPos(400.f, 588.f);
    Vector2f platTam(200.f, 20.f);
    criaEntidade(new entidades::obstaculos::Plataforma(platPos, platTam, false, 90.f, 5.f));
}

void FasePrimeira::carregarFundo() {
    textFundo = new Texture();
    if (!textFundo->loadFromFile("Textures/background 3.png")) {
        throw "textura não carregada";
    }
    spriteFundo = new Sprite(*textFundo);
    Vector2u tamTextura = textFundo->getSize();
    float escalaX = 1280.f / tamTextura.x;
    float escalaY = 720.f / tamTextura.y;
    spriteFundo->setScale(escalaX, escalaY);
}