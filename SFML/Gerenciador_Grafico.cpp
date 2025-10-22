#include "Gerenciador_Grafico.hpp"



GerenciadorGrafico::GerenciadorGrafico():
    window(NULL)
{
    
    window = new RenderWindow(VideoMode(1280, 720), "Jogo Simas");
    if (window) {
        window->setFramerateLimit(60);
        window->setPosition(Vector2i(0, 0));
    }
}


GerenciadorGrafico::~GerenciadorGrafico() {
    if (window) {
        delete window;
    }
}

//desenharEnte();

void GerenciadorGrafico::clearWindow(Color cor) {
    if (window) {
        window->clear(cor);
    }
}

void GerenciadorGrafico::drawWindow(const Drawable& corpo) {
    if (window) {
        window->draw(corpo);
    }
}

void GerenciadorGrafico::displayWindow() {
    if (window) {
        window->display();
    }
}

RenderWindow* GerenciadorGrafico::getWindow() const {
    return window;
}
