#include "Wilk.h"
#include "Swiat.h"

Wilk::Wilk(int x, int y, Swiat& swiat)
    : Zwierze(9, 5, x, y, swiat) {}

char Wilk::rysowanie() const {
    return 'W';
}

std::shared_ptr<Organizm> Wilk::utworzPotomka(int x, int y) {
    // tworzy nowego wilka
    return std::make_shared<Wilk>(x, y, swiat_);
}
