#include "Fase.hpp"
#include <random>

using namespace fases;

Fase::Fase(entidades::personagens::Mago* pJog):
    Ente(),
    lista_ents(),
    GC(),
    jog(pJog),
    textFundo(NULL),
    spriteFundo(NULL)
{
    GC.setJog(pJog);
}

Fase::~Fase() {
    GC.limparObstaculos();
    GC.limparInimigos();
    GC.limparProjetis();
    GC.limparBlocos();
    lista_ents.limparPreservando(jog);                 //estranho..
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
    
    uniform_int_distribution<int> dist2(0, 1);
    int i = dist2(rng) + 3;
    while (i--) {
        uniform_int_distribution<int> dist2(0, 50);
        int j = dist2(rng) % v.size();
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
 
    GC.limparObstaculos();
    GC.limparInimigos();
    GC.limparProjetis();
    GC.limparBlocos();
    lista_ents.limparPreservando(jog);                                    //estranho..

    carregarFundo();

    if (jog) {
        jog->getConcluiuFase() ? jog->reseta(Vector2f(160.f, 1110.f), 15, 0) : jog->reseta(Vector2f(160.f, 630.f), 15, 0);
       
		jog->setFaseAtual(this);
        lista_ents.incluir(jog);
        Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMago(jog);
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
        else if (auto* prj = dynamic_cast<entidades::Projetil*>(e)) {
            GC.incluirProjetil(prj);
        }
        else if (auto* bloco = dynamic_cast<entidades::obstaculos::Bloco*>(e)) { 
            GC.incluirBloco(bloco);
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
            pGG->atualizarCamera(jog->getPos());
		    View cam = pGG->getCamera();

            window->setView(cam);
            
            while (window->pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window->close();
                    return;
                }

                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                    return;
                }
            }

            Gerenciador::GerenciadorEvento::getGerenciadorEvento()->executar();
            lista_ents.executarTodos();

            GC.executar();

            pGG->desenhaTodos(&lista_ents,spriteFundo);     //trocar no futuro?
        }
        jog->setConcluiuFase(GC.getFaseConcluida());
    }
}

void Fase::criarProjetil(Vector2f pos, bool dir, bool bond) {
    criaEntidade(new entidades::Projetil(pos, dir, bond));
}
