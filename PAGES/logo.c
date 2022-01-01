//std
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//stuff
#include "../SRC/html.h"
#include "../SRC/svg.h"

//main
int main(int argc, char **argv)  
{
	printf(HTML_HEADER,"CGI LOGO INTERPRETER");

	printf("<h1>CGI LOGO INTERPRETER</h1>");
	
	printf(HTML_LINK_SOURCE "<br><br>");

	SVG svg = SVG_init(DEFAULT_SVG_W,DEFAULT_SVG_H);

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
		SVG_render(&svg, SVG_SAMPLE_CODE);
		printf("<text x=\"50\" y=\"50\">SAMPLE CODE : %s</text>",SVG_SAMPLE_CODE);
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