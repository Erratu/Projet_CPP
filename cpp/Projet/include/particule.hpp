class Particule {
public:

    double x, y, z; // Position
    double vx, vy, vz; // Vitesse
    double masse; // Masse
    int id; // Identifiant unique
    const char* type; // Catégorie de la particule
    double fx, fy, fz; // Force appliquée à la particule

    void afficher();
    
    Particule(double x, double y, double z, double vx, 
            double vy, double vz, double masse, 
            int id, const char* type, 
            double forceX=0, double forceY=0, double forceZ=0) : 
        x(x), y(y), z(z), vx(vx), vy(vy), vz(vz),
        masse(masse), id(id), type(type),
        fx(forceX), fy(forceY), fz(forceZ) {}
};