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

    void GerenciadorEvento::soltaTeclas() {
        while (true) {
            bool algumaTeclaApertada =
                Keyboard::isKeyPressed(Keyboard::Up) ||
                Keyboard::isKeyPressed(Keyboard::W) ||
                Keyboard::isKeyPressed(Keyboard::Down) ||
                Keyboard::isKeyPressed(Keyboard::S) ||
                Keyboard::isKeyPressed(Keyboard::Enter) ||
                Keyboard::isKeyPressed(Keyboard::Space) ||
                Keyboard::isKeyPressed(Keyboard::Escape);

            if (!algumaTeclaApertada) {
                break;
            }
        }
        prevUp = prevDown = prevEnter = false;
    }


    bool GerenciadorEvento::verificarEventosJanela(sf::RenderWindow* window) {
        if (window) {
            Event event;
            while (window->pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window->close();
                    return false; 
                }
            }
            return true;
        }
    }
}




