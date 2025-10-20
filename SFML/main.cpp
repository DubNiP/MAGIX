#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Menu.hpp"
#include "Gerenciador.Grafico.hpp"

using namespace std;
using namespace sf;

int main() {
    GerenciadorGrafico* gerenciador = GerenciadorGrafico::getInstancia();
    gerenciador->executar();
                               //nao deleta?
    return 0;

}