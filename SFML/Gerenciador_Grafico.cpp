#include "Gerenciador_Grafico.hpp"
#include "ListaEntidades.hpp"


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

void GerenciadorGrafico::desenharEnte(const Drawable &shape) {
    if (window) {
        window->draw(shape);
    }
}

void GerenciadorGrafico::clearWindow(Color cor) {
    if (window) {
        window->clear(cor);
    }
}

void GerenciadorGrafico::displayWindow() {
    if (window) {
        window->display();
    }
}

void GerenciadorGrafico::desenhaTodos(ListaEntidades *pLE, Color cor) {
    if (window) {
        clearWindow(cor);
        if (pLE) {
            pLE->desenharTodos();
        }
        displayWindow();
    }
}

RenderWindow* GerenciadorGrafico::getWindow() const {
    return window;
}
