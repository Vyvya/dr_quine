#include <stdio.h>

void print_source(char *quine) {
    printf(quine, 10, 10, 10, 10, 10, 10, 47, 47, 10, 10, 47, 47, 10, 34, 35, quine, 34, 10, 10, 10, 10);
}

//Quine program
int main() {
    //First line to print
    char *quine = "#%cinclude <stdio.h>%c%cvoid print_source(char *quine) {%c   printf();%c}%c%c%c%cQuine program%cint main() {%c    %c%cFirst line to print%c    char *quine = %c%s%c;%c    print_source(quine);%c    return 0;%c}%c%c";
    print_source(quine);
    return 0;
}

//%c%c%c{%c%c}%c%c /n
//%c%c //
//%c /n
//

//10, 10, 10, 10, 10, 10, 10, 47, 47, 10, 10, 47, 47, 10, 34, quine, 34, 10, 10, 10, 10