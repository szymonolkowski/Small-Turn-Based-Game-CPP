#ifndef SWIAT_H
#define SWIAT_H

#include <vector>
#include <memory>
#include <string>
#include "Organizm.h"
#include <utility>

class Swiat {
public:
    Swiat(int width, int height);

    // jedna tura, akcje organizmów, obsługuje kolizje
    void wykonajTure();

    // Rysuje świat, wypisuje log zdarzeń, wypisuje legende
    void rysujSwiat() const;

    void dodajOrganizm(const std::shared_ptr<Organizm>& org);

    void usunOrganizm(const std::shared_ptr<Organizm>& org);

    void zapiszDoPliku(const std::string& filename) const;
    void wczytajZPliku(const std::string& filename);

    bool czyWZakresie(int x, int y) const;

    std::shared_ptr<Organizm> zwrocOrganizm(int x, int y) const;

    void przesunOrganizm(const std::shared_ptr<Organizm>& org, int nx, int ny);

    std::pair<int,int> znajdzWolnePoleObok(int x, int y) const;

    void dodajDoLogu(const std::string& msg);

    const std::vector<std::shared_ptr<Organizm>>& getOrganizmy() const;

    int getWidth() const;
    int getHeight() const;
private:
    int width_;
    int height_;

    // wszystkie organizmy
    std::vector<std::shared_ptr<Organizm>> organizmy_;

    std::vector<std::string> log_;

    void czyscLog();
};

#endif
