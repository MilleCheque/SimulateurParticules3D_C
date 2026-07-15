# Compilateur et options de compilation
# -g pour les débug info
cc = gcc -Wall -Wextra -std=c99


EXEC = ./bin/simulateur

# Fichiers objets
OBJ = obj/main.o obj/particules.o obj/interface.o obj/environnement.o obj/distribution.o obj/optimization.o

# Première règle par convention : compilation de l'exécutable
all: $(EXEC)

# Créer le dossier bin si manquant
# -lm pour la bibliothèque mathématique
$(EXEC): $(OBJ)
	@mkdir -p bin 
	$(cc) -o $@ $^ -lm 


obj/distribution.o : src/distribution.c headers/distribution.h
	@mkdir -p obj
	$(cc) -c $< -o $@

obj/environnement.o : src/environnement.c headers/environnement.h headers/particules.h
	@mkdir -p obj
	$(cc) -c $< -o $@

obj/interface.o : src/interface.c headers/interface.h headers/environnement.h headers/particules.h
	@mkdir -p obj
	$(cc) -c $< -o $@

obj/particules.o : src/particules.c headers/particules.h
	@mkdir -p obj
	$(cc) -c $< -o $@

obj/main.o : src/main.c headers/interface.h headers/environnement.h
	@mkdir -p obj
	$(cc) -c $< -o $@

obj/optimization.o : src/optimization.c headers/optimization.h
	@mkdir -p obj
	$(cc) -c $< -o $@

obj/reproduction.o : research_18/reproduction/reproduction.c research_18/reproduction/optimization.c research_18/reproduction/optimization.h
	@mkdir -p obj
	$(cc) -c $< -o $@
	
clean :
	rm -r ./obj/*.o ./bin/*
	touch ./obj/.keep
	touch ./bin/.keep
