//Dominguez Duran Alan Axel -- 3CM12
%{
#include <stdio.h>
%}

%%
x       { return 'x'; }
,       { return ','; }
\$      { return '$'; }
\n      { /* Ignorar saltos de línea */ }
[ \t]   { /* Ignorar espacios en blanco y tabulaciones */ }
.       { /* Manejar caracteres desconocidos o errores */ }

%%

int yywrap() {
    return 1;
}
