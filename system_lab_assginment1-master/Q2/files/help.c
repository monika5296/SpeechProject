#include<stdio.h>
int main() 
{ 
    puts("List of Commands supported:"
        "\n\n > pwd : Prints the current working directory."
        "\n\n > mv : Used to move files from source to destination."
	"\n	 mv [source] [destination]"
	"\n\n > grep : Used to find string from a file or a path."
	"\n	grep [option] [search string] [path (optional)]"
	"\n		[options] : -c(count) -l(filename) -n(line_number) -i(case-insensitive)"
	"\n\n > split : to split the files into pieces of files"
	"\n	split [option]"
	"\n		[options] : -b(bytes) -l(lines) -n(no. of files) -d(naming convention according to digits)"
        "\n\n > exit"
        ); 
  
    return 0; 
} 
