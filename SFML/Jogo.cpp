#include "Jogo.hpp"

Jogo::Jogo() :
    pJog1(NULL),
    GG(),
    GC(),
    menu(),
    event()
{
}

Jogo::~Jogo() {
    if (pJog1) {
        delete pJog1;
    }
}

void Jogo::executar() {
    RenderWindow* window = GG.getWindow();
    while (window && window->isOpen()) {
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
        menu.draw_menu(window);
    }
}

void Jogo::executarJogo() {
    if (pJog1) {
        delete pJog1;
    }
    pJog1 = new Jogador(Vector2f(640,360));

    RenderWindow* window = GG.getWindow();

    GC.setJog(pJog1);
    GC.setWindow(window);

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
        if (pJog1) {
            pJog1->executar();
            pJog1->limitarMovimento(window->getSize());
        }
        GC.executar();
        GG.clearWindow(Color::Blue);
        if (pJog1) {                                     //talvez desnecessarias... perguntar
            pJog1->draw(window);            
        }
        GG.displayWindow();
    }
}