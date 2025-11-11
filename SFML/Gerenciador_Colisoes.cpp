#include "Gerenciador_Colisoes.hpp"

using namespace Gerenciadores;

GerenciadorColisoes::GerenciadorColisoes(entidades::personagens::Mago* pJog, RenderWindow* win):
	LIs(),
	LOs(),
	LPs(),
	pJog1(pJog),
	window(win),
	faseConcluida(false)
{

}

GerenciadorColisoes::~GerenciadorColisoes() {
}

const bool GerenciadorColisoes::getFaseConcluida() const {
	return faseConcluida;
}

const bool GerenciadorColisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const {
	if (!pe1 || !pe2 || pe1 == pe2) {
		return false;
	}
	return pe1->getBounds().intersects(pe2->getBounds());
}

void GerenciadorColisoes::colidiu(Entidade* a, Entidade* b) {
	if (a && b && a != b) {

		FloatRect ra = a->getBounds();
		FloatRect rb = b->getBounds();

		b->setEmTerra(estaSobre(ra, rb, b, 40.f));
	
		FloatRect inter;
		if (ra.intersects(rb, inter)) {

			Vector2f mtv(0.f, 0.f);
			if (inter.width < inter.height) {
				const float aCx = ra.left + ra.width * 0.5f;
				const float bCx = rb.left + rb.width * 0.5f;

				mtv.x = (bCx > aCx) ? inter.width : -inter.width;
			}
			else {
				const float aCy = ra.top + ra.height * 0.5f;
				const float bCy = rb.top + rb.height * 0.5f;

				mtv.y = (bCy > aCy) ? inter.height : -inter.height;
			}

			const bool aPerson = dynamic_cast<const entidades::personagens::Personagem*>(a) != NULL;
			const bool bPerson = dynamic_cast<const entidades::personagens::Personagem*>(b) != NULL;

			if (!aPerson && bPerson) {
				b->setPos(b->getPos() + mtv);
				return;
			}
			if (aPerson && !bPerson) {
				a->setPos(a->getPos() - mtv);
				return;
			}
			if (aPerson && bPerson) {

				float va = max(0.f, a->getVelocidadeX());
				float vb = max(0.f, b->getVelocidadeX());

				float soma = va + vb;
				float fracA = 0.5f;
				float fracB = 0.5f;
				if (soma > 0.0001f) {
					fracA = vb / soma;
					fracB = va / soma;
				}

				a->setPos(a->getPos() - Vector2f(mtv.x * fracA, mtv.y * fracA));
				b->setPos(b->getPos() + Vector2f(mtv.x * fracB, mtv.y * fracB));
			}
		}
	}
}

bool GerenciadorColisoes::estaSobre(const FloatRect& obst, const FloatRect& ent, Entidade* b, float folga) {
	const float entCordDireita = ent.left + ent.width;
	const float obstCordDireita = obst.left + obst.width;
	const float entCordInferior = ent.top + ent.height;
	const float obstCordSuperior = obst.top;

	const float sobrePosicao = min(entCordDireita, obstCordDireita) - max(ent.left, obst.left);
	if (sobrePosicao <= 0.f) return false;

	if (sobrePosicao < ent.width * 0.2f) return false;

	if (entCordInferior >= obstCordSuperior - folga && entCordInferior <= obstCordSuperior + folga  ) {
		b->resetaRelogio();
		return true;
	}

	return false;
}

void GerenciadorColisoes::tratarColisoesJogsObstacs() {
	if (pJog1) {
		pJog1->setNaTeia(false);
		for (auto it = LOs.begin(); it != LOs.end(); ++it) {
			if (*it && verificarColisao(*it, pJog1)) {
				if (dynamic_cast<entidades::obstaculos::Saida*>(*it) != NULL) {
					faseConcluida = true;
				}
				if (dynamic_cast<entidades::obstaculos::Teia*>(*it) == NULL) {
					colidiu(*it, pJog1);
				}
				auto* plat = dynamic_cast<entidades::obstaculos::Plataforma*>(*it);
				if (dynamic_cast<entidades::obstaculos::Plataforma*>(*it) != NULL && plat->esmagou(pJog1)) {
					pJog1->setVidas(0);
				}
				(*it)->obstaculizar(pJog1);
			}
		}

		const FloatRect bJog = pJog1->getBounds();
		for (auto it = LOs.begin(); it != LOs.end(); ++it) {
			if (*it) {
				if (auto* saida = dynamic_cast<entidades::obstaculos::Saida*>(*it)) {
					saida->atualizarPorProximidade(bJog);
				}
			}
		}
	}
}

void GerenciadorColisoes::tratarColisoesJogsBlocos() {
	if (pJog1) {
		for (auto it = LBs.begin(); it != LBs.end(); ++it) {
			if (*it && verificarColisao(*it, pJog1)) {
				colidiu(*it, pJog1);
			}
		}
	}
}


void GerenciadorColisoes::tratarColisoesJogsInimgs() {
	if (pJog1) {
		for (int i = 0; i < LIs.size(); i++) {
			if (LIs[i]) {
				if (verificarColisao(pJog1, LIs[i])) {
					colidiu(LIs[i], pJog1);
					LIs[i]->danificar();            
				}
			}
		}
	}
}

void GerenciadorColisoes::tratarColisoesJogsProjeteis() {
	if (pJog1) {
		set<Projetil*>::iterator it = LPs.begin();
		while (it != LPs.end()) {
			if (verificarColisao(pJog1, *it) && !(*it)->getBondade()) {
				pJog1->tomarDano((*it)->getDano(), (*it)->getBondade());
				(*it)->setAtivo(false);
				it = LPs.erase(it);
				continue;
			}
			it++;
		}
	}
}

void GerenciadorColisoes::tratarColisoesInimgsObstacs() {
	list<entidades::obstaculos::Obstaculo*>::iterator itObs = LOs.begin();
	while (itObs != LOs.end()) {
		if (*itObs) {
			vector<entidades::personagens::Inimigo*>::iterator itIni = LIs.begin();
			while (itIni != LIs.end()) {
				if (*itIni) {
					if (verificarColisao(*itObs, *itIni)) {
						auto* plat = dynamic_cast<entidades::obstaculos::Plataforma*>(*itObs);
						if (dynamic_cast<entidades::obstaculos::Plataforma*>(*itObs) != NULL && plat->esmagou(*itIni)) {
							(*itIni)->setVidas(0);
						}
						if (!dynamic_cast<entidades::obstaculos::Teia*>(*itObs) && (!dynamic_cast<entidades::obstaculos::Saida*>(*itObs))) {
							colidiu(*itObs, *itIni);
						}
					}
				}
				itIni++;
			}
		}
		itObs++;
	}
}

void GerenciadorColisoes::tratarColisoesInimgsBlocos() {
	for (auto itB = LBs.begin(); itB != LBs.end(); ++itB) {
		if (*itB) {
			for (auto itI = LIs.begin(); itI != LIs.end(); ++itI) {
				if (*itI && verificarColisao(*itB, *itI)) {
					colidiu(*itB, *itI);
				}
			}
		}
	}
}


void GerenciadorColisoes::tratarColisoesProjeteisObstacs() {
	auto itP = LPs.begin();
	while (itP != LPs.end()) {

		bool removido = false;

		for (auto itObs = LOs.begin(); itObs != LOs.end();) {

			if (*itObs && verificarColisao(*itP, *itObs)) {

				if (auto* teia = dynamic_cast<entidades::obstaculos::Teia*>(*itObs)) {
					if ((*itP)->getBondade()) {
						teia->setVida(teia->getVida() - (*itP)->getDano());
						if (!teia->getAtivo()) {
							itObs = LOs.erase(itObs);
						} else {
							itObs++;
						}
					} else {
						itObs++;
					}
				} else {
					itObs++;
				}

				(*itP)->setAtivo(false);
				itP = LPs.erase(itP);
				removido = true;
				break;
			} else {
				itObs++;
			}
		}

		if (!removido) {
			itP++;
		}
	}
}

void GerenciadorColisoes::tratarColisoesProjeteisInimgs() {
	set<Projetil*>::iterator itP = LPs.begin();
	while (itP != LPs.end()) {
		bool colidiu = false;
		vector<entidades::personagens::Inimigo*>::iterator itIni = LIs.begin();
		while (itIni != LIs.end()) {
			if (*itIni && verificarColisao(*itP, *itIni) && (*itP)->getBondade()) {
				(*itIni)->tomarDano((*itP)->getDano(), (*itP)->getBondade());
				(*itP)->setAtivo(false);
				itP = LPs.erase(itP);
				colidiu = true;
				break;
			}
			itIni++;
		}

		if (colidiu) {
			continue;
		}
		itP++;
	}
}

void GerenciadorColisoes::tratarColisoesInimgs() {
	vector<entidades::personagens::Inimigo*>::iterator itA = LIs.begin();
	while (itA != LIs.end()) {
		if (*itA) {
			vector<entidades::personagens::Inimigo*>::iterator itB = itA;
			++itB;
			while (itB != LIs.end()) {
				if (*itB) {
					if (verificarColisao(*itA, *itB)) {
						colidiu(*itA, *itB);
					}
				}
				itB++;
			}
		}
		itA++;
	}
}


void GerenciadorColisoes::incluirInimigo(entidades::personagens::Inimigo* pi) {
	if (pi) {
		LIs.push_back(pi);
	}
}

void GerenciadorColisoes::incluirObstaculo(entidades::obstaculos::Obstaculo* pObstaculo) {
	if (pObstaculo) {
		LOs.push_back(pObstaculo);
	}
}

void GerenciadorColisoes::incluirBloco(entidades::obstaculos::Bloco* pBloco) {
	if (pBloco) {
		LBs.push_back(pBloco);
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

void GerenciadorColisoes::limparBlocos() {
	LBs.clear();
}

void GerenciadorColisoes::limparInimigos() {
	LIs.clear();
}

void GerenciadorColisoes::limparProjetis()
{
	LPs.clear();
}

void GerenciadorColisoes::removerMortos() {
	vector<entidades::personagens::Inimigo*>::iterator it = LIs.begin();
	while (it != LIs.end()) {
		if (*it && (*it)->getVidas() <= 0) {
			it = LIs.erase(it);
		}
		else {
			++it;
		}
	}
}

void GerenciadorColisoes::executar() {
	limiteDeTela();

	tratarColisoesInimgs();
	tratarColisoesInimgsObstacs();
	tratarColisoesInimgsBlocos();

	tratarColisoesProjeteisInimgs();
	tratarColisoesProjeteisObstacs();
	tratarColisoesJogsProjeteis();

	tratarColisoesJogsObstacs();
	tratarColisoesJogsBlocos();
	tratarColisoesJogsInimgs();

	removerMortos();
}

void GerenciadorColisoes::setJog(entidades::personagens::Mago* pJog) {
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

			const float X = windowSize.x - boundJog.width;
			const float Y = 1080;
			limiteDeTelaMago(X, Y);
			limiteDeTelaProjeteis(X, Y);
		}
	}
}

void GerenciadorColisoes::limiteDeTelaMago(float X, float Y) {

	if (pJog1->getPos().x < 0.f)   pJog1->setPos(Vector2f(0.f, pJog1->getPos().y));
	if (pJog1->getPos().y < 0.f)   pJog1->setPos(Vector2f(pJog1->getPos().x, 0.f));
	if (pJog1->getPos().x > X)   pJog1->setPos(Vector2f(X, pJog1->getPos().y));
	if (pJog1->getPos().y > Y)   pJog1->setPos(Vector2f(pJog1->getPos().x, Y));
}

void GerenciadorColisoes::limiteDeTelaProjeteis(float X, float Y) {

	set<Projetil*>::iterator it = LPs.begin();

	while (it != LPs.end()) {
		Projetil* projetil = *it;

		if (projetil) {
			Vector2f posProjetil = projetil->getPos();

			if (posProjetil.x  < 0 || posProjetil.y  < 0 || posProjetil.x > X || posProjetil.y > Y) {
				projetil->setAtivo(false); //fazer a devida alteracao?	

				it = LPs.erase(it);
				continue;

			}
		}
		it++;
	}

}