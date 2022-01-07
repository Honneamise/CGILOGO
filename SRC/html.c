//std
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//define
#define LEN_512     512

/**********/
char *HTML_post()
{
    char *method = getenv("REQUEST_METHOD");

    if(method==NULL || strcmp(method,"POST")!=0) { return NULL; }

    char *post_len_str = getenv("CONTENT_LENGTH");

    if(post_len_str==NULL) { return NULL; }
    
    int post_len = atoi(post_len_str);

    if(post_len>0) 
    { 
        char *post = calloc(LEN_512,sizeof(char));

        fgets(post, LEN_512, stdin);

        return post;
    }

    return NULL;
}

/**********/
char *HTML_get()
{
    char *method = getenv("REQUEST_METHOD");

    if(method==NULL || strcmp(method,"GET")!=0) { return NULL; }

    char *get = getenv("QUERY_STRING");

    if(get==NULL || strlen(get)<1) { return NULL; }
    
    char *_get = calloc(strlen(get)+1,sizeof(char));

    strcpy(_get,get);
    
    return _get;
}


/**********/
void HTML_unencode(char *str)
{
    if(!str){ return; };

    int len = (int)strlen(str);

    int i = 0;
    int j = 0;

    for(i=0,j=0;i<len;i++,j++)
    {
        if(str[i]=='+') { str[j]=' '; }
        else
        {
            if(str[i]=='%' && i<len-2) 
            {
                char num_str[3] = {0};
                num_str[0] = str[i+1];
                num_str[1] = str[i+2]; 

                int num = (int)strtoul(num_str, NULL, 16);

                str[j]=num;

                i+=2;
            }
            else
            {
                str[j]=str[i];
            }
        }
    }

    str[j] = 0;

}

/**********/
char *HTML_field(char *str, char *field)
{
    if(!str || !field) { return NULL; }
    
    if(strstr(str,field)==NULL) { return NULL; }

    int len = (int)strlen(field);

    char *delimiters = "&";

    char *save = NULL;

    char _str[LEN_512] = {0};

    strcpy(_str,str);

  	char *token = strtok_r(_str, delimiters, &save);

  	while(token != NULL)
    {
        if(strncmp(field,token,len)==0) 
        {
            char *buffer = calloc(strlen(token)-len+1,sizeof(char));

            strcpy(buffer,token+len);

            return buffer;
        };

        token = strtok_r(NULL, delimiters, &save);
    }

    return NULL;
}