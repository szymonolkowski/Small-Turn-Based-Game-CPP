#ifndef ANTYLOPA_H
#define ANTYLOPA_H

#include "Zwierze.h"
#include <memory>

class Antylopa : public Zwierze {
public:
    // Konstruktor: siła = 4, inicjatywa = 4
    Antylopa(int x, int y, Swiat& swiat);
    virtual ~Antylopa() = default;

    // Ruch na odległość do 2 pól
    void akcja(Swiat& swiat) override;

    // 50% szans na ucieczkę zamiast walki
    void kolizja(const std::shared_ptr<Organizm>& inny) override;

    // Symbol rysowany na planszy
    char rysowanie() const override;

protected:
    // Tworzy nowe Antylopa w zadanym punkcie
    std::shared_ptr<Organizm> utworzPotomka(int x, int y) override;
};

#endif // ANTYLOPA_H
