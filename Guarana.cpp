#include "Guarana.h"
#include "Swiat.h"
#include <string>

Guarana::Guarana(int x, int y, Swiat& swiat)
    : Roslina(x, y, swiat) {}

void Guarana::akcja(Swiat& swiat) {
    Roslina::akcja(swiat);
}

void Guarana::kolizja(const std::shared_ptr<Organizm>& inny) {
    // zwieksz sile o 3
    inny->zmienSile(3);
    swiat_.dodajDoLogu(std::string("Zwierz jedzacy guarane otrzymal +3 sily"));

    Roslina::kolizja(inny);
}

char Guarana::rysowanie() const {
    return 'U';
}

std::shared_ptr<Organizm> Guarana::utworzSadzonke(int x, int y) {
    return std::make_shared<Guarana>(x, y, swiat_);
}
