#ifndef _SVG_H
#define _SVG_H

#include "time.h"
#include "2d.h"

#define LEN_256     256
#define LEN_512     512

#define DEFAULT_SVG_W 800
#define DEFAULT_SVG_H 600

//#define SVG_SAMPLE_CODE "W 36 [ R 10 W 360 [ F 2 R 1 ] ]"
#define SVG_SAMPLE_CODE "W 12 [ R 30 W 12 [ F 50 R 30 ] ]"

#define SVG_TIMEOUT     1.0f//in seconds

#define SVG_ERR_INT     "Expected INT"
#define SVG_ERR_RGB     "Missing or malformed RGB"
#define SVG_ERR_RIGHT   "Missing right paren"
#define SVG_ERR_LEFT    "Missing left paren"
#define SVG_ERR_TOKEN   "Invalid token"
#define SVG_ERR_RENDER  "Render error"
#define SVG_ERR_TIMEOUT "Timed out"

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