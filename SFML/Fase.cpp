#include "Fase.hpp"

using namespace fases;

Fase::Fase(entidades::personagens::Jogador* pJog):
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

void Fase::criarCenario() {
    lista_ents.limparPreservando(jog);                                    //estranho..
    GC.limparObstaculos();
    GC.limparInimigos();
    GC.limparProjetis();

    carregarFundo();

    //deve ter criar plataformas, etc...
    if (jog) {
        jog->reseta(Vector2f(640.f, 240.f), 10, 0);
        lista_ents.incluir(jog);
    }
    criarObstaculo();
    criarInimigos();
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
}

void Fase::executar() {
    criarCenario();
    if (pGG) {
        GC.setWindow(pGG->getWindow());
        RenderWindow* window = pGG->getWindow();
        Event event;
        while (window && window->isOpen() && jog && jog->getVidas() > 0) {
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

            pGG->desenhaTodos(&lista_ents,spriteFundo);     //talvez trocar no futuro
        }
    }
}