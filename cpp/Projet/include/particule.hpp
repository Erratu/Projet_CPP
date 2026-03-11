class Particule {
public:

    float x, y, z; // Position
    float vx, vy, vz; // Vitesse
    float masse; // Masse
    int id; // Identifiant unique
    const char* type; // Catégorie de la particule
    float forceX, forceY, forceZ; // Force appliquée à la particule

    void afficher();
    
    Particule(float x, float y, float z, float vx, 
            float vy, float vz, float masse, 
            int id, const char* type, 
            float forceX=0, float forceY=0, float forceZ=0) : 
        x(x), y(y), z(z), vx(vx), vy(vy), vz(vz),
        masse(masse), id(id), type(type),
        forceX(forceX), forceY(forceY), forceZ(forceZ) {}
};