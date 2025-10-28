#include "Gerenciador_Colisoes.hpp"

GerenciadorColisoes::GerenciadorColisoes(Jogador* pJog, RenderWindow* win):
	LIs(),
	LOs(),
	LPs(),
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

void GerenciadorColisoes::colidiu(Entidade* pe1, Entidade* pe2, FloatRect jog, FloatRect en) {
	if (pe1 && pe2 && pe1 != pe2) {
		float jogx = jog.left + jog.width / 2;         //Lógica: a posição central é a coordenada que fica no topo superior esquerdo + a altura/largura.  
		float jogy = jog.top + jog.height / 2;
		float obsx = en.left + en.width / 2;
		float obsy = en.top + en.height / 2;
		const float sobrePosX = (jog.width * 0.5f + en.width * 0.5f) - fabs(jogx - obsx);
		const float sobrePosY = (jog.height * 0.5f + en.height * 0.5f) - fabs(jogy - obsy);


		Vector2f MTV(0, 0);                     
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
	}

}




void GerenciadorColisoes::tratarColisoesJogsObstacs() {
	
	if (pJog1) {
		list<Obstaculo*>::iterator it = LOs.begin();
		while (it != LOs.end()) {
			if (*it) {                                           
				FloatRect jog = pJog1->getBounds();
				FloatRect obs = (*it)->getBounds();
				if (verificarColisao(pJog1, *it)) {
					colidiu(*it, pJog1, jog, obs);
					(*it)->obstaculizar(pJog1);
				}
			}
			it++;
		}


	}
}
void GerenciadorColisoes::tratarColisoesJogsInimgs() {
	if (pJog1) {
		for (int i = 0; i < LIs.size(); i++) {
			if (LIs[i]) {
				FloatRect jog = pJog1->getBounds();
				FloatRect inim = LIs[i]->getBounds();
				if (verificarColisao(pJog1, LIs[i])) {
					colidiu(LIs[i], pJog1, jog, inim);
					LIs[i]->danificar();                //isso tá sugando a vida do jogador MT rápido, dps é bom dar uma olhada
				}
			}
		}
	}
}

void GerenciadorColisoes::tratarColisoesJogsProjeteis() {
	if (pJog1) {
		set<Projetil*>::iterator it = LPs.begin();
		while (it != LPs.end()) {
			FloatRect jog = pJog1->getBounds();
			FloatRect inim = (*it)->getBounds();
			if (verificarColisao(pJog1, *it)) {
				pJog1->tomarDano((*it)->getDano());               
				(*it)->setAtivo(false);
				it = LPs.erase(it);
				continue;
			}
			it++;
		}
	}
}


void GerenciadorColisoes::incluirInimigo(Inimigo* pi) {
	if (pi) {
		LIs.push_back(pi);
	}
}

void GerenciadorColisoes::incluirObstaculo(Obstaculo* pObstaculo) {
	if (pObstaculo) {
		LOs.push_back(pObstaculo);
	}
}

void GerenciadorColisoes::incluirProjetil(Projetil* pProjetil)
{
	if (pProjetil) {
		LPs.insert(pProjetil);
	}
}


void GerenciadorColisoes::limparObstaculos() {
	LOs.clear();
}

void GerenciadorColisoes::limparInimigos() {
	LIs.clear();
}

void GerenciadorColisoes::limparProjetis()
{
	LPs.clear();
}

void GerenciadorColisoes::executar() {
	limiteDeTela();
	tratarColisoesJogsObstacs();
	tratarColisoesJogsProjeteis();
	tratarColisoesJogsInimgs();
}

void GerenciadorColisoes::setJog(Jogador* pJog) {
	pJog1 = pJog;
}

void GerenciadorColisoes::setWindow(RenderWindow* win) {
	window = win;
}

void GerenciadorColisoes::limiteDeTela() {
	if (window) {
		if (pJog1) {

			FloatRect boundJog = pJog1->getBounds();
			Vector2u windowSize = window->getSize();

			const int X = windowSize.x - boundJog.width;
			const int Y = windowSize.y - boundJog.height;
			limiteDeTelaJogador(X, Y);
			limiteDeTelaProjeteis(X, Y);
		}
	}
}

void GerenciadorColisoes::limiteDeTelaJogador(int X, int Y) {

	if (pJog1->getPos().x < 0)   pJog1->setPos(Vector2f(0.f, pJog1->getPos().y));
	if (pJog1->getPos().y < 0)   pJog1->setPos(Vector2f(pJog1->getPos().x, 0.f));
	if (pJog1->getPos().x > X)   pJog1->setPos(Vector2f(X, pJog1->getPos().y));
	if (pJog1->getPos().y > Y)   pJog1->setPos(Vector2f(pJog1->getPos().x, Y));
}

void GerenciadorColisoes::limiteDeTelaProjeteis(int X, int Y) {

	set<Projetil*>::iterator it = LPs.begin();

	while (it != LPs.end()) {
		Projetil* projetil = *it;

		if (projetil) {
			Vector2f posProjetil = projetil->getPos();

			if (posProjetil.x  < 0 || posProjetil.y  < 0 || posProjetil.x > X || posProjetil.y > Y) {
				projetil->setAtivo(false); //fazer a devida alteração

				it = LPs.erase(it);
				continue;

			}
		}
		it++;
	}

}