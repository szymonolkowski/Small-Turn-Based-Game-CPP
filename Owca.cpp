#include "Owca.h"
#include "Swiat.h"

Owca::Owca(int x, int y, Swiat& swiat)
    : Zwierze(4, 4, x, y, swiat) {}

char Owca::rysowanie() const {
    return 'O';
}

std::shared_ptr<Organizm> Owca::utworzPotomka(int x, int y) {
    return std::make_shared<Owca>(x, y, swiat_);
}
