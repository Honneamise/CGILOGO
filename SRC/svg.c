//std
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

//stuff
#include "svg.h"

/**********/
static int TOKEN_isint(char *token)
{
    if(!token) { return 0; }

    int len = strlen(token);

    for(int i=0;i<len;i++)
    {
        if(!isdigit(token[i])) { return 0; }
    }

    return 1;
}

/**********/
static int TOKEN_isrgb(char *token)
{
    if(!token) { return 0; }

    int len = strlen(token);

    if(len!=7 || token[0]!='#'){ return 0; }

    for(int i=1;i<len;i++)
    {
        if(!isalnum(token[i])) { return 0; }
    }

    return 1;
}

/**********/
static int TOKEN_isleft(char *token)
{
    if(!token) { return 0; }

    return strcmp(token,"[")==0;
}

/**********/
static int TOKEN_isright(char *token)
{
    if(!token) { return 0; }

    return strcmp(token,"]")==0;
}

/**********/
char *SVG_error(char *err, char *token)
{
    if(!err) { return 0; }
    
    char *buffer=calloc(LEN_256,sizeof(char));

    if(token){ sprintf(buffer,"%s ( found : \"%s\" )", err, token); }
    else { sprintf(buffer,"ERROR : %s",err); }

    return buffer;
}

/**********/
SVG SVG_init(int w, int h)
{
    SVG svg = {0};

    svg.w = w;

    svg.h = h;

    svg.pen = 1;

    strcpy(svg.color,"#000000");//default pen is black

    svg.pos.x = w/2;
    svg.pos.y = h/2;

    svg.dir.x = 0.0f;
    svg.dir.y = -1.0f;

    svg.render_start = clock();

    return svg;

}

/**********/
void SVG_begin(SVG svg)
{
     printf("<svg width=\"%d\" height=\"%d\">\n", svg.w, svg.h);
}

/**********/
void SVG_end()
{
    printf("</svg>\n");
}

/**********/
void SVG_line(float srcx, float srcy, float dstx, float dsty, char *color)
{
    printf("<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\"/>\n",
    srcx,
    srcy,
    dstx,
    dsty,
    color);
}

/**********/
char *SVG_render(SVG *svg, char *code)
{
    if(!svg || !code) { return SVG_error(SVG_ERR_RENDER,NULL); }
    
    char *delimiters = " \f\n\r\t\v";

    char *save = NULL;

    char str[LEN_512] = {0};

    strcpy(str,code);

  	char *token = strtok_r(str, delimiters, &save);

  	while(token != NULL)
  	{  
        if( (float)(clock()-svg->render_start)/CLOCKS_PER_SEC > SVG_TIMEOUT ) { return SVG_error(SVG_ERR_TIMEOUT,NULL); };

        //forward
    	if(strcasecmp(token,"F")==0)
        {
            token = strtok_r(NULL, delimiters, &save);

            if(token!=NULL && TOKEN_isint(token))
            {
                int num = atoi(token);

                if(svg->pen==1)
                {
                    Vec2f end = Vec2fAdd(svg->pos, Vec2fMul(svg->dir,num) );

                    SVG_line(svg->pos.x, svg->pos.y, end.x, end.y, svg->color);
                }

                svg->pos = Vec2fAdd(svg->pos, Vec2fMul(svg->dir,num) );
            }
            else { return SVG_error(SVG_ERR_INT,token); }
        }

        //rotate right
        else if(strcasecmp(token,"R")==0)
        {
            token = strtok_r(NULL, delimiters, &save);

            if(token!=NULL && TOKEN_isint(token))
            {
                int num = atoi(token);

                svg->dir = Vec2fRotate(svg->dir, (Vec2f){0.0f, 0.0f}, num);
            }
            else { return SVG_error(SVG_ERR_INT,token); }
        }

        //rotate left
        else if(strcasecmp(token,"L")==0)
        {
            token = strtok_r(NULL, delimiters, &save);

            if(token!=NULL && TOKEN_isint(token))
            {
                int num = atoi(token);
                
                svg->dir = Vec2fRotate(svg->dir, (Vec2f){0.0f, 0.0f}, num);
            }
            else { return SVG_error(SVG_ERR_INT,token); }
        }

        //reset
        else if(strcasecmp(token,"H")==0)
        {
            svg->pos.x = svg->w/2;
            svg->pos.y = svg->h/2;
            svg->dir.x = 0.0f;
            svg->dir.y = -1.0f;
        }

        //move
        else if(strcasecmp(token,"M")==0)
        {
            int x = 0;
            int y = 0;

            token = strtok_r(NULL, delimiters, &save);
            if(token!=NULL && TOKEN_isint(token)) { x = atoi(token);}
            else { return SVG_error(SVG_ERR_INT,token); }

            token = strtok_r(NULL, delimiters, &save);
            if(token!=NULL && TOKEN_isint(token)) { y = atoi(token);}
            else { return SVG_error(SVG_ERR_INT,token); }

            if(svg->pen){ SVG_line(svg->pos.x, svg->pos.y, x, y, svg->color); }

            svg->pos.x = x;
            svg->pos.y = y;
        }

        //pen up
        else if(strcasecmp(token,"U")==0)
        {
            svg->pen = 0;
        }

        //pen down
        else if(strcasecmp(token,"D")==0)
        {
            svg->pen = 1;
        }

        //set color
        else if(strcasecmp(token,"C")==0)
        {
            token = strtok_r(NULL, delimiters, &save);
            if(token!=NULL && TOKEN_isrgb(token)) { strcpy(svg->color,token); }
            else{ return SVG_error(SVG_ERR_RGB,token); }
        }

        //loop
        else if(strcasecmp(token,"W")==0)
        {
            int num = 0;
            token = strtok_r(NULL, delimiters, &save);
            if(token!=NULL && TOKEN_isint(token)) { num = atoi(token);}
            else { return SVG_error(SVG_ERR_INT,token); }

            token = strtok_r(NULL, delimiters, &save);
            if(token!=NULL && TOKEN_isleft(token)) 
            { 
                char _code[LEN_512] = {0};

                int open = 1;

                token = strtok_r(NULL, delimiters, &save);

                while(token!=NULL)
                {
                    if(TOKEN_isleft(token)){ open++; }
                    if(TOKEN_isright(token)){ open--; }

                    if(open==0){ break; }
                    
                    strcat(_code," "); 
                    strcat(_code,token);

                    token = strtok_r(NULL, delimiters, &save);
                }


                if(token!=NULL && TOKEN_isright(token) && open==0) 
                { 
                    for(int i=0;i<num;i++)
                    { 
                        char *err = SVG_render(svg,_code);
                        if(err){ return err; }; 
                    }  
                }
                else { return SVG_error(SVG_ERR_RIGHT,token); }

            }
            else
            { 
                return SVG_error(SVG_ERR_LEFT,token);
            }
        }

        //error
        else
        {
            return SVG_error(SVG_ERR_TOKEN,token);
        }

        token = strtok_r(NULL, delimiters, &save);

  	}

    return NULL;

}
