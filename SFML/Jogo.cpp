#include "Jogo.hpp"


Jogo::Jogo() :
    pJog1(Vector2f(100.f,630.f), Vector2f(3.f, 100.f)),
    pJog2(Vector2f(100.f, 630.f), Vector2f(3.f, 100.f)),
    fase1(&pJog1, &pJog2),
    fase2(&pJog1, &pJog2)
{
    Ente::setGG(&Gerenciadores::GerenciadorGrafico::getGG());
    estadoAtual = new MenuPrincipalState(this);

}

Jogo::~Jogo() {
}



void Jogo::executar() {
    RenderWindow* window = Gerenciadores::GerenciadorGrafico::getGG().getWindow();
    View cam = View(FloatRect(0.f, 0.f, 1280.f, 720.f));
    window->setView(cam);
  
    while (window && window->isOpen()) {
        if (estadoAtual) {
            estadoAtual->Entrar();
            estadoAtual->handle();
            estadoAtual->Sair();
        }
    }
}

void Jogo::mudarEstado(State * novoEstado) {
    if (estadoAtual) {
        delete estadoAtual;
    }
    estadoAtual = novoEstado;
}




//GETTERS:

entidades::personagens::Mago* Jogo::getMago1() {
    return &pJog1;
}
entidades::personagens::Mago* Jogo::getMago2() {
    return &pJog2;
}

fases::FasePrimeira* Jogo::getFase1() {
    return &fase1;
}

fases::FaseSegunda* Jogo::getFase2() {
    return &fase2;
}