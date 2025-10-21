#include "Jogo.hpp"
#include "Menu.hpp"

Jogo::Jogo() :
    GG()
{
}

Jogo::~Jogo() {
}

void Jogo::executar() {
    Menu menu;

    while (GG.getWindow()->isOpen()) {
        executarMenu(menu);


        if (menu.getIniciar() && GG.getWindow()->isOpen()) {
            menu.reseta();
            executarJogo();
        }

        
        if (menu.getSair()) {
            GG.getWindow()->close();
        }
    }
}

void Jogo::executarMenu(Menu& menu) {
    Event event;

    while (GG.getWindow()->isOpen() && !menu.getIniciar() && !menu.getSair()) {
        while (GG.getWindow()->pollEvent(event)) {
            menu.loop_menu(event);
        }
        menu.draw_menu(GG.getWindow());
    }
}

void Jogo::executarJogo() {
    Event event;
    Font fonte;
    Text texto;

    if (fonte.loadFromFile("Fonts/Newsreader-VariableFont_opsz,wght.ttf")) {
        texto.setFont(fonte);
    }
    texto.setString("TELA DO JOGO\n\nPressione ESC para voltar ao menu");
    texto.setCharacterSize(50);
    texto.setFillColor(Color::White);
    texto.setPosition(350, 300);

    while (GG.getWindow()->isOpen()) {
        while (GG.getWindow()->pollEvent(event)) {
            if (event.type == Event::Closed) {
                GG.getWindow()->close();
                return;
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                return;
            }
        }
        GG.clearWindow(Color::Blue);
        GG.drawWindow(texto);
        GG.displayWindow();
    }
}