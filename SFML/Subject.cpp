#include "Subject.hpp"
#include "Observer.cpp"

// Padrão de Projeto Observer.

subject::subject() : 
	LObs()
{

}

subject::~subject(){
}

void subject::attach(Observer* Ob) {
	LObs.incluir(Ob);
}

void subject::dettach(Observer* Ob) {
	LObs.deletar(Ob);
}

void subject::notify(int i) {
	Lista<Observer>::Iterator it = LObs.begin();
	while (it != LObs.end()) {
		if (*it) {
			(*it)->update(i);
		}
		++it;
	}
}