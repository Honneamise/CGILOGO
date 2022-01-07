//std
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//stuff
#include "../SRC/html.h"
#include "../SRC/svg.h"

//defines
#define WIDTH 800
#define HEIGHT 600

#define SAMPLE_CODE "W 12 [ R 30 W 12 [ F 50 R 30 ] ]"

#define HTML_LINK_SOURCE "<a href=\"https://github.com/Honneamise/CGILOGO\">https://github.com/Honneamise/CGILOGO</a>"

#define HTML_FORM_CODE "<form method=\"post\" action=\"logo.bin\" >\
                    <textarea name=\"code\" rows=\"15\" cols=\"65\" maxlength=\"500\">%s</textarea>\
                    <br><br>\
                    <input type=\"submit\" value=\"SUBMIT\">\
                    </form>\n"

#define HTML_USAGE "<p>\
                    <b>F INT</b> : advance of INT pixels<br>\
                    <b>R INT</b> : rotate right of INT degrees<br>\
                    <b>L INT</b> : rotate left of INT degrees<br>\
                    <b>H</b> : reset position and direction<br>\
                    <b>M INT INT</b> : move to coordinates X Y<br>\
                    <b>U</b> : pen up<br>\
                    <b>D</b> : pen down<br>\
                    <b>C RGB</b> : set the current pen color<br>\
                    <b>W INT [ INSTRUCTIONS ]</b> : repeat INT times the instructions in the brackets.<br>\
                    <br>\
                    The top left of the drawing area is located at 0,0 and the bottom right at 800,600.<br>\
                    The starting position is at 400,300 and the direction points upwards.<br>\
                    INT must be a positive number in decimal format.<br>\
                    RGB is a color in standard hexadecimal format ( default is #000000 )<br>\
                    Tokens must be separated by one or more blank characters.<br>\
                    The code can be of max 500 characters, including blanks.\
                    </p>\n"


//main
int main(int argc, char **argv)  
{
	printf(HTML_HEADER,"CGI LOGO INTERPRETER");

	printf("<h1>CGI LOGO INTERPRETER</h1>");
	
	printf(HTML_LINK_SOURCE "<br><br>");

	SVG svg = SVG_init(WIDTH,HEIGHT);

	char *post = HTML_post();

	char *code = NULL;

	char *err = NULL;

	if(post)
	{
		code = HTML_field(post,"code=");

		if(code!=NULL)
		{
			HTML_unencode(code);

			SVG_begin(svg);
			err = SVG_render(&svg,code);	
			SVG_end();			
		}
		else//code is NULL
		{
			SVG_begin(svg);
			SVG_end();
		}

	}
	else//post is NULL
	{	
		SVG_begin(svg);
		SVG_render(&svg, SAMPLE_CODE);
		printf("<text x=\"50\" y=\"50\">SAMPLE CODE : %s</text>",SAMPLE_CODE);
		SVG_end();	
	}

	printf("<div>");
	printf(HTML_USAGE);
	printf(HTML_FORM_CODE,(code!=NULL) ? code:"" );
	printf("</div>");

	if(err){ printf("<h2>%s</h2>",err); }

	//clean up
	if(post){ free(post); post=NULL; }

	if(code){ free(code); code=NULL; }

	if(err){ free(err); err=NULL; }

    printf(HTML_FOOTER);

    return 0;
	
}