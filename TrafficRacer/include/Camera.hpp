#ifndef Camera_hpp
#define Camera_hpp

#include "SDL_Tools.hpp"
#include "Objet.hpp"
#include "Route.hpp"

class Camera
{
public:
    Camera();
    virtual ~Camera();

    void CameraInit( int vue, Route* route, Objet* plateau);

    void gestionTouches( SDL_Event& event, Route* route, Objet* plateau );
    void afficherRouteEchelle1(Route* route);
    void afficherToutPlateau(Objet* plateau);
    void afficherTouteRoute(Route* route);
    void calculerEchelle();
protected:
private:
};

#endif /* Camera_hpp */
