#include "Trawa.h"
#include "Swiat.h"

Trawa::Trawa(int x, int y, Swiat& swiat)
    : Roslina(x, y, swiat)
{}

char Trawa::rysowanie() const {
    return 'T';
}

std::shared_ptr<Organizm> Trawa::utworzSadzonke(int x, int y) {
    // tworzy nową Trawę
    return std::make_shared<Trawa>(x, y, swiat_);
}
