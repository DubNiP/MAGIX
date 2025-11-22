#include "Projetil.hpp"

namespace entidades
{
    Projetil::Projetil(Vector2f pos, bool dir, bool bond) :
        Entidade(pos, Vector2f(80.f, -40.f), dir),
        ativo(true),
        bondade(bond),
        dano(2)
    {
        id = 10;
		tempoMovimento.restart();
		tempoAceleracao.restart();
		clocksIni = true;
        carregarSprite();
    }

    Projetil::~Projetil()
    {
    }

    void Projetil::salvar() {
		tempBuffer.str("");
        tempBuffer.clear();

		salvarDataBuffer();

        buffer.open("Save/save.txt", ios::out | ios::app);

        if (!buffer.is_open()) {
            throw "Erro ao abrir arquivo de salvamento do projetil";
        }
    
        buffer << tempBuffer.str();
        buffer.close();
       
        tempBuffer.str("");
	}

    void Projetil::salvarDataBuffer() {
		Entidade::salvarDataBuffer();

        tempBuffer  << ativo << " "
        << bondade << " "
        << dano << " " << endl;
	}

    void Projetil::carregar(bool ativo, bool bond, int d) {
        this->ativo = ativo;
        this->bondade = bond;
        this->dano = d;
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
			emAceleracao = true;

            int direcao = olhandoDir ? 1 : -1;
            vel.x = fabs(vel.x) * direcao;

            acelerar();
            gravidade();

            attPos();
        }
    }


    int Projetil::getDano() {
        return dano;
    }

    const bool Projetil::getBondade() {
        return bondade;
    }

    void Projetil::carregarSprite() {
        if (!carregarTexturaSprite("Textures/Charge1.png")) {
            throw "Textura não carregada";
        }
        setScale(Vector2f(2.f, 2.f));
        setPos(pos);
        atualizaDirSprite();
    }
}