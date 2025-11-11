#include "Gerenciador_Grafico.hpp"
#include "ListaEntidades.hpp"

using namespace Gerenciadores;
using namespace listas;
using namespace std;

GerenciadorGrafico* GerenciadorGrafico::uniqueInstance = NULL;

GerenciadorGrafico::GerenciadorGrafico() :
    window(NULL),
    camera(View(FloatRect(0.f, 0.f, 1280.f, 720.f)))
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

GerenciadorGrafico& GerenciadorGrafico::Instance() {
    static once_flag flag;
    call_once(flag, []() {
        uniqueInstance = new GerenciadorGrafico();
        });
    return *uniqueInstance;
}

void GerenciadorGrafico::desenharEnte(const Drawable& shape) {
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

void GerenciadorGrafico::atualizarCamera(const Vector2f posMago) {
    const float visaoE = camera.getSize().x;
    const float visaoD = camera.getSize().y;

    const float maxX = window->getSize().x;
    const float maxY = 1080;

    Vector2f centro = posMago;

    if (centro.x < visaoE / 2.f)
        centro.x = visaoE / 2.f;

    if (centro.x > maxX - visaoE / 2.f)
        centro.x = maxX - visaoE / 2.f;

    if (centro.y < visaoD / 2.f)
        centro.y = visaoD / 2.f;

    if (centro.y > maxY - visaoD / 2.f)
        centro.y = maxY - visaoD / 2.f;

    camera.setCenter(centro);
}


void GerenciadorGrafico::desenhaTodos(listas::ListaEntidades* pLE, Sprite* fundo) {
    if (window) {
        clearWindow();
        if (fundo) {
            window->draw(*fundo);
        }
        if (pLE) {
            pLE->desenharTodos();
        }
        displayWindow();
    }
}

RenderWindow* GerenciadorGrafico::getWindow() const {
    return window;
}

View GerenciadorGrafico::getCamera() const {
    return camera;
}
