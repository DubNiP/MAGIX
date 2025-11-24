#include "Fase.hpp"
#include <random>
#include <fstream>
#include <string>
#include <iostream>
#include "Golem.hpp"
#include "MagoNegro.hpp"

using namespace fases;  

listas::ListaEntidades Fase::lista_ents;

Fase::Fase(entidades::personagens::Mago* pJog1, entidades::personagens::Mago* pJog2):
    Ente(),
    GC(pJog1),
    jog1(pJog1),
    jog2(pJog2),
    faseIniciada(false),
    pause(false),
    cenarioCriado(false),
    doisJog(false)
{
    if (pJog2) { 
        GC.setJog2(pJog2);
    }
}

Fase::~Fase() {
    limparCenario();
    
    jog1 = NULL;
    jog2 = NULL;
}

void Fase::criarCenario() {
 
    limparCenario(); 

    Vector2f posInicial = getPosicaoInicialJogador();

    if (jog1) {
        jog1->reseta(posInicial, 15, 0);

		jog1->setFaseAtual(this);
        lista_ents.incluir(jog1);
    }

    if (jog2 && doisJog) {
        jog2->reseta(posInicial, 15, 0);

        jog2->setFaseAtual(this);
        lista_ents.incluir(jog2);
        GC.setJog2(jog2);
    }
    else {
        GC.setJog2(NULL);
    }


    //padrão de projeto Template Method
    carregarFundo();
    criarObstaculo();
    criarInimigos();
    criarBlocos();
    criarPlataformas();
}

Entidade* Fase::criaEntidade(Entidade* e) {
    if (e) {

        lista_ents.incluir(e);

        if (auto* ob = dynamic_cast<entidades::obstaculos::Obstaculo*>(e)) {
            GC.incluirObstaculo(ob);
        }
        else if (auto* ini = dynamic_cast<entidades::personagens::Inimigo*>(e)) {
            GC.incluirInimigo(ini);
        }
        else if (auto* prj = dynamic_cast<entidades::Projetil*>(e)) {
            GC.incluirProjetil(prj);
        }
        else if (auto* bloco = dynamic_cast<entidades::obstaculos::Bloco*>(e)) { 
            GC.incluirBloco(bloco);
        }

        return e;
    }
    return NULL;
}

void Fase::limparCenario() {
    GC.limparObstaculos();
    GC.limparInimigos();
    GC.limparProjetis();
    GC.limparBlocos();
    lista_ents.limparPreservando(jog1, jog2);
}

void Fase::inicializar() {
    if (!cenarioCriado) {
        criarCenario();
        cenarioCriado = true;
    }
}

void Fase::executar() {
    inicializar();
    lista_ents.retomarTodos();                                             //Despausa os clocks das entidades.
    pause = false;

    if (pGG) {
        RenderWindow* window = pGG->getWindow();
        Event event;
        faseIniciada = true;
        bool teclaEscAnterior = false;
        while (window && window->isOpen() && jog1 && jog1->getVidas() > 0 && !GC.getFaseConcluida()) {        //Enquanto as vidas do jogador1 > 0 e a fase não ser concluída..
            pGG->atualizarCamera(jog1->getPos());
		    View cam = pGG->getCamera();

            window->setView(cam);
            
            if (!Gerenciador::GerenciadorEvento::getGerenciadorEvento()->verificarEventosJanela(window)) {
                return;
            }

            bool teclaEsc = Keyboard::isKeyPressed(Keyboard::Escape);
            if (teclaEsc && !teclaEscAnterior) {
                pause = true;
                return; 
            }
            teclaEscAnterior = teclaEsc;

            Gerenciador::GerenciadorEvento::getGerenciadorEvento()->executar();
            lista_ents.executarTodos();
            GC.executar();

            if (jog2 && jog2->getVidas() <= 0) {
                lista_ents.excluir(jog2);
                Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMago2(NULL);
                GC.setJog2(NULL);
                doisJog = false;
            }

            pGG->desenhaTodos(&lista_ents,pSprite);   
        }
        jog1->setConcluiuFase(GC.getFaseConcluida());
    }
}

void Fase::resetar() {
    cenarioCriado = false;
    faseIniciada = false;
    inicializar();
}

void Fase::criarProjetil(Vector2f pos, bool dir, bool bond) {
    criaEntidade(new entidades::Projetil(pos, dir, bond));
}

void Fase::setdoisJog(bool doisJ) {
    doisJog = doisJ;
}

const bool Fase::getFaseIniciada() const {
    return faseIniciada;
}

const bool Fase::getPause() const {
    return pause;
}

listas::ListaEntidades* Fase::getListaEntidades() {
    return &lista_ents;
}


void Fase::carregarSave(const string& caminho) {
    ifstream recuperarDados(caminho, ios::in);

    char n[50];
    int p, f;

	recuperarDados >> n >> p >> f;

    if (!recuperarDados.is_open()) {
        cerr << "Fase::carregarSave: nao foi possivel abrir " << caminho << endl;
		fflush(stdin);
        return;
    }

    // limpar fase
    limparCenario();

    if (jog1) {
        jog1->setFaseAtual(this);
        lista_ents.incluir(jog1);
        Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMago1(jog1);
    }

    criarBlocos();

	int contPlat = 0;
    int idEnt = -1;
    float posx = 0.f, posy = 0.f;
    int emTerraInt = 0;
    float velx = 0.f, vely = 0.f;
    float vIniX = 0.f, vIniY = 0.f;
    int emAcelInt = 0;
    int olhandoDirInt = 1;

    while (recuperarDados >> idEnt >> posx >> posy >> emTerraInt
        >> velx >> vely >> vIniX >> vIniY
        >> emAcelInt >> olhandoDirInt) {
        Vector2f posL(posx, posy);
        Vector2f vel(velx, vely);
        Vector2f velInit(vIniX, vIniY);
        bool emTerra = (emTerraInt != 0);
        bool emAcl = (emAcelInt != 0);
        bool olhando = (olhandoDirInt != 0);

        int numVidas = 0;
        if (idEnt == 1 || idEnt == 2 || idEnt == 3 || idEnt == 4) {
            if (!(recuperarDados >> numVidas)) {
                recuperarDados.clear();
                string lixo; getline(recuperarDados, lixo);
                numVidas = 0;
            }
        }

        int m = 0, d = 0;
        short mA = 0;
        Vector2f pI(0.f, 0.f);
        float tS = 0.f, tP = 0.f;
        if (idEnt >= 2 && idEnt <= 4) {
            if (!(recuperarDados >> m >> mA >> pI.x >> pI.y >> d >> tS >> tP)) {
                recuperarDados.clear();
                string lixo; getline(recuperarDados, lixo);
            }
        }

        switch (idEnt) {
            case 1: { // Mago 
                int pontosInt = 0, naTeiaInt = 0, apto = 0, concluiuInt = 0;
                float inv = 0.f, tDano = 0.f, tAtaq = 0.f;

                if (!(recuperarDados >> pontosInt >> inv >> tDano >> tAtaq
                    >> naTeiaInt >> apto >> concluiuInt)) {
                    recuperarDados.clear();
                    string lixo;
                    getline(recuperarDados, lixo);
                    break;
                }
                if (jog1) {
                    setarEntidade(jog1, posL, emTerra, emAcl, vel, velInit, olhando);
                    jog1->carregar(numVidas, pontosInt, inv, tDano, tAtaq,
                        naTeiaInt != 0, apto!= 0 , concluiuInt != 0);
                    jog1->iniciarClocks();
                    jog1->setNome(n);
                }
                break;
            }
             
            case 2: { // Sapo
                float raio = 0.f, intervalo = 0.f;
                if (!(recuperarDados >> raio >> intervalo)) {
                    recuperarDados.clear();
                    string lixo; 
                    getline(recuperarDados, lixo);
                }
                auto* s = new entidades::personagens::Sapo(posL, jog1, Vector2f(20.f, 70.f));
                setarEntidade(s, posL, emTerra, emAcl, vel, velInit, olhando);
                s->setVidas(numVidas);
                s->carregar(numVidas, m, jog1, mA, pI, d, raio, intervalo);
                criaEntidade(s);
                break;
            }

            case 3: { // MagoNegro
                int tamanho = 0; bool apto = false;
                if (!(recuperarDados >> tamanho >> apto )) {
                    recuperarDados.clear();
                    string lixo; 
                    getline(recuperarDados, lixo);
                }
                auto* mn = new entidades::personagens::MagoNegro(posL, jog1, Vector2f(20.f, -70.f));
                setarEntidade(mn, posL, emTerra, emAcl, vel, velInit, olhando);
                mn->setVidas(numVidas);
                mn->carregar(numVidas, m, jog1, mA, pI, d, tamanho, apto);
                mn->setFaseAtual(this);
                criaEntidade(mn);
                break;
            }

            case 4: { // Golem
                int tamanho = 0; 
                if (!(recuperarDados >> tamanho )) {
                    recuperarDados.clear();
                    string lixo; 
                    getline(recuperarDados, lixo);
                }
                auto* g = new entidades::personagens::Golem(posL, jog1, Vector2f(20.f, -70.f));
                setarEntidade(g, posL, emTerra, emAcl, vel, velInit, olhando);
                g->setVidas(numVidas);
                g->carregar(numVidas, m, jog1, mA, pI, d, tamanho);
                criaEntidade(g);
                break;
            }

            case 5: { // Teia
                bool dano = false; float larg = 0.f, alt = 0.f;
                int vida = 0; int ativoInt = 0;
  
                if (!(recuperarDados >> dano >> larg >> alt >> vida >> ativoInt)) {
                    recuperarDados.clear();
                    string lixo; getline(recuperarDados, lixo);
                }
                auto* t = new entidades::obstaculos::Teia(posL, Vector2f(larg, alt));
                setarEntidade(t, posL, emTerra, emAcl, vel, velInit, olhando);
                t->carregar(larg, alt, dano, vida, (ativoInt != 0));
                criaEntidade(t);
                break;
            }

            case 6: { // Saida
                bool dano = false; float larg = 0.f, alt = 0.f;
                bool aberta = false; float raio = 0.f;
                if (!(recuperarDados >> dano >> larg >> alt >> aberta >> raio)) {
                    recuperarDados.clear();
                    string lixo; getline(recuperarDados, lixo);
                }
                auto* s = new entidades::obstaculos::Saida(posL, Vector2f(larg, alt));
                setarEntidade(s, posL, emTerra, emAcl, vel, velInit, olhando);
                s->carregar(larg, alt, dano, aberta, raio);
                criaEntidade(s);
                break;
            }

            case 7: { // Plataforma
                bool dano = false; float larg = 0.f, alt = 0.f;
                contPlat++;
                float ampl = 0.f, per = 0.f, yin = 0.f, yant = 0.f; bool ativ = false; float temp = 0.f;
                if (!(recuperarDados >> dano >> larg >> alt >> ampl >> per >> yin >> yant >> ativ >> temp)) {
                    recuperarDados.clear();
                    string lixo; getline(recuperarDados, lixo);
                }
                carregarPlataforma(contPlat, ativ, temp);
                break;
            }

            case 8: { // Espinho
                bool dano = false; float larg = 0.f, alt = 0.f;
                int quantDano = 0;
                if (!(recuperarDados >> dano >> larg >> alt >> quantDano)) {
                    recuperarDados.clear();
                    string lixo; getline(recuperarDados, lixo);
                }
                auto* e = new entidades::obstaculos::Espinho(posL, Vector2f(larg, alt), quantDano);
                setarEntidade(e, posL, emTerra, emAcl, vel, velInit, olhando);
                e->carregar(larg, alt, dano, quantDano);
                criaEntidade(e);
                break;
            }

            case 10: { // Projetil
                bool ativo, olhandoDir, bond;
                int danoInt = 0;

                if (!(recuperarDados >> ativo >> olhandoDir >> bond >> danoInt)) {
                    recuperarDados.clear();
                    string lixo;
                    getline(recuperarDados, lixo);
                }
                auto* pr = new entidades::Projetil(posL, olhandoDir, bond);
                setarEntidade(pr, posL, emTerra, emAcl, vel, velInit, olhando);
                pr->carregar(ativo, bond, danoInt);
                criaEntidade(pr);
                break;
            }

            default: {
                recuperarDados.clear();
                string lixo; getline(recuperarDados, lixo);
                break;
            }           
        }
    } 

    recuperarDados.close();

}

void Fase::setarEntidade(Entidade* ent, Vector2f posL, bool emTerra,
    bool emAcl, Vector2f vel, Vector2f velInit, bool olhandoDir) {
    ent->setPos(posL);
    ent->setEmTerra(emTerra);
    ent->setEmAceleracao(emAcl);
    ent->setVelocidade(vel.x, vel.y);
    ent->setVelocidadeInicial(velInit.x, velInit.y);
    ent->setOlhandoDir(olhandoDir);
}