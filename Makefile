CROSS_COMPILE =
CC = $(CROSS_COMPILE)gcc

#in
SRC  = ${wildcard graphic/*.c}
SRC += ${wildcard *.c}
OBJ = ${patsubst %.c, %.o, $(SRC)}

#out
OUT = app

#flags
INCLUDE=-Iinclude -I/usr/include/gtk-2.0 -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/lib/i386-linux-gnu/gtk-2.0/include -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/atk-1.0
LIBS=-L/usr/lib/i386-linux-gnu -lgtk-x11-2.0 -lgobject-2.0 -lgdk_pixbuf-2.0.so.0.3000.7 -lgdk-x11-2.0 -lpango-1.0
CFLAGS = $(INCLUDE) $(LIBS) -O0 -g -Wall

#result
$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	@echo "clean done"
	@rm $(OBJ)
