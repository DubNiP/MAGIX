#include "Fase.hpp"

using namespace fases;

Fase::Fase(entidades::personagens::Jogador* pJog):
    Ente(),
    lista_ents(),
    GC(),
    jog(pJog),
    faseConcluida(false),
    textFundo(NULL),
    spriteFundo(NULL)
{
    GC.setJog(pJog);
}

Fase::~Fase() {
    lista_ents.limparPreservando(jog);                 //estranho..
    GC.limparObstaculos();
    GC.limparInimigos();
    GC.limparProjetis();
    if (spriteFundo) {
        delete spriteFundo;
        spriteFundo = NULL;
    }
    if (textFundo) {
        delete textFundo;
        textFundo = NULL;
    }

    jog = NULL;
}

void Fase::criarSapos() {
    vector<Vector2f>v;
    v.push_back(Vector2f(300.f, 250.f));
    v.push_back(Vector2f(400.f, 250.f));
    v.push_back(Vector2f(200.f, 250.f));
    v.push_back(Vector2f(1190.f, 180.f));
    int i = rand() % 2 + 3;
    while (i--) {
        int j = rand() % v.size();
        criaEntidade(new entidades::personagens::Sapo(v[j], jog, Vector2f(20.f, 70.f)));
        v[j] = v.back();
        v.pop_back();
    }
}

void Fase::criarPlataformas() {

    auto* plat1 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(400.f, 588.f), Vector2f(200.f, 20.f), false, 90.f, 5.f)));
    auto* plat2 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(760.f, 380.f), Vector2f(220.f, 20.f), false, 100.f, 5.f)));

    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(1100.f, 670.f), Vector2f(30.f, 50.f), plat1));
    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(1030.f, 120.f), Vector2f(30.f, 50.f), plat2));
}

void Fase::criarCenario() {
    lista_ents.limparPreservando(jog);                                    //estranho..
    GC.limparObstaculos();
    GC.limparInimigos();
    GC.limparProjetis();

    carregarFundo();

    if (jog) {
        jog->reseta(Vector2f(100.f, 630.f), 10, 0);
        lista_ents.incluir(jog);
    }
    criarObstaculo();
    criarInimigos();
    criarBlocos();
}

Entidade* Fase::criaEntidade(Entidade* e) {
    if (e) {

        lista_ents.incluir(e);

        if (auto* ob = dynamic_cast<entidades::obstaculos::Obstaculo*>(e)) {
            GC.incluirObstaculo(ob);
        }
        else if (auto* ini = dynamic_cast<entidades::personagens::Inimigo*>(e)) {
            GC.incluirInimigo(ini);
        }
        else if (auto* prj = dynamic_cast<Projetil*>(e)) {       //else?
            GC.incluirProjetil(prj);
        }

        return e;
    }
    return NULL;
}

void Fase::executar() {
    criarCenario();
    if (pGG) {
        GC.setWindow(pGG->getWindow());
        RenderWindow* window = pGG->getWindow();
        Event event;
        while (window && window->isOpen() && jog && jog->getVidas() > 0 && !GC.getFaseConcluida()) {
            while (window->pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window->close();
                    return;
                }

                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                    return;
                }
            }
            lista_ents.executarTodos();
            GC.executar();

            pGG->desenhaTodos(&lista_ents,spriteFundo);     //trocar no futuro?
        }
    }
}