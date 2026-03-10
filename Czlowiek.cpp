#include "Czlowiek.h"
#include "Swiat.h"
#include "Roslina.h"
#include <memory>
#include <string>

Czlowiek::Czlowiek(int x, int y, Swiat& swiat)
    : Zwierze(5, 4, x, y, swiat),
      kierunek_(Kierunek::BRAK),
      umiejetnoscAktywna_(false),
      turyAktywnosci_(0),
      turyCooldown_(0) {}

void Czlowiek::ustawKierunek(Kierunek k) {
    kierunek_ = k;
}

void Czlowiek::aktywujUmiejetnosc() {
    if (!umiejetnoscAktywna_ && turyCooldown_ == 0) {
        umiejetnoscAktywna_ = true;
        turyAktywnosci_ = 5;
        swiat_.dodajDoLogu("Tarcza Alzura AKTYWOWANA! Dziala przez 5 tur.");
    } else if (umiejetnoscAktywna_) {
        swiat_.dodajDoLogu("Tarcza Alzura jest juz aktywna. Pozostalo tur: " +
                           std::to_string(turyAktywnosci_));
    } else {
        swiat_.dodajDoLogu("Tarcza Alzura w cooldownie. Pozostalo tur do ponownej aktywacji: " +
                           std::to_string(turyCooldown_));
    }
}

void Czlowiek::akcja(Swiat& swiat) {
    int dx = 0, dy = 0;
    switch (kierunek_) {
        case Kierunek::GORA:  dy = -1; break;
        case Kierunek::DOL:   dy =  1; break;
        case Kierunek::LEWO:  dx = -1; break;
        case Kierunek::PRAWO: dx =  1; break;
        default: break;
    }
    kierunek_ = Kierunek::BRAK;

    int nx = x_ + dx, ny = y_ + dy;
    if ((dx || dy) && swiat.czyWZakresie(nx, ny)) {
        auto occ = swiat.zwrocOrganizm(nx, ny);
        if (!occ) swiat.przesunOrganizm(shared_from_this(), nx, ny);
        else     kolizja(occ);
    }

    if (czyTarczaAktywna()) {
        swiat.dodajDoLogu("Tarcza Alzura AKTYWNA. Pozostalo tur: " +
                          std::to_string(turyAktywnosci_));
    }

    if (umiejetnoscAktywna_) {
        if (--turyAktywnosci_ == 0) {
            umiejetnoscAktywna_ = false;
            turyCooldown_ = 5;
            swiat.dodajDoLogu("Tarcza Alzura DEZAKTYWOWANA. Rozpoczyna sie 5-tur. cooldown.");
        }
    } else if (turyCooldown_ > 0) {
        if (--turyCooldown_ == 0) {
            swiat.dodajDoLogu("Tarcza Alzura ponownie DOSTEPNA!");
        }
    }
}

void Czlowiek::kolizja(const std::shared_ptr<Organizm>& inny) {
    if (auto ros = dynamic_cast<Roslina*>(inny.get())) {
        inny->kolizja(shared_from_this());
        swiat_.przesunOrganizm(shared_from_this(), ros->getX(), ros->getY());
        return;
    }

    if (czyTarczaAktywna() && dynamic_cast<Zwierze*>(inny.get())) {
        auto [px, py] = swiat_.znajdzWolnePoleObok(x_, y_);
        if (px != -1) {
            swiat_.przesunOrganizm(inny, px, py);
            swiat_.dodajDoLogu("Zwierze odparte przez tarcze Alzura!");
            return;
        }
    }

    Zwierze::kolizja(inny);
}

char Czlowiek::rysowanie() const {
    return 'C';
}

// gettery i settery dla wczytu/zapisu
int Czlowiek::getKierunekInt() const { return static_cast<int>(kierunek_); }
void Czlowiek::ustawKierunekInt(int k) { kierunek_ = static_cast<Kierunek>(k); }

bool Czlowiek::czyTarczaAktywna() const { return umiejetnoscAktywna_; }
bool Czlowiek::tarczaAktywna()    const { return umiejetnoscAktywna_; }
bool Czlowiek::tarczaDostepna()   const { return !umiejetnoscAktywna_ && turyCooldown_ == 0; }

int Czlowiek::getTuryTarczy()   const { return turyAktywnosci_; }
int Czlowiek::getTuryCooldown() const { return turyCooldown_; }

void Czlowiek::ustawTarczaAktywna(bool w) { umiejetnoscAktywna_ = w; }
void Czlowiek::ustawTuryTarczy(int t)    { turyAktywnosci_    = t; }
void Czlowiek::ustawTuryCooldown(int c)  { turyCooldown_      = c; }
