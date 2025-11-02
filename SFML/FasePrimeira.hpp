#pragma once
#include "Fase.hpp"
#include "Golem.hpp"
#include "Jogador.hpp"
#include "Plataforma.hpp"

namespace fases {

	class FasePrimeira : public Fase {
	private:
		const int maxGolems;
	protected:
		void criarInimigos();
		void criarObstaculo();


		void criarGolems();


		void criarObsMedios();

		void carregarFundo();

	public:
		FasePrimeira(entidades::personagens::Jogador* pJog);         //FASE ESTÁ CONHECENDO JOGADOR AQUI, E NO DIAGRAMA NÃO TEM NADA, PODE?
		~FasePrimeira();
	};

}