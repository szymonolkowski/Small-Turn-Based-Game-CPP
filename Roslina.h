#ifndef ROSLINA_H
#define ROSLINA_H

#include "Organizm.h"
#include <memory>

class Roslina : public Organizm {
public:
    // sila zawsze = 0, inicjatywa = 0
    Roslina(int x, int y, Swiat& swiat);
    virtual ~Roslina() = default;

    void akcja(Swiat& swiat) override;

    void kolizja(const std::shared_ptr<Organizm>& inny) override;

    virtual char rysowanie() const override = 0;

protected:
    virtual std::shared_ptr<Organizm> utworzSadzonke(int x, int y) = 0;

    // procent prawdopodobieństwo rozsiania się
    static constexpr int PROB_SIANIA = 10;
};

#endif
