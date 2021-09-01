#include "CWindow.h"

#include <SDL2/SDL_image.h>

CAM_NS_BEGIN

class CWindow::CWindowImpl
{
public:
    CWindowImpl()
    {
    }

    ~CWindowImpl()
    {
        if (NULL != mFrame) {
            SDL_FreeSurface(mFrame);
        }

        if (NULL != mBufferStream) {
            SDL_RWclose(mBufferStream);
        }

        IMG_Quit();
        SDL_Quit();
    }

    void init(const int &w, const int &h)
    {
        SDL_Init(SDL_INIT_VIDEO);
        IMG_Init(IMG_INIT_JPG);
        mWindow = SDL_CreateWindow("Video",0,0,w,h,SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
        mRenderer = SDL_CreateRenderer(mWindow,-1,0);
    }

    void putFrame(void *f, int len)
    {
        mBufferStream = SDL_RWFromMem(f,len);
        mFrame = IMG_Load_RW(mBufferStream,0);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer,mFrame);
        SDL_RenderCopy(mRenderer,texture,NULL,NULL);
        SDL_RenderPresent(mRenderer);
    }

private:
    SDL_Window *mWindow=NULL;
    SDL_Renderer *mRenderer=NULL;
    SDL_Surface *mFrame=NULL;
    SDL_RWops *mBufferStream=NULL;
    SDL_Rect mPosition = {.x=0, .y=0};
};

CWindow::CWindow()
{
    mImpl = std::make_unique<CWindowImpl>();
}

CWindow::~CWindow()
{
}

void CWindow::init(const int &w, const int &h)
{
    mImpl->init(w,h);
}
void CWindow::putFrame(void *f, int len)
{
    mImpl->putFrame(f,len);
}

CAM_NS_END