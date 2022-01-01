#ifndef _HTML_H
#define _HTML_H

#define LEN_512     512

#define HTML_CSS    "body {\
                    color:#000000;\
                    background-color: #707070;\
                    font-family: Arial;\
                    font-size: 14px;\
                    text-align: center;\
                    display: block; }\
                    \
                    p {\
                    text-align: left;\
                    padding: 10px; }\
                    \
                    svg {\
                    border-color: #000000;\
                    border-style: solid;\
                    border-width: 1px; }\
                    \
                    div {\
                    display: inline-block;\
                    vertical-align: top; }\
                    \
                    form { padding : 10px; }\
                    \
                    textarea { resize: none; }"

#define HTML_HEADER "Content-type: text/html\n\n\
                    <!DOCTYPE html>\
                    <html lang=\"en\">\
                    <head>\
                    <title>%s</title>\
                    <style>" HTML_CSS "</style>\
                    </head>\
                    <body>\n"

#define HTML_FOOTER "</body></html>\n"

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


#define HTML_FORM_SHARE "<form method=\"post\" action=\"share.bin\" >\
                        <input type=\"hidden\" name=\"code\" value=\"%s\">\
                        <input type=\"submit\" value=\"SHARE\">\
                        </form>\n"

#define HTML_FORM_SHARE_VALIDATE "<form method=\"post\" action=\"share.bin\" >\
                                Name <input type=\"text\" name=\"name\" minlength=\"3\" required>\
                                Mail <input type=\"email\" name=\"mail\" minlength=\"3\" required>\
                                <input type=\"hidden\" name=\"code\" value=\"%s\">\
                                <input type=\"submit\" value=\"SHARE\">\
                                <br><br>\
                                <textarea readonly disabled name=\"code\" rows=\"20\" cols=\"80\" maxlength=\"500\">%s</textarea>\
                                </form>\n"

char *HTML_post();

void HTML_unencode(char *str);

char *HTML_field(char *str, char *field);

#endif