	TOUDOU

////// TINYXML  /////////

- changer le makefile :

LIBS  = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lQtGui -lQtCore -lpthread /usr/lib/libtinyxml.so

- faisable automatiquement ?? 


	
- Ouverture d'une liste de tâches avec double-clic (onglet?)
- Bouton Nouveau, puis proposition : tâche simple, liste, liste ordonnée, template
- Les options s'affichent au fur et à mesure des choix
	-> nom
	-> racine
	-> type ?
		tâche :			autres :
		-> date			-> ouvre l'arborescence de la nouvelle liste
		(absolue
		ou relative)
- Onglets Toutes les tâches, tâches effectuées, templates?, listes cliquées
- Dans l'écran des templates, bouton : créer une liste à partir de ce template
- Case à cocher
- Affichage des dates ?
- Menu Affichage avec plein de réglages
	-> dates ?
	-> priorité ?
	-> onglet templates
- quand la date approche, le signaler (warning)
- top moumoute : alertes
- essayer de trier par dates (possibilité de changer dans le menu)
- une tâche = un nom + une liste (ordonnée) de sous-tâches
	-> si liste vide : tâche simple
	-> sinon liste/liste ordonnée/template
	-> possibilité de rajouter un attribut type pour aller + vite
- logo tout doux + icône appli
- warning si coche la tâche 3 avant 1 et 2, + phrase rouge dans le recap
- limiter le nb de caracteres pour le nom, si + d'info mettre dans les notes
- possibilité de vider les tâches effectuées

- rajout d'une barre de progression pour les listes de tâches
- distinguer les tâches à réaliser aujourd'hui (tête de liste, séparées, couleur, icône...)

- idéal : quand on coche une case, la tâche reste dans la liste, cochée. quand on rouvre l'appli, la tâche est passée dans l'onglet "Achevées" : plus besoin de la voir normalement.
A VOIR. Possibilité de faire les réglages dans les options.

////

PLUS RETENUS :
- Tiroir à droite de la fenêtre pour créer/modifier
- Recap d'une tâche en cliquant 1 fois dessus + bouton Editer
- attribut tache : parent. Quand on ajoute une sous-tache, il faut lui préciser sa tache parente (peut être utile pour l'affichage des informations ?)
=> INUTILE car plus d'affichage infos
- Bouton retour à toutes les tâches
- possibilité de transformer une tâche simple en liste : dans le tiroir d'édition, bouton "ajouter sous-tâche" avec un linedit "Nouvelle tâche" et le tiroir s'actualise sur cette nouvelle tâche en question


A FAIRE CE WEEK END :

- Fenetre d'ajout finie avec ajout des preconditions, fignolage de la fenetre
- Transfert des taches "topLevel" (les taches primaires dans l'arbre) dans l'onglet Achevées une fois cochées
- Warning lorsqu'on coche une tache alors que certaines sous taches ou preconditions ne sont aps cochées (on peut peut etre considérer les sous taches comme faisant partie des preconditions)
- sauvegarde et chargement de liste en XML
- sauvegarde automatique de la liste courante dans un backup.xml, avec lequel l'application s'ouvre.
- Barre de menus (Fichier, Affichage...) avec les fonctions possibles de l 'appli