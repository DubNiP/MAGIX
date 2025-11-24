#include "Gerenciador_Eventos.hpp"

namespace Gerenciador {

    GerenciadorEvento* GerenciadorEvento::pEvento = NULL;

    GerenciadorEvento::GerenciadorEvento() :
        subject(),
        pMago1(NULL),
        pMago2(NULL),
        prevUp(false),
        prevDown(false),
        prevEnter(false),
        eventQueue()
    {
    }

    GerenciadorEvento::~GerenciadorEvento() {
        pMago1 = NULL;
        pMago2 = NULL;
    }

    GerenciadorEvento* GerenciadorEvento::getGerenciadorEvento() {     //Singleton.
        if (!pEvento) {
            pEvento = new GerenciadorEvento();
        }
        return pEvento;
    }

    void GerenciadorEvento::setMago1(entidades::personagens::Mago* pj) {
        pMago1 = pj;
    }
    void GerenciadorEvento::setMago2(entidades::personagens::Mago* pj) {
        pMago2 = pj;
    }


    void GerenciadorEvento::executar() {
        if (pMago1) {

           bool moverEsq = Keyboard::isKeyPressed(Keyboard::A);
           bool moverDir = Keyboard::isKeyPressed(Keyboard::D);
           bool pular = Keyboard::isKeyPressed(Keyboard::W);
           bool atirar = Keyboard::isKeyPressed(Keyboard::F);

            pMago1->processarInput(moverEsq, moverDir, pular, atirar);
        }
        if (pMago2) {
            bool moverEsq2 = Keyboard::isKeyPressed(Keyboard::Left);
            bool moverDir2 = Keyboard::isKeyPressed(Keyboard::Right);
            bool pular2 = Keyboard::isKeyPressed(Keyboard::Up);
            bool atirar2 = Keyboard::isKeyPressed(Keyboard::Space);

            pMago2->processarInput(moverEsq2, moverDir2, pular2, atirar2);
        }
    }

    void GerenciadorEvento::executarMenu() {

        bool down = Keyboard::isKeyPressed(Keyboard::Down);
        bool up = Keyboard::isKeyPressed(Keyboard::Up);
        bool enter = Keyboard::isKeyPressed(Keyboard::Enter);

    if (down && !prevDown) {                                 //Quando uma tecla é pressionada, o gerenciador de eventos notifica os Observadores.
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
                Keyboard::isKeyPressed(Keyboard::F) ||
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




