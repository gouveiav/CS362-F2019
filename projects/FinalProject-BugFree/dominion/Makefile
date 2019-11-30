CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testdrawcard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testdrawcard.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc  -o unittest1Bug1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
unittest2: unittest2.c dominion.o rngs.o
	gcc  -o unittest2Bug2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
unittest3: unittest3.c dominion.o rngs.o
	gcc  -o unittest3Bug3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
unittest4: unittest4.c dominion.o rngs.o
	gcc  -o unittest4Bug4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
unittest5: unittest5.c dominion.o rngs.o
	gcc  -o unittest5Bug5 -g  unittest5.c dominion.o rngs.o $(CFLAGS)
unittest6: unittest6.c dominion.o rngs.o
	gcc  -o unittest6Bug6 -g  unittest6.c dominion.o rngs.o $(CFLAGS)
unittest7: unittest7.c dominion.o rngs.o
	gcc  -o unittest7Bug7 -g  unittest7.c dominion.o rngs.o $(CFLAGS)
unittest8: unittest8.c dominion.o rngs.o
	gcc  -o unittest8Bug8 -g  unittest8.c dominion.o rngs.o $(CFLAGS)
unittest9: unittest9.c dominion.o rngs.o
	gcc  -o unittest9Bug9 -g  unittest9.c dominion.o rngs.o $(CFLAGS)
unittest10: unittest10.c dominion.o rngs.o
	gcc  -o unittest10Bug10 -g  unittest10.c dominion.o rngs.o $(CFLAGS)

unittestresults: unittest1 unittest2 unittest3 unittest4 unittest5 unittest6 unittest7 unittest8 unittest9 unittest10
	./unittest1Bug1 >> unittestresults.out
	./unittest2Bug2 >> unittestresults.out
	./unittest3Bug3 >> unittestresults.out
	./unittest4Bug4 >> unittestresults.out
	./unittest5Bug5 >> unittestresults.out
	./unittest6Bug6 >> unittestresults.out
	./unittest7Bug7 >> unittestresults.out
	./unittest8Bug8 >> unittestresults.out
	./unittest9Bug9 >> unittestresults.out
	./unittest10Bug10 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f unittest1Bug1 unittest2Bug2 unittest3Bug3 unittest4Bug4 unittest5Bug5 unittest6Bug6
	rm -f unittest7Bug7 unittest8Bug8 unittest9Bug9 unittest10Bug10
