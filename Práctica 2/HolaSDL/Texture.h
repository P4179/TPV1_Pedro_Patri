
#ifndef TextureH
#define TextureH

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "checkML.h"
#include "SDLError.h"

#include <string>

using namespace std;

typedef unsigned int uint;

class Texture {
private:
    SDL_Texture* texture = nullptr;
    SDL_Renderer* renderer = nullptr;
    uint w = 0;
    uint h = 0;
    uint fw = 0; // Frame width
    uint fh = 0; // Frame height
    uint numCols = 1;   // columnas
    uint numRows = 1;   // filas

    void libera();
    void load(string filename, uint numRows = 1, uint numCols = 1);

public:
    // construirse, es decir, cargarse de fichero
    Texture(SDL_Renderer* r) : renderer(r) {};
    Texture(SDL_Renderer* r, string filename, uint numRows = 1, uint numCols = 1) : renderer(r) { load(filename, numRows, numCols); };
    ~Texture() { libera(); };

    // getters
    int getW() const { return w; };
    int getH() const { return h; };
    uint getNumCols() const { return numCols; };
    SDL_Texture* getTexture() const { return texture; };

    // dibujarse en pantalla
    void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
    void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};

#endif