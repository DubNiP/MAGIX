#include "Fase.hpp"

Fase::Fase(Jogador* pJog,GerenciadorGrafico* pGG):
    Ente(),
    lista_ents(),
    GG(pGG),
    GC(),
    jog(pJog)
{
    GC.setJog(pJog);
    GC.setWindow(GG->getWindow());
}

Fase::~Fase() {
    lista_ents.limparPreservando(jog);                 //estranho..
    GC.limparObstaculos();
    GC.limparInimigos();
    jog = NULL;
    GG = NULL;
}

void Fase::criarInimigos() {
    Inimigo* in1 = new Inimigo(Vector2f(200.f, 200.f), 0.f);                   //substituir por algo no futuro..
    GC.incluirInimigo(in1);
    lista_ents.incluir(in1);
}

void Fase::criarObstaculo() {
    Obstaculo* obs1 = new Obstaculo(Vector2f(400.f, 300.f), Vector2f(200.f, 40.f), false, 0);     //substituir por algo no futuro..
    GC.incluirObstaculo(obs1);
    lista_ents.incluir(obs1);
}

void Fase::criarCenario() {
    lista_ents.limparPreservando(jog);                                    //estranho..
    GC.limparObstaculos();
    GC.limparInimigos();

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

            GG->desenhaTodos(&lista_ents);
        }
    }
}