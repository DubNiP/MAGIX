#include "Projetil.hpp"


Projetil::Projetil(Vector2f pos, bool dir, bool bond) :
    Entidade(pos, Vector2f(500.f,30.f), dir),
    ativo(true),
    bondade(bond),
    posicao(0),
    dano(2)
{
    velocidadeInicialX = vel.x;
	velocidadeInicialY = vel.y;
    carregarSprite();
}

Projetil::~Projetil()
{
}


void Projetil::setAtivo(bool valor) {
    ativo = valor; 
}

const bool Projetil::getAtivo() const {
    return ativo;
}

void Projetil::executar() {
    if (ativo) {
        emTerra = false;

        Vector2f novaPos = getPos();
        if (olhandoDir) {
            vel.x = velocidadeInicialX;
        }
        else {
            vel.x = -velocidadeInicialX;
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

const bool Projetil::getBondade() {
    return bondade;
}   

//void Projetil::salvar() { }

void Projetil::carregarSprite() {
    if (!carregarTexturaSprite("Textures/Charge1.png")) {
        throw "Textura não carregada";
    }
    setScale(Vector2f(2.f, 2.f));
    setPos(pos);
    atualizaDirSprite();
}