	TOUDOU

////// TINYXML  /////////
- changer le makefile :
LIBS  = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lQtGui -lQtCore -lpthread /usr/lib/libtinyxml.so
- tinyxml faisable automatiquement ?? 

/// idées pour rajouter des trucs (optionelles pour la plupart...)
- onglet templates
- quand la date approche, le signaler (warning)
- warning si coche la tâche 3 avant 1 et 2

- possibilité de vider les tâches effectuées
- possibilité de vider la liste courante

- distinguer les tâches à réaliser aujourd'hui (tête de liste, séparées, couleur, icône...)

- idéal : quand on coche une case, la tâche reste dans la liste, cochée. quand on rouvre l'appli, la tâche est passée dans l'onglet "Achevées" : plus besoin de la voir normalement.
A VOIR. Possibilité de faire les réglages dans les options.

/// notes sur le widget ajout :

- chez moi les boutons Ajouter/Annuler sont plus petits si on affiche pas la date ou preconditions : /
- ca plante quand on clique sur [+] preconditions puis [+] Date (quand on clique sur l'un puis sur l'autre , il faut peut etre le faire plusieurs fois pour faire apparaitre le bug)
