#include "Gerenciador_Eventos.hpp"

namespace Gerenciador {

    GerenciadorEvento* GerenciadorEvento::pEvento = NULL;

    GerenciadorEvento::GerenciadorEvento() :
        pMago(NULL),
        pMenu(NULL),
        prevUp(false),
        prevDown(false),
        prevEnter(false)
    {
    }

    GerenciadorEvento::~GerenciadorEvento() {
        pMago = NULL;
        pMenu = NULL;
    }

    GerenciadorEvento* GerenciadorEvento::getGerenciadorEvento() {
        if (!pEvento) {
            pEvento = new GerenciadorEvento();
        }
        return pEvento;
    }

    void GerenciadorEvento::setMago(entidades::personagens::Mago* pj) {
        pMago = pj;
    }

    void GerenciadorEvento::setMenu(Menu* pm) {
        pMenu = pm;
        // reset estados para não herdar teclas já seguradas
        prevUp = prevDown = prevEnter = false;
    }

    void GerenciadorEvento::executar() {
        if (pMago) {

           bool moverEsq = Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left);
           bool moverDir = Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right);
           bool pular = Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up);
           bool atirar = Keyboard::isKeyPressed(Keyboard::Space);

            pMago->processarInput(moverEsq, moverDir, pular, atirar);
        }
    }

    void GerenciadorEvento::executarMenu() {
        if (!pMenu) return;

        bool down = Keyboard::isKeyPressed(Keyboard::Down);
        bool up = Keyboard::isKeyPressed(Keyboard::Up);
        bool enter = Keyboard::isKeyPressed(Keyboard::Enter);

        if (down && !prevDown) {
            pMenu->moverBaixo();
        }
        if (up && !prevUp) {
            pMenu->moverCima();
        }
        if (enter && !prevEnter) {
            pMenu->confirmar();
        }


        prevDown  = down;
        prevUp    = up;
        prevEnter = enter;
    }

}