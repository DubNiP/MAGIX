#include "Fase.hpp"

Fase::Fase(Jogador* pJog,GerenciadorGrafico* pGG):
    Ente(),
    lista_ents(),
    GG(pGG),
    GC(),
    jog(pJog),
    textFundo(NULL),
    spriteFundo(NULL)
{
    GC.setJog(pJog);
    GC.setWindow(GG->getWindow());
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
    GG = NULL;
}

void Fase::criarProjetil()                                                       //COMENTAR COM O RAFA
{
    Projetil* pProjetil = new Projetil(Vector2f(1000.f, 360.f), false);
    GC.incluirProjetil(pProjetil);
    lista_ents.incluir(pProjetil);
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
    criarProjetil(); //adicionar de forma que seja enviado pelo chefão
}

void Fase::executar() {
    criarCenario();
    if (GG) {
        RenderWindow* window = GG->getWindow();
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
            GC.limiteDeTela();
            GC.executar();

            GG->desenhaTodos(&lista_ents,spriteFundo);
        }
    }
}