#ifndef CZLOWIEK_H
#define CZLOWIEK_H

#include "Zwierze.h"
#include <memory>

enum class Kierunek { BRAK, GORA, DOL, LEWO, PRAWO };

class Czlowiek : public Zwierze {
public:
    // siła=5, inicjatywa=4
    Czlowiek(int x, int y, Swiat& swiat);
    virtual ~Czlowiek() = default;

    void akcja(Swiat& swiat) override;

    //jeśli tarcza aktywna → odpycha zwierzęta
    void kolizja(const std::shared_ptr<Organizm>& inny) override;

    char rysowanie() const override;

    void ustawKierunek(Kierunek k);

    void aktywujUmiejetnosc();

    // sprawdzenie stanu tarczy
    bool czyTarczaAktywna() const;
    bool tarczaDostepna() const;
    bool tarczaAktywna() const;

    // gettery do zapisu
    int getKierunekInt() const;
    int getTuryTarczy() const;
    int getTuryCooldown() const;

    // setter do wczytywania
    void ustawKierunekInt(int k);
    void ustawTarczaAktywna(bool w);
    void ustawTuryTarczy(int t);
    void ustawTuryCooldown(int c);

protected:
    std::shared_ptr<Organizm> utworzPotomka(int x, int y) override {
        return nullptr;
    }

private:
    Kierunek kierunek_;
    bool umiejetnoscAktywna_;
    int turyAktywnosci_;
    int turyCooldown_;
};

#endif