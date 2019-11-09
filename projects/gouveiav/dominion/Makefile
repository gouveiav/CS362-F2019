CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testdrawcard -g  testdrawcard.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc  -o unittest1Baron -g  unittest1.c dominion.o rngs.o $(CFLAGS)
unittest2: unittest2.c dominion.o rngs.o
	gcc  -o unittest2Minion -g  unittest2.c dominion.o rngs.o $(CFLAGS)
unittest3: unittest3.c dominion.o rngs.o
	gcc  -o unittest3Ambassador -g  unittest3.c dominion.o rngs.o $(CFLAGS)
unittest4: unittest4.c dominion.o rngs.o
	gcc  -o unittest4Tribute -g  unittest4.c dominion.o rngs.o $(CFLAGS)
unittest5: unittest5.c dominion.o rngs.o
	gcc  -o unittest5Mine -g  unittest5.c dominion.o rngs.o $(CFLAGS)

unittestresults: unittest1 unittest2 unittest3 unittest4 unittest5
	./unittest1Baron &> unittestresults.out
	./unittest2Minion &> unittestresults.out
	./unittest3Ambassador &> unittestresults.out
	./unittest4Tribute &> unittestresults.out
	./unittest5Mine &> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> testDrawResult.out
	gcov dominion.c >> testDrawResult.out
	cat dominion.c.gcov >> testDrawResult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f unittest1Baron unittest2Minion unittest3Ambassador unittest4Tribute unittest5Mine
