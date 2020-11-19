#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "fb3-1.h"

struct ast *
newast(int nodetype, struct ast *l, struct ast *r)
{
    struct ast *a = malloc(sizeof(struct ast));
    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}
struct ast *
newnum(int d)
{
    struct numval *a = malloc(sizeof(struct numval));
    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'K';
    a->number = d;
    return (struct ast *)a;
}

void prettyPrint(struct ast *a)
{
    switch (a->nodetype)
    {
    case 'K':
        printf("[%d]", ((struct numval *) a)->number);
        break;
    case '+':
        printf("[ADD ");
        prettyPrint(a->l);
        printf(" ");
        prettyPrint(a->r);
        printf("]");
        break;
    case '-':
        printf("[SUB ");
        prettyPrint(a->l);
        printf(" ");
        prettyPrint(a->r);
        printf("]");
        break;
    case '*':
        printf("[MUL ");
        prettyPrint(a->l);
        printf(" ");
        prettyPrint(a->r);
        printf("]");
        break;
    case '/':
        printf("[DIV ");
        prettyPrint(a->l);
        printf(" ");
        prettyPrint(a->r);
        printf("]");
        break;
    case '|':
        printf("[OR ");
        prettyPrint(a->l);
        printf(" ");
        prettyPrint(a->r);
        printf("]");
        break;
    case 'M':
        printf("[ABS ");
        prettyPrint(a->l);
        printf("]");
        break;
    default:
        printf("internal error: bad node %c\n", a->nodetype);
    }
}

void treefree(struct ast *a)
{
    switch (a->nodetype)
    {
    /* two subtrees */
    case '+':
    case '-':
    case '*':
    case '/':
        treefree(a->r);
    /* one subtree */
    case '|':
    case 'M':
        treefree(a->l);
    /* no subtree */
    case 'K':
        free(a);
        break;
    default:
        printf("internal error: free bad node %c\n", a->nodetype);
    }
}

void yyerror(char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}
int main()
{
    printf("> ");
    return yyparse();
}
