## 加载不同格式的图片

SDL仅原生地支持bmp格式的图片文件，但是通过使用SDL_image这个扩展库，你将可以加载BMP, PNM, XPM, LBM, PCX, GIF, JPEG, TGA 和 PNG 格式的图片文件。

### 使用

#include <SDL/SDL_image.h>

Makefile: -lSDL_image


### IMG_Load()

IMG_Load()函数与SDL_LoadBMP()函数的功能看上去完全相同，但实际上有一个很大的不同点，就是IMG_Load()可以加载BMP, PNM, XPM, LBM, PCX, GIF, JPEG, TGA 和 PNG 格式的文件。 

```
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
```
