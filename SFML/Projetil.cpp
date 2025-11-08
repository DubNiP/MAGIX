#include "Projetil.hpp"

Projetil::Projetil(Vector2f pos, bool dir,bool bondade) :
    Entidade(pos),
    ativo(true),
    bondade(bondade),
    velocidadeInicialX(500.0),
    direcao(dir),
    posicao(0),
    dano(2)
{
    vel.x = velocidadeInicialX;
	vel.y = 50.f;
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
        vel.x = velocidadeInicialX; 
    }
}

void Projetil::moverEsquerda() {
    if (ativo) {
        vel.x = -velocidadeInicialX; 
    }
}

void Projetil::executar() {
    if (ativo) {
        emTerra = false;

        if (direcao) {
            moverDireita();
        }
        else {
            moverEsquerda();
        }

        float dt = tempoMovimento.restart().asSeconds();
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;

        attPos();
    }
}


int Projetil::getDano() {
    return dano;
}

bool Projetil::getBondade() {
    return bondade;
}   

//void Projetil::salvar() { }

void Projetil::carregarSprite() {
    if (!carregarTexturaSprite("Textures/Charge1.png")) {
        throw "Textura não carregada";
    }
    setScale(Vector2f(2.f, 2.f));
    setPos(pos);
}