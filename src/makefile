
astar: astar.o list.o pile.o ouverture.o fonction_commune.o
	gcc  -o astar astar.o list.o pile.o ouverture.o fonction_commune.o

dijkstra: dijkstra.o list.o  pile.o ouverture.o fonction_commune.o
	gcc -o dijkstra dijkstra.o list.o pile.o ouverture.o fonction_commune.o

astar.o: astar.c
	gcc  -c astar.c

list.o: list.c
	gcc  -c list.c

pile.o: pile.c
	gcc  -c pile.c

ouverture.o: ouverture.c
	gcc  -c ouverture.c

fonction_commune.o: fonction_commune.c
	gcc -c fonction_commune.c

dijkstra.o: dijkstra.c
	gcc -c dijkstra.c
