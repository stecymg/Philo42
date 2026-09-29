# Philosophers

Implémentation en C du problème des philosophes qui dînent, avec `pthread` : plusieurs threads concurrents se disputent des ressources partagées, sous contrainte de temps réel et sans interblocage.

Projet réalisé dans le cadre du cursus **École 42 Paris** (2023).

---

## Le problème

Des philosophes sont assis autour d'une table ronde, avec une fourchette entre chaque paire de voisins. Chacun alterne entre penser, manger et dormir. Pour manger, il lui faut **les deux fourchettes adjacentes** — donc l'accord tacite de ses deux voisins.

Si chaque philosophe saisit simultanément la fourchette à sa droite, tous attendent indéfiniment celle de gauche : c'est un **interblocage**. Et si un philosophe reste trop longtemps sans manger, il meurt — la simulation s'arrête.

La difficulté tient à la conjonction des deux contraintes : éviter l'interblocage tout en garantissant qu'aucun thread ne soit privé de ressource assez longtemps pour dépasser le délai fatal.

---

## Utilisation

```bash
make
./philo <nb_philosophes> <temps_avant_mort> <temps_repas> <temps_sommeil> [nb_repas]
```

Toutes les durées sont en millisecondes. Le dernier paramètre est optionnel : s'il est fourni, la simulation s'arrête quand chaque philosophe a mangé ce nombre de fois.

```bash
./philo 5 800 200 200
./philo 4 410 200 200 10
```

Sortie : chaque changement d'état est horodaté depuis le début de la simulation.

```
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
```

---

## Choix d'implémentation

**Un thread par philosophe, un mutex par fourchette**

Chaque fourchette est un `pthread_mutex_t`. La verrouiller représente la prise de la fourchette, la déverrouiller sa reposée. Le mutex traduit directement la contrainte physique : deux voisins ne peuvent pas tenir la même fourchette au même instant.

**Décalage des philosophes impairs**

C'est la clé pour éviter l'interblocage. Si tous les threads démarrent ensemble et tentent de prendre la même fourchette, aucun ne progresse. Un décalage introduit au lancement pour les philosophes de rang impair brise cette symétrie : les paires se forment naturellement, et il reste toujours au moins un philosophe capable d'obtenir ses deux fourchettes.

**Un thread moniteur dédié**

Un thread distinct parcourt en continu l'ensemble des philosophes et compare, pour chacun, le temps écoulé depuis son dernier repas au délai fatal. Séparer la surveillance de l'exécution évite de confier à chaque philosophe le soin de vérifier sa propre mort — ce qu'il ne peut pas faire pendant qu'il dort ou attend une fourchette.

**Une attente fractionnée plutôt qu'un `usleep` unique**

`usleep` n'est pas précis et, surtout, ne peut pas être interrompu. Un philosophe endormi pendant 200 ms continuerait à afficher son état alors qu'un autre est déjà mort. L'attente est donc découpée en intervalles courts, avec vérification de l'état de la simulation entre chacun : la sortie s'arrête net à la première mort.

**Protection des données partagées**

Les états des philosophes, l'horloge de simulation et le drapeau de fin sont chacun protégés par leur propre mutex. Un verrou unique pour tout sérialiserait l'exécution et ferait perdre l'intérêt du parallélisme ; des verrous distincts limitent la contention à ce qui est réellement partagé.

**Cas particulier : un seul philosophe**

Avec une seule fourchette, aucun repas n'est possible. Ce cas est traité à part, sinon le thread resterait bloqué sur un mutex qu'aucun autre ne libérera.

---

## Organisation

```
main.c          point d'entrée
parsing.c       validation des arguments
init.c          création des threads et des mutex
philo.c         routine d'un philosophe : penser, manger, dormir
runtime.c       horloge de simulation
death.c         thread moniteur
usleep.c        attente fractionnée et interruptible
print_status.c  affichage horodaté
free_all.c      destruction des mutex et libération
error_msg.c     messages d'erreur
```

---

## Ce que le projet m'a apporté

- **Concurrence** — constater qu'un programme correct en apparence peut échouer une fois sur dix selon l'ordonnancement, et que le débogage repose sur le raisonnement plutôt que sur l'observation.
- **Interblocage** — comprendre qu'il ne se corrige pas par des verrous supplémentaires, mais en cassant la symétrie qui le rend possible.
- **Précision temporelle** — découvrir que `usleep` garantit une durée minimale, pas exacte, et qu'une contrainte temps réel impose de vérifier plutôt que de supposer.
- **Granularité des verrous** — chercher le point d'équilibre entre trop peu de mutex, qui laisse passer les accès concurrents, et trop de verrouillage, qui annule le parallélisme.
- **Séparation des responsabilités** — isoler la surveillance de l'exécution, principe qu'on retrouve dans tout système où un superviseur observe des processus qu'il ne contrôle pas.
