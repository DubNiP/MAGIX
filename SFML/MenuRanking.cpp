#include "MenuRanking.hpp"
#include "Gerenciador_Grafico.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace sf;


MenuRanking::MenuRanking() :
    Menu(),
    sair(false),
    rankPos(1),
    ranking()
{
    set_values();
    reseta();
}

MenuRanking::~MenuRanking() {
    ranking.clear();
}

vector<int> MenuRanking::calcularFaixa() {

    vector<int> faixa;

    if (ranking.empty()) return faixa;

    if (pos < 1) pos = 1;
    if (pos > static_cast<int>(ranking.size())) pos = static_cast<int>(ranking.size());

    int inicio = pos - 1;
    if (inicio < 1) inicio = 1;

    int fim = inicio + 4;
    if (fim > static_cast<int>(ranking.size())) {
        fim = static_cast<int>(ranking.size());
        inicio = max(1, fim - 4);
    }

    for (int i = inicio; i <= fim; i++)
        faixa.push_back(i);

    return faixa;
}

void MenuRanking::preencherTexts(const vector<int>& faixa) {

    for (int i = 0; i < 5; i++) {

        int posTexto = i + 1; 

        if (i < static_cast<int>(faixa.size())) {

            int idx = faixa[i] - 1;

            if (idx >= 0 && idx < static_cast<int>(ranking.size())) {
                string linha =
                    to_string(faixa[i]) + " - " +
                    ranking[idx].first + "  " +
                    to_string(ranking[idx].second);

                texts[posTexto].setString(linha);
            }
            else {
                texts[posTexto].setString(to_string(faixa[i]) + " - ---");
            }

        }
        else {
            texts[posTexto].setString(to_string(i + 1) + " - ---");
        }
    }
}

void MenuRanking::set_values() {

    ranking.clear();

    ifstream in("Save/ranking.txt");
    if (!in) {
        cerr << "MenuRanking::set_values: Save/ranking.txt não encontrado." << endl;
    }

    string nome;
    int pontos, fase;

    while (in >> nome >> pontos >> fase) {
        ranking.push_back({ nome, pontos });
    }

    sort(ranking.begin(), ranking.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        }
    );

    const Vector2f posi[] = {
        {500.f, 110.f},
        {500.f, 200.f},
        {500.f, 260.f},
        {500.f, 320.f},
        {500.f, 380.f},
        {500.f, 440.f}
    };

    const unsigned int tam[] = { 80u, 40u, 40u, 40u, 40u, 40u };

    texts.clear();
    texts.reserve(6);

    Text titulo;
    titulo.setFont(font);
    titulo.setString("Ranking Magix");
    titulo.setCharacterSize(tam[0]);
    titulo.setPosition(posi[0]);
    titulo.setFillColor(Color::White);
    texts.push_back(titulo);

    for (int i = 1; i <= 5; i++) {
        Text t;
        t.setFont(font);
        t.setString("---");
        t.setCharacterSize(tam[i]);
        t.setPosition(posi[i]);
        t.setFillColor(Color::White);
        texts.push_back(t);
    }

    posMin = 1;
    int maxSelectable = static_cast<int>(texts.size()) - 1;
    int rankingCount = static_cast<int>(ranking.size());
    posMax = max(1, min(rankingCount, maxSelectable));
    pos = posMin;
}

void MenuRanking::confirmar() { 
    sair = true;
}

bool MenuRanking::getSair() const { 
    return sair; 
}

void MenuRanking::resetaFlags() { 
    sair = false; 
}

void MenuRanking::mostrarRanking() {
    
    vector<int> faixa = calcularFaixa();

    preencherTexts(faixa);
}
