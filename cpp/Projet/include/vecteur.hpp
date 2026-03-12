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
    Vecteur& operator*=(const Vecteur& autre);

    friend Vecteur operator+(Vecteur v1, const Vecteur& v2);
    friend Vecteur operator-(Vecteur v1, const Vecteur& v2);
    friend Vecteur operator*(double scalaire, const Vecteur& v);

    double produitScalaire(const Vecteur& autre) const;

    void afficher() const;
}