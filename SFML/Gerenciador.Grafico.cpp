#include "Gerenciador.Grafico.hpp"
#include "Menu.hpp"

GerenciadorGrafico* GerenciadorGrafico::instancia = NULL;

GerenciadorGrafico* GerenciadorGrafico::getInstancia() {
    if (instancia == NULL) {
        instancia = new GerenciadorGrafico();
    }
    return instancia;
}


GerenciadorGrafico::GerenciadorGrafico() {
    
    window = new RenderWindow(VideoMode(1280, 720), "Jogo Simas");
    window->setFramerateLimit(60);
    window->setPosition(Vector2i(0, 0));
}


GerenciadorGrafico::~GerenciadorGrafico() {
    if (window) {
        delete window;
    }
    if (instancia) {
        delete instancia;
    }
}


void GerenciadorGrafico::clearWindow() {
    window->clear();

}

void GerenciadorGrafico::drawWindow(const Drawable& corpo) {
    window->draw(corpo);
}

void GerenciadorGrafico::displayWindow() {
    window->display();
}

RenderWindow* GerenciadorGrafico::getWindow() {
    return window;
}

void GerenciadorGrafico::executar() {
    Menu menu;
    menu.executar();
}