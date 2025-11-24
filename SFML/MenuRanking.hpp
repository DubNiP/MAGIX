#pragma once
#include "Menu.hpp"
#include <vector>
#include <string>

namespace Gerenciadores { class GerenciadorGrafico; }

class MenuRanking : public Menu {
private:
    bool sair;
    int rankPos;
    vector<pair<string, int>> ranking;

protected:
    void set_values();

public:
    MenuRanking();
    ~MenuRanking();

    void confirmar();
    bool getSair() const;
    void resetaFlags();

    void mostrarRanking();

    vector<int> calcularFaixa();
    void preencherTexts(const vector<int>& faixa);
};
