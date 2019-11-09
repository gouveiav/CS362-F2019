#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	
	int space = 32;
	int lParen = 40;
	int rParen = 41;
	int MAX = 125;//== }
	int MIN = 91;
	//pick a number 1-10
	int choice = (rand() % (15 - 1 + 1) + 1);
	//this covers the a-z plus a few brackets
	char c = ((char)(rand() % (MAX - MIN + 1) + MIN));
	//printf("char testing \"%c\"\n", c);

	if (choice == 1) {
		//printf("return choice 1= '%c'\n", (char)space);
		return (char)space;
	}
	else if(choice ==2) {
		//printf("return choice 2= '%c'\n", (char)lParen);
		return (char)lParen;
	}
	else if (choice == 3) {
		//printf("return choice 3= '%c'\n", (char)rParen);

		return (char)rParen;
	}
	else {
		//printf("else return c= '%c'\n", c);
		return c;
	}

}

char *inputString()
{
	char buffer[6] = {'\0' };
	int i;
	for (i = 0; i < 5; i++) {
		buffer[i] = ((char)(rand() % (117 - 100 + 1) + 100));
	}
    return buffer;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
		
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
