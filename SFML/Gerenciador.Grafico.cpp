#include "Gerenciador.Grafico.hpp"
#include "Menu.hpp"


GerenciadorGrafico::GerenciadorGrafico() {
    
    window = new RenderWindow(VideoMode(1280, 720), "Jogo Simas");
    window->setFramerateLimit(60);
    window->setPosition(Vector2i(0, 0));
}


GerenciadorGrafico::~GerenciadorGrafico() {
    if (window) {
        delete window;
    }
}


void GerenciadorGrafico::clearWindow(Color cor) {
    window->clear(cor);

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
