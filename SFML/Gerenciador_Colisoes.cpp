#include "Gerenciador_Colisoes.hpp"

GerenciadorColisoes::GerenciadorColisoes(Jogador* pJog, RenderWindow* win):
	LOs(),
	pJog1(pJog),
	window(win)
{

}

GerenciadorColisoes::~GerenciadorColisoes() {
}

const bool GerenciadorColisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const {
	if (!pe1 || !pe2 || pe1 == pe2) {
		return false;
	}
	return pe1->getBounds().intersects(pe2->getBounds());
}

void GerenciadorColisoes::tratarColisoesJogsObstaculos() {
	
	if (pJog1) {
		list<Obstaculo*>::iterator it = LOs.begin();
		while (it != LOs.end()) {
			if (*it) {                                             //no futuro posso implementar uma funçao que simplifica esse processo de AABB e MTV
				FloatRect jog = pJog1->getBounds();
				FloatRect obs = (*it)->getBounds();
				if (jog.intersects(obs)) {                
					float jogx = jog.left + jog.width / 2;         //Lógica: a posição central é a coordenada que fica no topo superior esquerdo + a altura/largura.         
					float jogy = jog.top + jog.height / 2;
					float obsx = obs.left + obs.width / 2;
					float obsy = obs.top + obs.height / 2;
					const float sobrePosX = (jog.width * 0.5f + obs.width * 0.5f) - fabs(jogx - obsx);
					const float sobrePosY = (jog.height * 0.5f + obs.height * 0.5f) - fabs(jogy - obsy);


					Vector2f MTV(0, 0);                      //dar uma olhada na colisão
					if (sobrePosX < sobrePosY) {        
						if (jogx > obsx) {
							MTV.x = sobrePosX;
						}
						else {
							MTV.x = -sobrePosX; 
						}
					}
					else {
						
						if (jogy > obsy) {
							MTV.y = sobrePosY;
						}
						else {
							MTV.y = -sobrePosY;
						}
					}

					pJog1->setPos(pJog1->getPos() + MTV);
					(*it)->obstaculizar(pJog1);
				}
			}
			it++;
		}


	}
}

void GerenciadorColisoes::incluirObstaculo(Obstaculo* pObstaculo) {
	if (pObstaculo) {
		LOs.push_back(pObstaculo);
	}
}

void GerenciadorColisoes::executar() {
	if (pJog1) {
		list<Obstaculo*>::iterator it = LOs.begin();
		while (it != LOs.end()) {
			if (*it && window) {
				(*it)->draw(window);                             //WARNING: DESENHAR DEVE SER NO GERENCIADOR GRÁFICO...
			}
			it++;
		}
		tratarColisoesJogsObstaculos();
	}
}

void GerenciadorColisoes::setJog(Jogador* pJog) {
	pJog1 = pJog;
}

void GerenciadorColisoes::setWindow(RenderWindow* win) {
	window = win;
}

// Observação:  as demais funções comentadas no .hpp
// não são definidas aqui até que as dependências sejam implementadas