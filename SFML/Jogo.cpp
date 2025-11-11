#include "Jogo.hpp"


Jogo::Jogo() :
    pJog1(Vector2f(100.f,630.f), Vector2f(3.f, 100.f)),
    GG(Gerenciadores::GerenciadorGrafico::Instance()),
    menu(),
    event(),
    fase1(&pJog1),
    fase2(&pJog1)
{
    Ente::setGG(&GG);         //pode mudar
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMenu(&menu);
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
            Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMenu(NULL);
            Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMago(&pJog1);
            executarJogo();
            Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMago(NULL);
            Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMenu(&menu);
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
            if (event.type == Event::Closed) { 
                window->close(); return; 
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                menu.reseta();
            }
        }
        Gerenciador::GerenciadorEvento::getGerenciadorEvento()->executarMenu();
        menu.draw_menu();
    }
}

void Jogo::executarJogo() {
    //fase1.executar();
    fase2.executar();
}