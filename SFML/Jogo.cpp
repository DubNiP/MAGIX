#include "Jogo.hpp"


Jogo::Jogo() :
    pJog1(Vector2f(100.f,630.f), Vector2f(3.f, 100.f)),
    GG(Gerenciadores::GerenciadorGrafico::Instance()),
    menu(),
    event(),
    fase1(&pJog1)
{
    Ente::setGG(&GG);         //pode mudar
}

Jogo::~Jogo() {
}

void Jogo::executar() {
    RenderWindow* window = GG.getWindow();
  
    while (window && window->isOpen()) {
		View cam = View(FloatRect(0.f, 0.f, 1280.f, 720.f));
		window->setView(cam);
        executarMenu(menu);

        if (menu.getIniciar() && window->isOpen()) {
            menu.reseta();
            executarJogo();
        }


        if (menu.getSair()) {
            window->close();
        }
    }
}

void Jogo::executarMenu(Menu& menu) {
    RenderWindow* window = GG.getWindow();

    while (window && window->isOpen() && !menu.getIniciar() && !menu.getSair()) {
        while (window->pollEvent(event)) {
            menu.loop_menu(event);
        }
        menu.draw_menu();
    }
}

void Jogo::executarJogo() {
    fase1.executar();
}