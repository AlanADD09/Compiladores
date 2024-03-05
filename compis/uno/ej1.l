
   int num_lineas = 0, num_caracteres = 0;
%option noyywrap

%%
\n      ++num_lineas; ++num_caracteres;
.       ++num_caracteres;

%%
int main()
{
  yylex();
  printf( "# de lineas = %d, # de caracteres. = %d\n",
  num_lineas, num_caracteres );
}

