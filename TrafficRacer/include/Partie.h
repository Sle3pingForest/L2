#ifndef PARTIE_H
#define PARTIE_H


class Partie
{
    public:
        Partie();
        virtual ~Partie();
        void gestion_evenements();
        void afficher();
        bool continuer_partie();
    protected:
    private:
         bool jouer;
};

#endif // PARTIE_H
