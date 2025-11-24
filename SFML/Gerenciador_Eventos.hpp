#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include "Mago.hpp"
#include "Menu.hpp"
#include "Subject.hpp"
#include <deque>

// Gerenciador de Eventos com apoio do padrão de projeto Observer.

namespace Gerenciador {

    class GerenciadorEvento : public subject {
    private:
        static GerenciadorEvento* pEvento;
        entidades::personagens::Mago* pMago1;
        entidades::personagens::Mago* pMago2;
        bool prevUp;
        bool prevDown;
        bool prevEnter;

        // fila local de eventos coletados da janela
        deque<Event> eventQueue;

        GerenciadorEvento();
        ~GerenciadorEvento();

    public:

        static GerenciadorEvento* getGerenciadorEvento();

        void setMago1(entidades::personagens::Mago* pj);
        void setMago2(entidades::personagens::Mago* pj);

        void executar();
        void executarMenu();
        void soltaTeclas();

        // coleta eventos da janela e os armazena internamente
        // retorna false se janela foi fechada
        bool verificarEventosJanela(RenderWindow* window);

        // APIs para consumir a fila de eventos coletada
        bool temEvento() const;
        bool proximoEvento(Event& out);
    };

}