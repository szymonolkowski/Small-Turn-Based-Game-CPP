#ifndef ZWIERZE_H
#define ZWIERZE_H

#include "Organizm.h"
#include <memory>

class Zwierze : public Organizm {
public:
    Zwierze(int sila, int inicjatywa, int x, int y, Swiat& swiat);
    virtual ~Zwierze() = default;

    //losowy krok
    void akcja(Swiat& swiat) override;

    //rozmnażanie lub walka
    void kolizja(const std::shared_ptr<Organizm>& inny) override;

protected:
    // tworzenie potomka
    virtual std::shared_ptr<Organizm> utworzPotomka(int x, int y) = 0;
};

#endif
