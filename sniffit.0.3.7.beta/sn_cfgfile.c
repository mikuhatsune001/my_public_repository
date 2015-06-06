/* Sniffit Cfgfile source file                                            */
/*   - by          : Brecht Claerhout                                     */
/*   - improvements: Shudoh Kazuyuki                                      */

#include <stdio.h>
#include <netdb.h>	                           /* for getservbyname() */

#include "sn_config.h"
#include "sn_defines.h"
#include "sn_structs.h"
#include "sn_cfgfile.h"           
#include "sn_resolv.h"
/* #include "sn_generation.h" */

extern struct cfg_file_contense *select_from_list; /* pointers for cfg lists */ 
extern struct cfg_file_contense *select_to_list;
extern struct cfg_file_contense *deselect_from_list;
extern struct cfg_file_contense *deselect_to_list;

extern int select_from_length;               /* length of cfg lists  */ 
extern int select_to_length;
extern int deselect_from_length;
extern int deselect_to_length;
extern int Priority;        /* The higher the priority, the more important */
extern char dot_notation[20];                       /* for easy working, Q&D */
extern char Logfile[250];                                                              

void clear_list_buffer (struct cfg_file_contense *help)
{
help->host[0]=0;
help->priority=0;
help->port=0;
help->wildcard=0;
}

struct cfg_file_contense *adjust_select_from_list (void)
{
Priority++;
select_from_length++; 

if(select_from_list==NULL)
     {
     select_from_list=(struct cfg_file_contense *)malloc(sizeof(struct cfg_file_contense));
     }
else {
     select_from_list=(struct cfg_file_contense *)realloc(select_from_list,
			select_from_length*sizeof(struct cfg_file_contense));
     }
if(select_from_list==NULL)
	{printf("Sniffit hartattack... out of memory!\n"); exit(1);}
clear_list_buffer(&(select_from_list[select_from_length-1])); 
return &(select_from_list[select_from_length-1]); 
}

struct cfg_file_contense *adjust_select_to_list (void)
{
Priority++;
select_to_length++; 

if(select_to_list==NULL)
     {
     select_to_list=(struct cfg_file_contense *)malloc(sizeof(struct cfg_file_contense));
     }
else
     {
     select_to_list=(struct cfg_file_contense *)realloc(select_to_list,
			select_to_length*sizeof(struct cfg_file_contense));
     };
if(select_to_list==NULL)
	{printf("Sniffit hartattack... out of memory!\n"); exit(1);}
clear_list_buffer(&(select_to_list[select_to_length-1]));
return &(select_to_list[select_to_length-1]);
}

struct cfg_file_contense *adjust_deselect_from_list (void)
{
Priority++;
deselect_from_length++; 
if(deselect_from_list==NULL)
     {
     deselect_from_list=(struct cfg_file_contense *)malloc(sizeof(struct cfg_file_contense));
     }
else
     {
     deselect_from_list=(struct cfg_file_contense *)realloc(deselect_from_list,
			deselect_from_length*sizeof(struct cfg_file_contense));
     }
if(deselect_from_list==NULL)
	{printf("Sniffit hartattack... out of memory!\n"); exit(1);}
clear_list_buffer(&(deselect_from_list[deselect_from_length-1]));
return (&(deselect_from_list[deselect_from_length-1]));
}

struct cfg_file_contense *adjust_deselect_to_list (void)
{
Priority++;
deselect_to_length++; 

if(deselect_to_list==NULL)
     {
     deselect_to_list=(struct cfg_file_contense *)malloc(sizeof(struct cfg_file_contense));
     }
else
     {
     deselect_to_list=(struct cfg_file_contense *)realloc(deselect_to_list,
			deselect_to_length*sizeof(struct cfg_file_contense));
     }
if(deselect_to_list==NULL)
	{printf("Sniffit hartattack... out of memory!\n"); exit(1);}
clear_list_buffer(&(deselect_to_list[deselect_to_length-1]));
return &(deselect_to_list[deselect_to_length-1]);
}

char *clean_string (char *string)
{
char help[20];
int i, j;

j=0;
for(i=0;i<strlen(string);i++)
	{
	if( (isalnum(string[i]))||(string[i]=='.') )
		{
		help[j]=string[i];
		help[j+1]=0;
		}
	j++;
	}
strcpy(string, help);
return string;
}

char *clean_filename (char *string)
{
char help[20];
int i, j;

j=0;
for(i=0;i<strlen(string);i++)
	{
	if( !(iscntrl(string[i])) && !(isspace(string[i])) )
		{
		help[j]=string[i];
		help[j+1]=0;
		}
	j++;
	}
strcpy(string, help);
return string;
}

void make_nr_dot (char *host)
{
_32_bit hostnr;
unsigned char *digit;
char help[255];

strcpy(help, host);
clean_string(help);
hostnr=getaddrbyname(help);
digit=(char *)&hostnr;
sprintf(dot_notation,"%u.%u.%u.%u",digit[0],digit[1],digit[2],digit[3]);
}

static int make_portno(char *servname)             /* by Shudoh Kazuyuki */ 
{
struct servent *ent = NULL;
int ret = 0;
char *buf;
int namelen;

buf = strdup(servname);
namelen = strlen(buf) - 1;
if (buf[namelen] == '\n') 
  {buf[namelen] = '\0';}

setservent(0 /*false*/);
ent = getservbyname(buf, "tcp");

if (ent) 
  {ret = (int)ntohs((unsigned short)ent->s_port);}
else 
  {ret = atoi(buf);}

free(buf);

if (ret <= 0) 
  {
  printf("Invalid port no or service name in config file: %s\n", servname);
  exit(1);
  }

return ret;
}

void interprete_line (char *line)
{
struct cfg_file_contense *help, *helpp; 
char *field;
size_t i;

field=strtok(line," ");
if(field!=NULL)
	{
	/* comment line */
	if(*field == '#')  return;
	if(*field == ';')  return;

	strlower(field);
	if(strcmp(strlower(field),"logfile")==0)
	  {
	  field=clean_filename(strtok(NULL," "));
     	  if(field != NULL) strcpy(Logfile,field);
	  }
	else if(strcmp(strlower(field),"select")==0)
	  {
	  field=strtok(NULL," ");
          if(strcmp(strlower(field),"from")==0)
	    {
            field=strtok(NULL," ");
            if(strcmp(strlower(field),"host")==0)  /* select from host */
	      {
	      help=adjust_select_from_list();
              make_nr_dot(strtok(NULL," "));
              strcpy(help->host,dot_notation);
              if( (field=strtok(NULL," "))!=NULL) 
			help->port=make_portno(field);
	      help->priority=Priority;
              return;
 	      }
            if(strcmp(strlower(field),"port")==0)  /* select from port */
	      {                           
	      help=adjust_select_from_list();
	      help->port=make_portno( strtok(NULL," ") ); 
	      help->priority=Priority;
	      return;
	      }
            if(strcmp(strlower(field),"mhosts")==0)  /* select from mhosts */
	      {
	      help=adjust_select_from_list();
	      strcpy(help->host, clean_string(strtok(NULL," ")));
	      if( (field=strtok(NULL," "))!=NULL)
			help->port=make_portno(field);
	      help->priority=Priority;
	      help->wildcard=1;
 	      return;
	      }
 	    }
          if(strcmp(strlower(field),"to")==0)
	    {
            field=strtok(NULL," ");
            if(strcmp(strlower(field),"host")==0)  /* select to host */
	      {
	      help=adjust_select_to_list();
              make_nr_dot(strtok(NULL," "));
	      strcpy(help->host,dot_notation);
	      if( (field=strtok(NULL," "))!=NULL)
			help->port=make_portno(field);
	      help->priority=Priority;
              return;
 	      }
            if(strcmp(strlower(field),"port")==0)  /* select to port */
	      {                           
	      help=adjust_select_to_list();
	      help->port=make_portno( strtok(NULL," ") ); 
	      help->priority=Priority;
              return;
 	      }
            if(strcmp(strlower(field),"mhosts")==0)  /* select to mhosts */
	      {                           
	      help=adjust_select_to_list();
	      strcpy(help->host, clean_string(strtok(NULL," ")));
	      if( (field=strtok(NULL," "))!=NULL)
			help->port=make_portno(field);
	      help->priority=Priority;
	      help->wildcard=1;
              return;
 	      }
 	    }
          if(strcmp(strlower(field),"both")==0)
	    {
            field=strtok(NULL," ");
            if(strcmp(strlower(field),"host")==0)  /* select both host */
	      {
	      help=adjust_select_from_list();
	      helpp=adjust_select_to_list();
              make_nr_dot(strtok(NULL," "));
	      strcpy(help->host,dot_notation);
	      strcpy(helpp->host,dot_notation);
	      if( (field=strtok(NULL," "))!=NULL)
			{help->port=make_portno(field); helpp->port=make_portno(field);}
	      help->priority=Priority;
 	      helpp->priority=Priority;
              return;
	      }
            if(strcmp(strlower(field),"port")==0)  /* select both port */
	      {                           
	      help=adjust_select_from_list();
	      helpp=adjust_select_to_list();
	      field=strtok(NULL," "); 
	      help->port=make_portno(field); 
	      helpp->port=make_portno(field); 
	      help->priority=Priority;
	      helpp->priority=Priority;
              return;
 	      }
            if(strcmp(strlower(field),"mhosts")==0)  /* select both mhosts */
	      {                           
	      help=adjust_select_from_list();
	      helpp=adjust_select_to_list();
	      field=clean_string(strtok(NULL," "));
	      strcpy(help->host, field);
	      strcpy(helpp->host, field);
	      if( (field=strtok(NULL," "))!=NULL)
			{help->port=make_portno(field); helpp->port=make_portno(field);}
	      help->priority=Priority;
	      helpp->priority=Priority;
 	      help->wildcard=1;
	      helpp->wildcard=1;
              return;
	      }
 	    }
	  }
	if(strcmp(strlower(field),"deselect")==0)
	  {
	  field=strtok(NULL," ");
          if(strcmp(strlower(field),"from")==0)
	    {
            field=strtok(NULL," ");
            if(strcmp(strlower(field),"host")==0)  /* select from host */
	      {
	      help=adjust_deselect_from_list();
              make_nr_dot(strtok(NULL," "));
	      strcpy(help->host,dot_notation);
	      if( (field=strtok(NULL," "))!=NULL)
			help->port=make_portno(field);
	      help->priority=Priority;
              return;
 	      }
            if(strcmp(strlower(field),"port")==0)  /* select from port */
	      {
	      help=adjust_deselect_from_list();
	      help->port=make_portno(strtok(NULL," ")); 
	      help->priority=Priority;
              return;
 	      }
            if(strcmp(strlower(field),"mhosts")==0)  /* select from mhosts */
	      {                           
	      help=adjust_deselect_from_list();
	      strcpy(help->host, clean_string(strtok(NULL," ")));
	      if( (field=strtok(NULL," "))!=NULL)
			help->port=make_portno(field);
	      help->priority=Priority;
 	      help->wildcard=1;
              return;
 	      }
 	    }
          if(strcmp(strlower(field),"to")==0)
	    {
            field=strtok(NULL," ");
            if(strcmp(strlower(field),"host")==0)  /* deselect to host */
	      {
	      help=adjust_deselect_to_list();
              make_nr_dot(strtok(NULL," "));
	      strcpy(help->host,dot_notation);
	      if( (field=strtok(NULL," "))!=NULL)
			help->port=make_portno(field);
	      help->priority=Priority;
              return;
 	      }
            if(strcmp(strlower(field),"port")==0)  /* deselect to port */
	      {                           
	      help=adjust_deselect_to_list();
	      help->port=make_portno(strtok(NULL," ")); 
	      help->priority=Priority;
              return;
 	      }
            if(strcmp(strlower(field),"mhosts")==0)  /* deselect to mhosts */
	      {                           
	      help=adjust_deselect_to_list();
	      strcpy(help->host, clean_string(strtok(NULL," ")));
	      if( (field=strtok(NULL," "))!=NULL)
			help->port=make_portno(field);
	      help->priority=Priority;
 	      help->wildcard=1;
              return;
	      }
 	    }
          if(strcmp(strlower(field),"both")==0)
	    {
            field=strtok(NULL," ");
            if(strcmp(strlower(field),"host")==0)  /* deselect both host */
	      {
	      help=adjust_deselect_from_list();
	      helpp=adjust_deselect_to_list();
              make_nr_dot(strtok(NULL," "));
	      strcpy(help->host,dot_notation);
	      strcpy(helpp->host,dot_notation);
	      if( (field=strtok(NULL," "))!=NULL)
			{helpp->port = help->port = make_portno(field);}
	      help->priority=Priority;
	      helpp->priority=Priority;
              return;
 	      }
            if(strcmp(strlower(field),"port")==0)  /* deselect both port */
	      {                           
	      help=adjust_deselect_from_list();
	      helpp=adjust_deselect_to_list();
	      field=strtok(NULL," "); 
	      helpp->port = help->port = make_portno(field); 
	      help->priority=Priority;
	      helpp->priority=Priority;
              return;
	      }
            if(strcmp(strlower(field),"mhosts")==0)  /* deselect both mhosts */
	      {                           
	      help=adjust_deselect_from_list();
	      helpp=adjust_deselect_to_list();
	      field=clean_string(strtok(NULL," "));
	      strcpy(help->host, field);
	      strcpy(helpp->host, field);
	      if( (field=strtok(NULL," "))!=NULL)
			{help->port=make_portno(field); helpp->port=make_portno(field);}
	      help->priority=Priority;
	      helpp->priority=Priority;
 	      help->wildcard=1;
 	      helpp->wildcard=1;
              return;
 	      }
 	    }
 	  }
	}
}

void read_cfg_file (char *file)
{
FILE *cfgfile;
size_t line_length;
char lineptr[260];

select_from_list=NULL; select_to_list=NULL;
deselect_from_list=NULL; deselect_to_list=NULL;
Priority=0;

if((cfgfile = fopen(file,"r"))==NULL)
	{fprintf(stderr,"Couldn't find config file... giving up.\n"); exit(1);}
while(feof(cfgfile)==0)
	{
	fgets(lineptr,259,cfgfile);
        if(feof(cfgfile)==0)
	   {
	   interprete_line(lineptr);}
	}
fclose(cfgfile);
};
