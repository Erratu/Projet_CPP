#include <iostream>

// ajouter un template<int D> et double data[D] pour faire du 2D ou du 3D

class Vecteur {
public:
    double x;
    double y;
    double z;

    Vecteur(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {};

    ~Vecteur() = default;

    Vecteur(const Vecteur& v) : x(v.x), y(v.y), z(v.z) {};

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