## 学习笔记

### SDL初始化和退出

1. SDL_Init()

2. SDL_SetVideoMode()

...

3. SDL_Quit()


### 加载bmp图像

1. `SDL_Surface *hello = SDL_LoadBMP( "hello.bmp" );`

2. `SDL_FreeSurface(hello);`

### 图像像素复制

`int SDL_BlitSurface(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect);`

复制src的矩形区域srcrect到dst的左上角(dstrect.x dstrect.y), 忽略(dstrect.w, dstrect.h)

### 格式化图像

`SDL_DisplayFormat()`

加载的图像格式不一定和screen的格式相同(可能是24位色， 32位色或者其他)，SDL会在每次blit时做一次临时性的格式转换，这会导致程序的运行效率降低。
`SDL_DisplayFormat()`来创建一个与窗口拥有同样格式的新版本的图像。SDL_DisplayFormat()创建了一个优化后的表面，但是没有去除原来的表面。

### 更新屏幕

`SDL_Flip(screen)`

