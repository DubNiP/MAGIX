#include "Fase.hpp"

Fase::Fase(Jogador* pJog,GerenciadorGrafico* pGG):
    GG(pGG),
    jog(pJog)
{
    GC.setJog(pJog);
    GC.setWindow(GG->getWindow());
}

Fase::~Fase() {
    GC.limparObstaculos();
    jog = NULL;
    GG = NULL;
}

void Fase::criarCenario() {
    //deve ter criar inimigos,plataformas, etc...
    if (jog) {
        jog->reseta(Vector2f(640.f, 360.f), 10, 0);
    }
    criarObstaculo();
}

void Fase::criarObstaculo() {
    Obstaculo* obs1 = new Obstaculo(Vector2f(400.f, 300.f), Vector2f(200.f, 40.f), false, 0);
    GC.incluirObstaculo(obs1);
}

void Fase::executar() {
    criarCenario();
    if (GG) {
        RenderWindow* window = GG->getWindow();
        Event event;
        while (window && window->isOpen()) {
            while (window->pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window->close();
                    return;
                }

                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                    return;
                }
            }

            GG->clearWindow(Color::Black);
            if (jog) {
                jog->executar();
            }
            GC.limiteDeTela();
            if (jog) {
                jog->draw(window);             //desenhar deve ser no GG
            }
            GC.executar();
            if (GG) {
                GG->displayWindow();
            }
        }
    }
}