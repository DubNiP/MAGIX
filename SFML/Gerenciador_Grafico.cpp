#include "Gerenciador_Grafico.hpp"
#include "ListaEntidades.hpp"
#include "Fase.hpp"

using namespace Gerenciadores;
using namespace listas;
using namespace fases;
using namespace std;

GerenciadorGrafico* GerenciadorGrafico::pGrafico = NULL;

GerenciadorGrafico::GerenciadorGrafico() :
    window(NULL),
	segundaTela(false),
    camera(View(FloatRect(0.f, 0.f, 1280.f, 720.f)))
{
    window = new RenderWindow(VideoMode(1280, 720), "MAGIX");
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

GerenciadorGrafico& GerenciadorGrafico::getGG() {
    if (!pGrafico) {
        pGrafico = new GerenciadorGrafico();            // Padrão de projeto Singleton.
    }
    return *pGrafico;
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

    float maxX = 1280.f;
    float maxY = segundaTela ? 1280.f : 720.f;

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

void GerenciadorGrafico::resetarCamera() {
    camera = View(FloatRect(0.f, 0.f, 1280.f, 720.f));
    if (window) {
        window->setView(camera);
    }
}

void GerenciadorGrafico::setSegundaTela(bool val) {
    segundaTela = val;
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
