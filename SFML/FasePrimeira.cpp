#include "FasePrimeira.hpp"

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
    criarSapos();
}

void FasePrimeira::criarObstaculo() {
    criarTeias();
    criarPlataformas();
    criaEntidade(new entidades::obstaculos::Saida(sf::Vector2f(60.f, 197.f), sf::Vector2f(47.f, 55.f)));
}

void FasePrimeira::criarBlocos() {
    //1280 e 720

    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 500.f), Vector2f(400.f, 40.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(600.f, 500.f), Vector2f(680.f, 40.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 280.f), Vector2f(760.f, 40.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(980.f, 0.f), Vector2f(40.f, 350.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(1020.f, 150.f), Vector2f(80.f, 40.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(1020.f, 290.f), Vector2f(80.f, 40.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(1180.f, 360.f), Vector2f(80.f, 40.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(1180.f, 220.f), Vector2f(80.f, 40.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 700.f), Vector2f(1300.f, 20.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 0.f), Vector2f(1280.f, 20.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 0.f), Vector2f(20.f, 720.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(1260.f, 0.f), Vector2f(20.f, 720.f)));
}

void FasePrimeira::criarGolems() {
    vector<Vector2f>v;
    v.push_back(Vector2f(950.f, 630.f));
    v.push_back(Vector2f(100.f, 430.f));
    v.push_back(Vector2f(140.f, 200.f));
    v.push_back(Vector2f(1150.f, 430.f));
    int i = rand() % 2 + 3;
    while (i--) {
        int j = rand() % v.size();
        criaEntidade(new entidades::personagens::Golem(v[j], jog, Vector2f(1.f, 30.f)));
        v[j] = v.back();
        v.pop_back();
    }
	criaEntidade(new Projetil(Vector2f(120.f, 150.f), 1));
}

void FasePrimeira::criarTeias() {
    vector<Vector2f>v;
    v.push_back(Vector2f(800.f, 650.f));
    v.push_back(Vector2f(250.f, 450.f));
    v.push_back(Vector2f(650.f, 450.f));
    v.push_back(Vector2f(1000.f, 450.f));
    v.push_back(Vector2f(680.f, 230.f));
    int i = rand() % 3 + 3;
    while (i--) {
        int j = rand() % v.size();
        criaEntidade(new entidades::obstaculos::Teia(v[j], Vector2f(60.f, 50.f)));
        v[j] = v.back();
        v.pop_back();
    }
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