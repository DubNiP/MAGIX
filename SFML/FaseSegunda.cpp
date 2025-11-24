#include "FaseSegunda.hpp"
#include "MagoNegro.hpp"
#include "Bloco.hpp"
#include "Saida.hpp"
#include "Plataforma.hpp"
#include "Alavanca.hpp"
#include "Teia.hpp"
#include "Mago.hpp"

using namespace fases;

FaseSegunda::FaseSegunda(entidades::personagens::Mago* pJog, entidades::personagens::Mago* pJog2) :
    Fase(pJog,pJog2),
    maxChefoes(5)
{
}


FaseSegunda::~FaseSegunda() {
}

void FaseSegunda::criarInimigos() {
    criarChefoes();
    criarSapos();
   
}

void FaseSegunda::criarSapos() {
    vector<Vector2f> posicoesInimigos;
    posicoesInimigos.push_back(Vector2f(660.f, 1200.f));
    posicoesInimigos.push_back(Vector2f(660.f, 1030.f));
    posicoesInimigos.push_back(Vector2f(660.f, 800.f));

    uniform_int_distribution<int> dist2(0, 2);

    for (int i = 0; i < 3; i++) {
        int idx = dist2(rng);
        criaEntidade(new entidades::personagens::Sapo(posicoesInimigos[idx], jog1, Vector2f(20.f, 70.f)));
    }
}

void FaseSegunda::criarObstaculo() {
    criarEspinho();

    criaEntidade(new entidades::obstaculos::Espinho(Vector2f(600.f, 1250.f), Vector2f(40.f, 10.f), 1));
    criaEntidade(new entidades::obstaculos::Espinho(Vector2f(40.f, 980.f), Vector2f(40.f, 10.f), 1));
    criaEntidade(new entidades::obstaculos::Espinho(Vector2f(40.f, 790.f), Vector2f(40.f, 10.f), 1));

    auto* plat1 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(20.f, 470.f), Vector2f(100.f, 20.f), false, 90.f, 10.f)));
    auto* plat2 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(1120.f, 790.f), Vector2f(140.f, 20.f), false, 90.f, 10.f)));
    auto* plat3 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(1120.f, 970.f), Vector2f(140.f, 20.f), false, 90.f, 10.f)));
    auto* plat4 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(1120.f, 1150.f), Vector2f(140.f, 20.f), false, 90.f, 10.f)));


    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(300.f, 1230.f), Vector2f(30.f, 40.f), plat1));
    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(300.f, 850.f), Vector2f(30.f, 40.f), plat2));
    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(300.f, 1030.f), Vector2f(30.f, 40.f), plat3));
    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(350.f, 1230.f), Vector2f(30.f, 40.f), plat4));

}

void FaseSegunda::criarPlataformas() {

    auto* plat1 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(20.f, 470.f), Vector2f(100.f, 20.f), false, 90.f, 10.f)));
    auto* plat2 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(1120.f, 790.f), Vector2f(140.f, 20.f), false, 90.f, 10.f)));
    auto* plat3 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(1120.f, 970.f), Vector2f(140.f, 20.f), false, 90.f, 10.f)));
    auto* plat4 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(1120.f, 1150.f), Vector2f(140.f, 20.f), false, 90.f, 10.f)));


    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(300.f, 1230.f), Vector2f(30.f, 40.f), plat1));
    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(300.f, 850.f), Vector2f(30.f, 40.f), plat2));
    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(300.f, 1030.f), Vector2f(30.f, 40.f), plat3));
    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(350.f, 1230.f), Vector2f(30.f, 40.f), plat4));

}

void FaseSegunda::carregarPlataforma(int i, bool ativ, float temp) {

    if (i == 1) {
        auto* plat1 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(20.f, 470.f), Vector2f(100.f, 20.f), false, 90.f, 10.f)));
        criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(300.f, 1230.f), Vector2f(30.f, 40.f), plat1));
        if (ativ)
            plat1->setAtiva();
        plat1->setTempo(temp);
	
    }
    else if (i == 2) {
        auto* plat2 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(1120.f, 790.f), Vector2f(140.f, 20.f), false, 90.f, 10.f)));
        criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(300.f, 850.f), Vector2f(30.f, 40.f), plat2));
        if(ativ)
			plat2->setAtiva();
        plat2->setTempo(temp);
    }
    else if (i == 3) {
        auto* plat3 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(1120.f, 970.f), Vector2f(140.f, 20.f), false, 90.f, 10.f)));
        criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(300.f, 1030.f), Vector2f(30.f, 40.f), plat3));
        if(ativ)
			plat3->setAtiva();
        plat3->setTempo(temp);
    }
    else if (i == 4) {
        auto* plat4 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(1120.f, 1150.f), Vector2f(140.f, 20.f), false, 90.f, 10.f)));
        criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(350.f, 1230.f), Vector2f(30.f, 40.f), plat4));
        if(ativ)
			plat4->setAtiva();
        plat4->setTempo(temp);
    }
}

void FaseSegunda::criarEspinho() {
    uniform_int_distribution<int> distDano(1, 3);

    criaEntidade(new entidades::obstaculos::Espinho(Vector2f(600.f, 1250.f), Vector2f(40.f, 10.f), distDano(rng)));
    criaEntidade(new entidades::obstaculos::Espinho(Vector2f(40.f, 980.f), Vector2f(40.f, 10.f), distDano(rng)));
    criaEntidade(new entidades::obstaculos::Espinho(Vector2f(40.f, 790.f), Vector2f(40.f, 10.f), distDano(rng)));
}

void FaseSegunda::criarChefoes() {

    vector<Vector2f> posicoesInimigos;
    posicoesInimigos.push_back(Vector2f(900.f, 200.f));
    posicoesInimigos.push_back(Vector2f(1180.f, 1200.f));
    posicoesInimigos.push_back(Vector2f(1000.f, 200.f));

    entidades::personagens::MagoNegro* pM = new entidades::personagens::MagoNegro(posicoesInimigos[0], jog1, Vector2f(3.f, -60.f));
    criaEntidade(pM);
    pM->setFaseAtual(this);

    uniform_int_distribution<int> dist2(0, 2);

    for (int i = 0; i < maxChefoes-1; i++) {
		int idx = dist2(rng);
        entidades::personagens::MagoNegro* pM = new entidades::personagens::MagoNegro(posicoesInimigos[idx], jog1, Vector2f(3.f, -60.f));
        criaEntidade(pM);
        pM->setFaseAtual(this);
    }
}


void FaseSegunda::criarBlocos() {
    //Padrão de projeto Prototype:
    entidades::obstaculos::Bloco molde(Vector2f(0.f, 0.f), Vector2f(0.f, 0.f));

    criaEntidade(molde.clone(Vector2f(0.f, 1260.f), Vector2f(1280.f, 20.f))); // chão
    criaEntidade(molde.clone(Vector2f(0.f, 0.f), Vector2f(1280.f, 20.f))); // teto
    criaEntidade(molde.clone(Vector2f(0.f, 0.f), Vector2f(20.f, 1260.f)));  // parede esquerda
    criaEntidade(molde.clone(Vector2f(1260.f, 0.f), Vector2f(20.f, 1260.f)));  // parede direita

    // Bloco vertical 
    criaEntidade(molde.clone(Vector2f(280.f, 720.f), Vector2f(20.f, 540.f)));

    //Escadaria 
    criaEntidade(molde.clone(Vector2f(20.f, 1170.f), Vector2f(100.f, 20.f)));
	criaEntidade(molde.clone(Vector2f(180.f, 1060.f), Vector2f(940.f, 20.f)));
	criaEntidade(molde.clone(Vector2f(20.f, 990.f), Vector2f(100.f, 20.f)));
	criaEntidade(molde.clone(Vector2f(180.f, 880.f), Vector2f(940.f, 20.f)));
    criaEntidade(molde.clone(Vector2f(20.f, 800.f), Vector2f(100.f, 20.f)));
    criaEntidade(molde.clone(Vector2f(200.f, 700.f), Vector2f(920.f, 20.f)));
    criaEntidade(molde.clone(Vector2f(20.f, 580.f), Vector2f(140.f, 20.f)));

   
    // Hall do Mago Negro
    criaEntidade(molde.clone(Vector2f(120.f, 440.f), Vector2f(1140.f, 20.f)));
    criaEntidade(molde.clone(Vector2f(120.f, 380.f), Vector2f(40.f, 80.f)));

}


void FaseSegunda::carregarFundo() {
    textura = new Texture();
    if (!textura->loadFromFile("Textures/background 2.png")) {
        throw "textura não carregada";
    }

    pSprite = new Sprite(*textura);

    Vector2u tam = textura->getSize();
    float escX = 1280.f / tam.x;
    float escY = 1280.f / tam.y;

    pSprite->setScale(escX, escY);
}

Vector2f FaseSegunda::getPosicaoInicialJogador() const {
    return Vector2f(150.f, 1200.f);
}