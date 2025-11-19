#include "Plataforma.hpp"

namespace entidades {
	namespace obstaculos {

		Plataforma::Plataforma(Vector2f pos, Vector2f tam, bool dano, float ampl, float per) :
			Obstaculo(pos, tam, dano),
			amplitude(ampl),
			periodo(per),
			yIn(pos.y),
			yAnt(pos.y),
			ativa(false),
			tempo()
		{
			id = 7;
			this->pos.y = yIn + amplitude;
			yAnt = pos.y;

			carregarSprite();
			tempo.restart();
		}

		Plataforma::~Plataforma() {

		}

		void Plataforma::executar() {

			if (ativa && periodo != 0.f) {
				yAnt = pos.y;

				const float t = tempo.getElapsedTime().asSeconds();
				const float omega = 2.f * 3.1415f / periodo;     // w = 2pi/T
				pos.y = yIn + amplitude * cos(omega * t);        // x = x0 + A * cos(wt)
				vel.y = pos.y - yAnt;
			}
			else {
				vel.y = 0.f;
			}
			attPos();
		}

		void Plataforma::salvar() {
			tempBuffer.str("");
			tempBuffer.clear();

			salvarDataBuffer();

			buffer.open("Save/save.txt", ios::out | ios::app);

			if (!buffer.is_open()) {
				cerr << "Arquivo não pode ser aberto" << endl;
				fflush(stdin);
				return;
			}

			buffer << tempBuffer.str();
			buffer.close();
		}

		void Plataforma::salvarDataBuffer() {
			Obstaculo::salvarDataBuffer();

			tempBuffer << amplitude << " "
				<< periodo << " "
				<< yIn << " "
				<< yAnt << " "
				<< ativa << " "
				<< tempo.getElapsedTime().asSeconds() << endl;
		}

		void Plataforma::obstaculizar(entidades::personagens::Mago* p) {
			if (p) {

				const FloatRect pj = p->getBounds();
				const FloatRect pf = getBounds();


				const float folga = 3.f;
				const bool overlapX = (pj.left + pj.width) > pf.left - folga && pj.left < (pf.left + pf.width);
				const bool onTop = (abs((pj.top + pj.height) - pf.top) <= folga) && overlapX;

				if (onTop) {
					const float deltaY = pos.y - yAnt;

					Vector2f jpos = p->getPos();
					jpos.y += deltaY;

					const float alturaJog = pj.height;
					jpos.y = pf.top - alturaJog;

					p->setPos(jpos);
				}
			}
		}

		bool Plataforma::esmagou(entidades::personagens::Personagem* p) const {
			if (p) {
				const FloatRect pj = p->getBounds();
				const FloatRect pf = getBounds();

				const float overlapX = min(pj.left + pj.width, pf.left + pf.width) - max(pj.left, pf.left);
				if (overlapX > pj.width * 0.2f && getVelocidadeY() > 0.f && (yAnt <= pj.top) && (pos.y >= pj.top)) {
					return true;
				}
			}
			return false;
		}

		void Plataforma::setAtiva() {
			ativa = true;
		}

		void Plataforma::carregarSprite() {
			if (!carregarTexturaSprite("Textures/plataforma.png", true, false)) {
				throw "Textura não carregada";
			}
			if (Sprite* sp = getSprite()) {
				sp->setTextureRect(IntRect(0, 0, static_cast<int>(largura), static_cast<int>(altura)));
			}
			setScale(Vector2f(1.f, 1.f));
			setPos(pos);
		}
	}
}