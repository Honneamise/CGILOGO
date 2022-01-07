#ifndef _SVG_H
#define _SVG_H

#include "time.h"
#include "2d.h"



/**********/
typedef struct SVG
{
    int w;

    int h;

    int pen;

    char color[8];

    Vec2f pos;

    Vec2f dir;

    clock_t render_start;

} SVG;

/**********/
char *SVG_error(char *err, char *token);

SVG SVG_init(int w, int h);

void SVG_begin();

void SVG_end();

char *SVG_render(SVG *svg, char *code);

void SVG_line(float srcx, float srcy, float dstx, float dsty, char *color);

#endif