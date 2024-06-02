# <span style="color:blue">Minishell</span>
![Demo Cub3d](assets/Minishell.gif)
<span style="color:blue">Minishell</span> est un interpréteur de commandes Unix minimal écrit en C.
<span style="color:blue">Le projet a été réalisé en collaboration avec FD-Arco.</span>.

fd-arco

## <span style="color:green">Fonctionnalités</span>

<span style="color:green">Minishell</span> dispose des fonctionnalités suivantes :

- Affichage d'un invite de commande lorsque le shell attend une nouvelle commande.
- Historique de commandes fonctionnel.
- Recherche et lancement du bon exécutable (en utilisant la variable PATH ou en spécifiant un chemin relatif ou absolu).
- Gestion d'une seule variable globale pour indiquer la réception d'un signal. Cela garantit que le gestionnaire de signaux n'accédera pas à des structures de données principales.
- Non-interprétation de guillemets non fermés ou de caractères spéciaux non requis par le sujet, tels que \ (backslash) ou ; (point-virgule).
- Gestion des guillemets simples ' (single quote) pour empêcher l'interprétation des métacaractères dans la séquence citée.
- Gestion des guillemets doubles " (double quote) pour empêcher l'interprétation des métacaractères dans la séquence citée, à l'exception de $ (dollar sign).
- Mise en œuvre des redirections :
  - < redirige l'entrée.
  - > redirige la sortie.
  - << doit être suivi d'un délimiteur, puis lit l'entrée jusqu'à ce qu'une ligne contenant le délimiteur soit vue. Cependant, il n'est pas nécessaire de mettre à jour l'historique.
  - >> redirige la sortie en mode ajout.
- Mise en œuvre des pipes (|). La sortie de chaque commande dans le pipeline est connectée à l'entrée de la commande suivante via un tube.
- Gestion des variables d'environnement ($ suivi d'une séquence de caractères) qui doivent se développer en leurs valeurs.
- Gestion de $? qui doit se développer en le code de sortie de la dernière pipeline en premier plan exécutée.
- Gestion de ctrl-C, ctrl-D et ctrl-\, qui doivent se comporter comme dans bash.
- En mode interactif :
  - ctrl-C affiche un nouvel invite sur une nouvelle ligne.
  - ctrl-D quitte le shell.
  - ctrl-\ ne fait rien.
- Implémentation des commandes intégrées suivantes :
  - echo avec l'option -n
  - cd avec uniquement un chemin relatif ou absolu
  - pwd sans options
  - export sans options
  - unset sans options
  - env sans options ni arguments
  - exit sans options

## Compilation et exécution

Utilisez le fichier Makefile fourni pour compiler le projet. Les fichiers sources sont *.c et les fichiers d'en-tête sont *.h.
make
make leak
./minishell
env -i ./minishell



