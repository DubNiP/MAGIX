#include "Gerenciador_Eventos.hpp"

namespace Gerenciador {

    GerenciadorEvento* GerenciadorEvento::pEvento = NULL;

    GerenciadorEvento::GerenciadorEvento() :
        subject(),
        pMago(NULL),
        prevUp(false),
        prevDown(false),
        prevEnter(false),
        eventQueue()
    {
    }

    GerenciadorEvento::~GerenciadorEvento() {
        pMago = NULL;
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

        bool down = Keyboard::isKeyPressed(Keyboard::Down);
        bool up = Keyboard::isKeyPressed(Keyboard::Up);
        bool enter = Keyboard::isKeyPressed(Keyboard::Enter);

        if (down && !prevDown) {
            notify(1);
        }
        if (up && !prevUp) {
            notify(2);
        }
        if (enter && !prevEnter) {
            notify(3);
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


    bool GerenciadorEvento::verificarEventosJanela(RenderWindow* window) {
        if (window) {
            Event event;
            eventQueue.clear();
            while (window->pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window->close();
                    return false;
                }
                // armazenar todos os eventos para consumo por estados
                eventQueue.push_back(event);
            }
            return true;
        }
        return false;
    }

    bool GerenciadorEvento::temEvento() const {
        return !eventQueue.empty();
    }

    bool GerenciadorEvento::proximoEvento(Event& out) {
        if (eventQueue.empty()) return false;
        out = eventQueue.front();
        eventQueue.pop_front();
        return true;
    }
}




