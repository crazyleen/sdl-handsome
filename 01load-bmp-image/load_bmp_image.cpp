/**
 * display bmp image
 */
#include <iostream>
#include <SDL/SDL.h>

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 320;
const int SCREEN_BPP = 32;

int main(void)
{

	// Init SDL
	Uint32 init_flags = SDL_INIT_EVERYTHING;
	Uint32 screen_flags = SDL_SWSURFACE | SDL_DOUBLEBUF;

	if (SDL_Init(init_flags) < 0)
	{
		std::cout << "Error initializing SDL: " << SDL_GetError();
		return 1;
	}

	SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,
			SCREEN_BPP, screen_flags);
	if (screen == NULL)
	{
		std::cout << "Error creating screen: " << SDL_GetError();
		return 4;
	}

	//设置窗口标题
	SDL_WM_SetCaption( "hello sdl", NULL);

	//load bmp image
	SDL_Surface *hello = SDL_LoadBMP( "../images/hello.bmp" );
	if (hello == NULL)
	{
		std::cout << "Error loading bmp: " << SDL_GetError();
		return 4;
	} else {
		/*
		 * 加载的图像格式不一定和screen的格式相同(可能是24位色， 32位色或者其他)，
		 * SDL会在每次blit时做一次临时性的格式转换，这会导致程序的运行效率降低。
		 * 使用SDL_DisplayFormat()来创建一个与窗口拥有同样格式的新版本的图像。
		 * SDL_DisplayFormat()创建了一个优化后的表面，但是没有去除原来的表面。
		 */
		SDL_Surface *optimizedImage = SDL_DisplayFormat( hello );
		if (optimizedImage != NULL) {
			SDL_FreeSurface(hello);
			hello = optimizedImage;
		}
	}

	/*
	 * srcrect是源面上的一个矩形区域，实际上，正是这个矩形区域被blit，
	 * 如果是空指针，则整个源面被blit；dstrect虽然是个矩形区域指针，
	 * 但是实际上只用到了这个矩形左上角坐标的数据。所以，实际上，它是源
	 * 面被blit到目的面上的坐标。如果是空指针，则被blit到目的面的左上角(0,0)。
	 */
	if (SDL_BlitSurface(hello, NULL, screen, NULL) != 0)
		std::cout << "Error blit hello: " << SDL_GetError();


	//update screen
	if (SDL_Flip(screen) != 0)
		std::cout << "Error blit hello: " << SDL_GetError();

	SDL_Delay(3000);

	//清除表面，释放内存
	SDL_FreeSurface(hello);

	SDL_Quit();

	return EXIT_SUCCESS;
}
