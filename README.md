	TOUDOU

////// TINYXML  /////////
- changer le makefile :
LIBS  = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lQtGui -lQtCore -lpthread /usr/lib/libtinyxml.so
- tinyxml faisable automatiquement ?? 

/// idées pour rajouter des trucs (optionelles pour la plupart...)
- templates dispo dans l ajout
- quand la date approche, le signaler (warning)
- warning si coche la tâche 3 avant 1 et 2 <=> preconditions

- distinguer les tâches à réaliser aujourd'hui (tête de liste, séparées, couleur, icône...)

- trier la liste par Date

- idéal : quand on coche une case, la tâche reste dans la liste, cochée. quand on rouvre l'appli, la tâche est passée dans l'onglet "Achevées" : plus besoin de la voir normalement.
A VOIR. Possibilité de faire les réglages dans les options.

