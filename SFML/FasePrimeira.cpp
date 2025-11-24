#include "FasePrimeira.hpp"

using namespace fases;

FasePrimeira::FasePrimeira(entidades::personagens::Mago* pJog1, entidades::personagens::Mago* pJog2):
    Fase(pJog1,pJog2),
    maxGolems(8)
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
    criaEntidade(new entidades::obstaculos::Saida(Vector2f(60.f, 197.f), Vector2f(47.f, 55.f)));
}

void FasePrimeira::criarBlocos() {
    //Tamanho tela: 1280 e 720
    //Padrão de projeto prototype:

    entidades::obstaculos::Bloco molde(Vector2f(0.f,0.f),Vector2f(0.f,0.f));

    criaEntidade(molde.clone(Vector2f(0.f, 500.f), Vector2f(400.f, 40.f)));
    criaEntidade(molde.clone(Vector2f(600.f, 500.f), Vector2f(680.f, 40.f)));
    criaEntidade(molde.clone(Vector2f(0.f, 280.f), Vector2f(760.f, 40.f)));
    criaEntidade(molde.clone(Vector2f(980.f, 0.f), Vector2f(40.f, 350.f)));
    criaEntidade(molde.clone(Vector2f(1020.f, 150.f), Vector2f(80.f, 40.f)));
    criaEntidade(molde.clone(Vector2f(1020.f, 290.f), Vector2f(80.f, 40.f)));
    criaEntidade(molde.clone(Vector2f(0.f, 700.f), Vector2f(1300.f, 60.f)));
    criaEntidade(molde.clone(Vector2f(0.f, 0.f), Vector2f(1280.f, 20.f)));
    criaEntidade(molde.clone(Vector2f(0.f, 0.f), Vector2f(20.f, 720.f)));
    criaEntidade(molde.clone(Vector2f(1260.f, 0.f), Vector2f(20.f, 720.f)));
}

void FasePrimeira::criarGolems() {
    vector<Vector2f>v;
    v.push_back(Vector2f(950.f, 630.f));
    v.push_back(Vector2f(100.f, 430.f));
    v.push_back(Vector2f(140.f, 200.f));
    v.push_back(Vector2f(1150.f, 430.f));
    uniform_int_distribution<int> dist2(0, 1);
    int i = dist2(rng) + 3;
    while (i--) {
        uniform_int_distribution<int> dist2(0, 50);
        int j = dist2(rng) % v.size();
        criaEntidade(new entidades::personagens::Golem(v[j], jog1, Vector2f(1.f, 30.f)));
        v[j] = v.back();
        v.pop_back();
    }

} 

void FasePrimeira::criarSapos() {
    vector<Vector2f>v;
    v.push_back(Vector2f(300.f, 250.f));
    v.push_back(Vector2f(400.f, 250.f));
    v.push_back(Vector2f(200.f, 250.f));
    v.push_back(Vector2f(1090.f, 240.f));

    uniform_int_distribution<int> dist2(0, 1);
    int i = dist2(rng) + 3;
    while (i--) {
        uniform_int_distribution<int> dist2(0, 100);
        int j = dist2(rng) % v.size();
        criaEntidade(new entidades::personagens::Sapo(v[j], jog1, Vector2f(20.f, 70.f)));
        v[j] = v.back();
        v.pop_back();
    }
}

void FasePrimeira::criarTeias() {
    vector<Vector2f>v;
    v.push_back(Vector2f(800.f, 650.f));
    v.push_back(Vector2f(250.f, 450.f));
    v.push_back(Vector2f(650.f, 450.f));
    v.push_back(Vector2f(1000.f, 450.f));
    v.push_back(Vector2f(680.f, 230.f));
    uniform_int_distribution<int> dist2(0, 2);
    int i = dist2(rng) + 3;
 
    while (i--) {
        uniform_int_distribution<int> dist2(0, 50);
        int j = dist2(rng) % v.size();
        criaEntidade(new entidades::obstaculos::Teia(v[j], Vector2f(60.f, 50.f)));
        v[j] = v.back();
        v.pop_back();
    }
}

void FasePrimeira::criarPlataformas() {

    auto* plat1 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(400.f, 588.f), Vector2f(200.f, 20.f), false, 90.f, 5.f)));
    auto* plat2 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(760.f, 380.f), Vector2f(220.f, 20.f), false, 100.f, 5.f)));
    auto* plat3 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(1150.f, 300.f), Vector2f(110.f, 20.f), false, 180.f, 5.f)));

    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(1100.f, 670.f), Vector2f(30.f, 50.f), plat1));
    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(1030.f, 120.f), Vector2f(30.f, 50.f), plat2));
    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(40.f, 470.f), Vector2f(30.f, 50.f), plat3));

    uniform_int_distribution<int> dist(1, 5);
    if (dist(rng) == 1) {
        auto* plat4 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(550.f, 200.f), Vector2f(150.f, 20.f), false, 60.f, 5.f)));
        criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(1030.f, 260.f), Vector2f(30.f, 50.f), plat4));
    }
    

}

void FasePrimeira::carregarPlataforma(int i, bool ativ, float temp) {

    if (i == 1) {
        auto* plat1 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(400.f, 588.f), Vector2f(200.f, 20.f), false, 90.f, 5.f)));
        criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(1100.f, 670.f), Vector2f(30.f, 50.f), plat1));
        if (ativ)
            plat1->setAtiva();
        plat1->setTempo(temp);

    }
    else if (i == 2) {
        auto* plat2 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(760.f, 380.f), Vector2f(220.f, 20.f), false, 100.f, 5.f)));
        criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(1030.f, 120.f), Vector2f(30.f, 50.f), plat2));
        if (ativ)
            plat2->setAtiva();
        plat2->setTempo(temp);
    }
    else if (i == 3) {
        auto* plat3 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(1150.f, 300.f), Vector2f(110.f, 20.f), false, 180.f, 5.f)));
        criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(40.f, 470.f), Vector2f(30.f, 50.f), plat3));
        if (ativ)
            plat3->setAtiva();
        plat3->setTempo(temp);
    }
    else if (i == 4) {
        auto* plat4 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(550.f, 200.f), Vector2f(150.f, 20.f), false, 60.f, 5.f)));
        criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(1030.f, 260.f), Vector2f(30.f, 50.f), plat4));
        if (ativ)
            plat4->setAtiva();
        plat4->setTempo(temp);
    }
}

void FasePrimeira::carregarFundo() {    //OLHAR DPS
    textura = new Texture();
    if (!textura->loadFromFile("Textures/background 3.png")) {
        throw "textura não carregada";
    }
    pSprite = new Sprite(*textura);
    Vector2u tamTextura = textura->getSize();
    float escalaX = 1280.f / tamTextura.x;
    float escalaY = 720.f / tamTextura.y;
    pSprite->setScale(escalaX, escalaY);
}

Vector2f FasePrimeira::getPosicaoInicialJogador() const {
    return Vector2f(100.f, 660.f);
}