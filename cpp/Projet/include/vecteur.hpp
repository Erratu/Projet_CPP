#include <iostream>
#include <initializer_list>

template<int D>
class Vecteur {
public:
    double coords[D];

    Vecteur(const double val[D]) : {
        for (int i = 0; i < D; ++i) {
            coords[i] = val[i];
        }
    };

    Vecteur(std::initializer_list<double> vals) {
        std::copy(vals.begin(), vals.end(), coords);
    };

    Vecteur() {
        for (int i = 0; i < D; ++i) {
            coords[i] = 0.0;
        }
    };

    ~Vecteur() = default;

    Vecteur(const Vecteur& v) : {
        for (int i = 0; i < D; ++i) {
            coords[i] = v.coords[i];
        }
    };

    Vecteur& operator=(const Vecteur& autre);

    Vecteur& operator+=(const Vecteur& autre);
    Vecteur& operator-=(const Vecteur& autre);
    Vecteur& operator*=(double scalaire);

    friend Vecteur operator+(Vecteur v1, const Vecteur& v2);
    friend Vecteur operator-(Vecteur v1, const Vecteur& v2);
    friend Vecteur operator*(Vecteur v, double scalaire);
    friend Vecteur operator*(double scalaire, const Vecteur& v);

    friend std::ostream& operator<<(std::ostream& os, const Vecteur& v);
    friend std::istream& operator>>(std::istream& is, Vecteur& v);

    void afficher() const;
};