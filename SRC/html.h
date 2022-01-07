#ifndef _HTML_H
#define _HTML_H



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
                    textarea { resize: none; }\
                    \
                    a { color : #000000;\
                    text-decoration : none; }"

#define HTML_HEADER "Content-type: text/html\n\n\
                    <!DOCTYPE html>\
                    <html lang=\"en\">\
                    <head>\
                    <title>%s</title>\
                    <style>" HTML_CSS "</style>\
                    </head>\
                    <body>\n"

#define HTML_FOOTER "</body></html>\n"

char *HTML_post();

char *HTML_get();

void HTML_unencode(char *str);

char *HTML_field(char *str, char *field);

#endif