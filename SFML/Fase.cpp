#include "Fase.hpp"

Fase::Fase(Jogador* pJog):
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
        jog->reseta(Vector2f(640.f, 360.f), 10, 0);
        lista_ents.incluir(jog);
    }
    criarObstaculo();
    criarInimigos();
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