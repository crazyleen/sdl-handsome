CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		load_bmp_image.o

LIBS = -lSDL

TARGET =	load_bmp_image

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
