#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Menu.hpp"
#include "Gerenciador.Grafico.hpp"
#include "Jogo.hpp"

using namespace std;
using namespace sf;

int main() {
    Jogo jogo;
    jogo.executar();
    return 0;

}