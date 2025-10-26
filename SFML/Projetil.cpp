#include "Projetil.hpp"


Projetil::Projetil(Vector2f pos, bool dir) :
    Entidade(pos),
    ativo(true),
    velocidade(5),
    direcao(dir),
    posicao(0),
    dano(1)
{
    carregarSprite();
}

Projetil::~Projetil()
{
}


void Projetil::setAtivo(bool valor) {
    ativo = valor; 
}

bool Projetil::getAtivo() const {
    return ativo;
}

void Projetil::moverDireita() {
    if (ativo) {
        Vector2f novaPos = getPos();
        novaPos.x += velocidade;
        setPos(novaPos);
    }
}

void Projetil::moverEsquerda() {
    if (ativo) {
        Vector2f novaPos = getPos();
        novaPos.x -= velocidade;
        setPos(novaPos);
    }
}

void Projetil::executar() {
    if (ativo) {
        if (direcao) {
            moverDireita();
            return;
        }
        moverEsquerda();
    }
}

int Projetil::getDano() {
    return dano;
}

//void Projetil::salvar() { }

void Projetil::carregarSprite() {
    if (!carregarTexturaSprite("Textures/Charge1.png")) {
        throw "Deu merda aqui";
    }
    setScale(Vector2f(2.f, 2.f));
    setPos(pos);
}