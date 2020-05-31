# BE_MICHEL_FIE
Application domotique - Gestion automatisée d'objets connectés d'une habitation

*** Il est préférable de lire le rapport du projet avant de réaliser la simulation afin d'en comprendre le fonctionnement ainsi que certains choix d'implémentation.

Étant donné que l'application proposée est entièrement automatisée, il n'y a pas d'interaction nécessaire de la part de l'utilisateur. Seule chose que vous ayez à faire: run la simulation.
Ce README vous permettra de comprendre ce qui s'affiche lorsque vous lancer le programme.

Tout d'abord le programme s'initialise. Il peut arriver que plusieurs jours passent avant que l'affichage soit bon.
L'alarme et sa LED ainsi que le portail n'ayant pas été simulé réellement, bien que codés entièrement, ils sont affichés à l'état d'initialisation pour les deux premiers, et fermé pour le portail. 

Nous avons choisir de simuler à partir du 4ème jour de la semaine 6 pour observer le mode semaine, puis le mode week-end et enfin le mode vacances (semaine 7) en une rapide simulation. Vous observerez donc les changements au fur et à mesure des jours et non au sein des jours. Ces paramètres peuvent cependant être modifiés en ralentissant le temps de simulation.

** AFFICHAGE:

--- EXTÉRIEUR : valeurs de température et de luminosité extérieure
--- DATE : jour et semaine actuelle
--- MODE ACTIF : vacances (vacation), semaine (week) ou week-end
--- ÉTAT DES OBJETS : variant selon l'objet, le mode et l'extérieur

Étant donné que les variables globales de l'environnement extérieur simulées varient en permanence, il peut arriver que certaines valeurs s'affichent puis changent avant l'affichage de l'état des objets et peuvent ne pas correspondre. Cela dépend uniquement des paramètres de la simulation. 
Notre objectif principal étant d'avoir une overview rapide du fonctionnement du système en une simulation.
