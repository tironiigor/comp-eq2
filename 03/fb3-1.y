/* simplest version of calculator */
%{
#include <stdio.h>
#include <stdlib.h>
#include "fb3-1.h"

int yylex();

%}
%union {
    struct ast *a;
    int d;
}

/* declare tokens */
%token <d> NUMBER
%token ADD SUB MUL DIV ABS
%token EOL
%type <a> exp factor term

%%
calclist: /* nothing */
    | calclist exp EOL {
        prettyPrint($2);
        treefree($2);
        printf("\n> ");
    }
| calclist EOL { printf("> "); } /* blank line or a comment */
;
exp: factor
| exp '+' factor { $$ = newast('+', $1,$3); }
| exp '-' factor { $$ = newast('-', $1,$3);}
;
factor: term
| factor '*' term { $$ = newast('*', $1,$3); }
| factor '/' term { $$ = newast('/', $1,$3); }
;
term: NUMBER { $$ = newnum($1); }
| '|' term { $$ = newast('|', $2, NULL); }
| '(' exp ')' { $$ = $2; }
| '-' term { $$ = newast('M', $2, NULL); }
;
%%
