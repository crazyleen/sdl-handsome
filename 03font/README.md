## 字体fft

### 使用

#include <SDL/SDL_image.h>

Makefile: -lSDL_image

1. 初始化, SDL_ttf是通过调用TTF_Init()完成初始化的。如果期间出现错误，该函数会返回 -1。必须在使用任何其他 SDL_ttf 的函数前被调用。

```
	if ( TTF_Init() < 0 )
	{
		std::cout << "Error initializing TTF: " << TTF_GetError();
		return 2;
	}
```

2. 打开字体

该函数的第一个参数是你想要打开的字体文件的文件名，第二个参数是你在打开字体文件时想要设定的字体大小。如果加载字体时出现错误，会返回NULL。

```
	TTF_Font *font = TTF_OpenFont("../font/font.otf", size);
	if ( ! font )
	{
		std::cerr << "Could not load font: " << TTF_GetError();
		return NULL;
	}
```

3. 渲染文字

最快的渲染文本的方式是使用TTF_RenderText_Solid()函数。该函数的第一个参数是字体，第二个参数是文本，第三个参数是颜色，它会使用这些来创建一个表面。
如果出现错误，该函数返回NULL。

```
	TTF_Font *font = load_font(i);
	if (font == NULL)
		continue;

	//Render the text
	SDL_Surface *message = TTF_RenderText_Solid(font, "hello world",
			textColor);

	if (hello != NULL)
		applySurface(0, 0, hello, screen);
	if (message != NULL)
		applySurface((screen->w - message->w)/2, (screen->h - message->h)/2, message, screen);

	if (SDL_Flip(screen) != 0)
		std::cout << "Error blit screen: " << SDL_GetError();

	//SDL_Delay(100);

	if (message != NULL)
		SDL_FreeSurface(message);
	TTF_CloseFont(font);
```

4. 关闭字体

```
TTF_CloseFont( font );
```

5. 退出

```
TTF_Quit();
```
