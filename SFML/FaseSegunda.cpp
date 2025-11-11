#include "FaseSegunda.hpp"
#include "MagoNegro.hpp"
#include "Bloco.hpp"
#include "Saida.hpp"
#include "Plataforma.hpp"
#include "Alavanca.hpp"
#include "Teia.hpp"
#include "Mago.hpp"

using namespace fases;

FaseSegunda::FaseSegunda(entidades::personagens::Mago* pJog) :
    Fase(pJog),
    maxChefoes(1)
{
}

FaseSegunda::~FaseSegunda() {
}

void FaseSegunda::criarInimigos() {
    criarChefoes();
    // Adicionar alguns inimigos 
    vector<Vector2f> posicoesInimigos;
    posicoesInimigos.push_back(Vector2f(300.f, 550.f));
    posicoesInimigos.push_back(Vector2f(600.f, 350.f));
    posicoesInimigos.push_back(Vector2f(900.f, 200.f));

   
}

void FaseSegunda::criarObstaculo() {

    criarObstaculosMedios();

}

void FaseSegunda::criarChefoes() {
    entidades::personagens::MagoNegro* pM = new entidades::personagens::MagoNegro(Vector2f(900.f, 200.f), jog, Vector2f(3.f, 50.f));
    criaEntidade(pM);
    pM->incluirGerenciadorColisoes(&GC);
    pM->incluirListaEntidades(&lista_ents);
}


void FaseSegunda::criarObstaculosMedios() {

    auto* plat1 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(1120.f, 810.f), Vector2f(140.f, 20.f), false, 90.f, 10.f)));
    auto* plat2 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(1120.f, 630.f), Vector2f(140.f, 20.f), false, 90.f, 10.f)));
    auto* plat3 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(20.f, 350.f), Vector2f(100.f, 20.f), false, 90.f, 10.f)));
    auto* plat4 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(1120.f, 950.f), Vector2f(140.f, 20.f), false, 90.f, 10.f)));

    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(300.f, 870.f), Vector2f(30.f, 40.f), plat1));
    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(300.f, 690.f), Vector2f(30.f, 40.f), plat2));
    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(300.f, 1030.f), Vector2f(30.f, 40.f), plat3));
    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(350.f, 1030.f), Vector2f(30.f, 40.f), plat4));
    
}


void FaseSegunda::criarBlocos() {

    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 1060.f), Vector2f(1280.f, 20.f))); // chão
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 0.f), Vector2f(1280.f, 20.f))); // teto
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(0.f, 0.f), Vector2f(20.f, 1060.f)));  // parede esquerda
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(1260.f, 0.f), Vector2f(20.f, 1060.f)));  // parede direita



    // Bloco vertical grande na esquerda
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(280.f, 540.f), Vector2f(20.f, 520.f)));

    //Escadaria 
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(20.f, 1000.f), Vector2f(100.f, 20.f)));
	criaEntidade(new entidades::obstaculos::Bloco(Vector2f(180.f, 900.f), Vector2f(940.f, 20.f)));
	criaEntidade(new entidades::obstaculos::Bloco(Vector2f(20.f, 810.f), Vector2f(100.f, 20.f)));
	criaEntidade(new entidades::obstaculos::Bloco(Vector2f(180.f, 720.f), Vector2f(940.f, 20.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(20.f, 640.f), Vector2f(100.f, 20.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(200.f, 540.f), Vector2f(110.f, 20.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(280.f, 540.f), Vector2f(840.f, 20.f)));
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(20.f, 460.f), Vector2f(120.f, 20.f)));

    //Hall do mago negro
    criaEntidade(new entidades::obstaculos::Bloco(Vector2f(120.f, 320.f), Vector2f(1160.f, 20.f)));
	criaEntidade(new entidades::obstaculos::Bloco(Vector2f(120.f, 270.f), Vector2f(20.f, 50.f)));
}


void FaseSegunda::carregarFundo() {
    textFundo = new Texture();

    if (!textFundo->loadFromFile("Textures/background 2.png")) {
        throw "textura não carregada";
    }

    spriteFundo = new Sprite(*textFundo);

    Vector2u tam = textFundo->getSize();
    float escX = 1280.f / tam.x;
    float escY = 1080.f / tam.y;

    spriteFundo->setScale(escX, escY);
}