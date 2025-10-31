#include "FasePrimeira.hpp"
#include "Plataforma.hpp"

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
    entidades::personagens::Inimigo* in1 = new entidades::personagens::Golem(Vector2f(200.f, 600.f), 1.f, jog);
    GC.incluirInimigo(in1);
    lista_ents.incluir(in1);
    Projetil* proj = new Projetil(Vector2f(50.f, 500.f), 1);
    lista_ents.incluir(proj);
    GC.incluirProjetil(proj);
}

void FasePrimeira::criarObsMedios() {
    //1280 e 720
	entidades::obstaculos::Obstaculo* obs1 = new entidades::obstaculos::ObstDificil(Vector2f(0.f, 500.f), Vector2f(400.f, 40.f), false);     //substituir por algo no futuro..
	GC.incluirObstaculo(obs1);
	lista_ents.incluir(obs1);

	entidades::obstaculos::Obstaculo* obs2 = new entidades::obstaculos::ObstDificil(Vector2f(600.f, 500.f), Vector2f(680.f, 40.f), false);     //substituir por algo no futuro..
	GC.incluirObstaculo(obs2);
	lista_ents.incluir(obs2);

	entidades::obstaculos::Obstaculo* obs3 = new entidades::obstaculos::ObstDificil(Vector2f(0.f, 280.f), Vector2f(760.f, 40.f), false);     //substituir por algo no futuro..
	GC.incluirObstaculo(obs3);
	lista_ents.incluir(obs3);

	entidades::obstaculos::Obstaculo* obs4 = new entidades::obstaculos::ObstDificil(Vector2f(980.f, 0.f), Vector2f(40.f, 350.f), false);     //substituir por algo no futuro..
	GC.incluirObstaculo(obs4);
	lista_ents.incluir(obs4);

	entidades::obstaculos::Obstaculo* degrau1 = new entidades::obstaculos::ObstDificil(Vector2f(1020.f, 170.f), Vector2f(80.f, 40.f), false);     //substituir por algo no futuro..
	GC.incluirObstaculo(degrau1);
	lista_ents.incluir(degrau1);

	entidades::obstaculos::Obstaculo* degrau2 = new entidades::obstaculos::ObstDificil(Vector2f(1020.f, 310.f), Vector2f(80.f, 40.f), false);     //substituir por algo no futuro..
	GC.incluirObstaculo(degrau2);
	lista_ents.incluir(degrau2);

	entidades::obstaculos::Obstaculo* degrau3 = new entidades::obstaculos::ObstDificil(Vector2f(1180.f, 380.f), Vector2f(80.f, 40.f), false);     //substituir por algo no futuro..
	GC.incluirObstaculo(degrau3);
	lista_ents.incluir(degrau3);

	entidades::obstaculos::Obstaculo* degrau4 = new entidades::obstaculos::ObstDificil(Vector2f(1180.f, 240.f), Vector2f(80.f, 40.f), false);     //substituir por algo no futuro..
	GC.incluirObstaculo(degrau4);
	lista_ents.incluir(degrau4);

	entidades::obstaculos::Obstaculo* chao = new entidades::obstaculos::ObstDificil(Vector2f(0.f, 700.f), Vector2f(1300.f, 20.f), false);
	GC.incluirObstaculo(chao);
	lista_ents.incluir(chao);


	entidades::obstaculos::Obstaculo* teto = new entidades::obstaculos::ObstDificil(Vector2f(0.f, 0.f), Vector2f(1280.f, 20.f), false);
	GC.incluirObstaculo(teto);
	lista_ents.incluir(teto);

	entidades::obstaculos::Obstaculo* paredeEsq = new entidades::obstaculos::ObstDificil(Vector2f(0.f, 0.f), Vector2f(20.f, 720.f), false);
	GC.incluirObstaculo(paredeEsq);
	lista_ents.incluir(paredeEsq);

	entidades::obstaculos::Obstaculo* paredeDir = new entidades::obstaculos::ObstDificil(Vector2f(1260.f, 0.f), Vector2f(20.f, 720.f), false);
	GC.incluirObstaculo(paredeDir);
	lista_ents.incluir(paredeDir);


	// Plataforma de teste
    Vector2f platPos(400.f, 588.f);
    Vector2f platTam(200.f, 20.f);
    auto* plat = new entidades::obstaculos::Plataforma(platPos, platTam, false, /*amplitude*/90.f, /*periodo*/5.f);
    GC.incluirObstaculo(plat);
    lista_ents.incluir(plat);
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