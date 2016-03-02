
// tuto6 : dessiner un objet texture 
// utiliser mesh pour charger un objet .obj 
// camera pour le dessiner du point de vue d'une camera + controle de la camera a la souris
// texture : creation a partir d'un fichier, utilisation avec draw(mesh, ...) et destruction avec glDeleteTextures( )

#include "window.h"

#include "mesh.h"
#include "wavefront.h"  // pour charger un objet au format .obj
#include "texture.h"

#include "orbiter.h"

#include "draw.h"        // pour dessiner du point de vue d'une camera

Mesh objet;
GLuint texture;
Orbiter camera;

int init( )
{
    // etape 1 : charger un objet 
    objet= read_mesh("data/cube.obj");
    
    // etape 2 : creer une camera pour observer l'objet
    // construit l'englobant de l'objet, les extremites de sa boite englobante
    Point pmin, pmax;
    mesh_bounds(objet, pmin, pmax);
    
    // regle le point de vue de la camera pour observer l'objet
    camera= make_orbiter_lookat( center(pmin, pmax), distance(pmin, pmax) );

    // etape 3 : charger une texture a aprtir d'un fichier .bmp, .jpg, .png, .tga, etc, utilise read_image( ) et sdl_image
/*
    openGL peut utiliser plusieurs textures simultanement pour dessiner un objet, il faut les numeroter.
    une texture et ses parametres sont selectionnes sur une unite de texture.
    et ce sont les unites de texture qui sont utilisees pour dessiner un objet.
    
    l'exemple cree la texture sur l'unite 0 avec les parametres par defaut
 */
    texture= read_texture(0, "data/debug2x2red.png");
    
    // etat openGL par defaut
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);        // couleur par defaut de la fenetre
    
    // etape 3 : configuration du pipeline.
    glClearDepth(1.f);                          // profondeur par defaut
    glDepthFunc(GL_LESS);                       // ztest, conserver l'intersection la plus proche de la camera
    glEnable(GL_DEPTH_TEST);                    // activer le ztest
    
    return 0;   // ras, pas d'erreur
}

int draw( )
{
    // etape 2 : dessiner l'objet avec opengl
    
    // on commence par effacer la fenetre avant de dessiner quelquechose
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // on efface aussi le zbuffer
    
    // recupere les mouvements de la souris, utilise directement SDL2
    int mx, my;
    unsigned int mb= SDL_GetRelativeMouseState(&mx, &my);
    
    // deplace la camera
    if(mb & SDL_BUTTON(1))              // le bouton gauche est enfonce
        // tourne autour de l'objet
        orbiter_rotation(camera, mx, my);
    
    else if(mb & SDL_BUTTON(3))         // le bouton droit est enfonce
        // approche / eloigne l'objet
        orbiter_move(camera, mx);
    
    else if(mb & SDL_BUTTON(2))         // le bouton du milieu est enfonce
        // deplace le point de rotation
        orbiter_translation(camera, (float) mx / (float) window_width(), (float) my / (float) window_height()); 
    
    draw(objet, camera, texture);
    
    return 1;    
}

int quit( )
{
    // etape 3 : detruire la description de l'objet
    release_mesh(objet);
    // et la texture
    glDeleteTextures(1, &texture);
    
    return 0;   // ras, pas d'erreur
}

int main( int argc, char **argv )
{
    Window w= create_window(1024, 640);
    if(w == NULL) 
        return 1;       // erreur lors de la creation de la fenetre ou de l'init de sdl2
    
    Context c= create_context(w);
    if(c == NULL) 
        return 1;       // erreur lors de la creation du contexte opengl
    
    // creation des objets opengl
    if(init() < 0)
    {
        printf("[error] init failed.\n");
        return 1;
    }
    
    // affichage de l'application, tant que la fenetre n'est pas fermee. ou que draw() ne renvoie pas 0
    run(w);

    // nettoyage
    quit();
    release_context(c);
    release_window(w);
    return 0;
}

