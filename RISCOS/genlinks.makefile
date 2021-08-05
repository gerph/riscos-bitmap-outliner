all: dirs \
     c/bitmap-outliner \
     h/bitmap-outliner \
     c/main \

dirs:
	mkdir -p c h

c/bitmap-outliner: ../src/bitmap-outliner.c
	ln -sf ../$? $@
h/bitmap-outliner: ../src/bitmap-outliner.h
	ln -sf ../$? $@
c/main: ../main.c
	ln -sf ../$? $@
