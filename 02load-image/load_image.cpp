/**
 * display bmp image
 */
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 320;
const int SCREEN_BPP = 24;

static SDL_Surface *screen = NULL;

SDL_Surface *loadOptimizedImage(std::string filename)
{
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());
	if (loadedImage != NULL)
	{
		/*
		 * 对于那些使用带透明色的PNG图片的人来说，IMG_Load()函数会自动地为他们处理透明色。
		 * 在一个已经具有透明背景色的图片上设置关键色会导致糟糕的结果。另外，如果你使用
		 * SDL_DisplayFormat()，而不是SDL_DisplayFormatAlpha()，你也会丢失Alpha透明色。
		 * 要保持PNG中的透明色，请不要设置关键色。IMG_Load()也会处理TGA图像的Alpha透明色。
		 */
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	return optimizedImage;
}

void applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

	/*
	 * srcrect是源面上的一个矩形区域，实际上，正是这个矩形区域被blit，
	 * 如果是空指针，则整个源面被blit；dstrect虽然是个矩形区域指针，
	 * 但是实际上只用到了这个矩形左上角坐标的数据。所以，实际上，它是源
	 * 面被blit到目的面上的坐标。如果是空指针，则被blit到目的面的左上角(0,0)。
	 */
	if (SDL_BlitSurface(source, NULL, destination, &offset) != 0)
		std::cout << "Error blit hello: " << SDL_GetError();

}

bool initSDL()
{
	Uint32 init_flags = SDL_INIT_EVERYTHING;
	Uint32 screen_flags = SDL_SWSURFACE | SDL_DOUBLEBUF;

	if (SDL_Init(init_flags) < 0)
	{
		std::cout << "Error initializing SDL: " << SDL_GetError();
		return false;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,
			SCREEN_BPP, screen_flags);
	if (screen == NULL)
	{
		std::cout << "Error creating screen: " << SDL_GetError();
		return false;
	}

	SDL_WM_SetCaption("hello sdl", NULL);

    return true;
}

void cleanUpSDL()
{
    SDL_Quit();
}

int main(void)
{
	if (initSDL() == false)
		return 1;

	SDL_Surface *hello = loadOptimizedImage("../images/hello.jpg");
	if (hello == NULL)
		std::cout << "Error loading image: " << SDL_GetError();
	else
		applySurface(0, 0, hello, screen);

	SDL_Surface *kiss = loadOptimizedImage("../images/kiss.png");
	if (hello == NULL)
		std::cout << "Error loading image: " << SDL_GetError();
	else
		applySurface(-100, 100, kiss, screen);

	//update screen
	if (SDL_Flip(screen) != 0)
		std::cout << "Error blit hello: " << SDL_GetError();

	SDL_Delay(3000);

	//清除表面，释放内存
	if (hello != NULL)
		SDL_FreeSurface(hello);
	if (kiss != NULL)
		SDL_FreeSurface(kiss);

	cleanUpSDL();
	return EXIT_SUCCESS;
}
