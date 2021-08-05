#if 0
gcc -Wall -O2 -DC89 -I./src -o /tmp/`basename $0` $0 src/bitmap-outliner.c \
	&& /tmp/`basename $0` $@
exit
#endif

#include <stdlib.h>
#include <stdio.h>
#include "bitmap-outliner.h"

// the bitmap data
int const width = 6;
int const height = 6;
uint8_t const data[] = {
	0, 1, 1, 1, 0, 0,
	1, 0, 1, 0, 0, 1,
	1, 1, 0, 0, 1, 1,
	1, 0, 0, 1, 0, 1,
	0, 0, 1, 0, 1, 1,
	1, 0, 1, 1, 1, 0,
};

int main() {
	// allocate outliner
	bmol_outliner* outliner = bmol_alloc(width, height, data);
    size_t path_len;
    char *path;

	// find paths in bitmap
	bmol_find_paths(outliner, NULL);

	// calculate SVG path length (needs some performance).
	// for numerous calls to `bmol__svg_path`,
	// better use a large enough buffer directly.
	path_len = bmol_svg_path_len(outliner);

	// ok for small bitmaps; be aware to not use large buffers on the stack!
	path = malloc(path_len);
    if (path == NULL)
    {
        printf("Failed to allocate space for path\n");
        return 1;
    }

	// write SVG path to `path`
	bmol_svg_path(outliner, path, path_len);

	// output SVG
	printf(
		"<svg viewBox=\"0 0 %d %d\" xmlns=\"http://www.w3.org/2000/svg\">\n"
		"	<path d=\"%s\" fill=\"#000\" fill-rule=\"evenodd\"/>\n"
		"</svg>\n", width, height, path);

	// free outliner
	bmol_free(outliner);

    free(path);

	return 0;
}
