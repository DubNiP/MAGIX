#include "Jogo.hpp"

/*Seguinte, a parte de desenhar está sendo feita aqui, mas ela deve ser feita no GG,
         para arrumar isso, teremos a classe Ente e a lista de entidades,
         o que faremos é que o menu será derivado de ente, e através de uma
         função estática, setaremos o GG de ente, assim, percorreremos a lista
         de entidades e desenharemos elas no GG.                                */



Jogo::Jogo() :
    pJog1(Vector2f(640,360), 50.0f),
    GG(),
    menu(),
    event(),
    fase1(&pJog1,&GG)
{
}

Jogo::~Jogo() {
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
    fase1.executar();
}