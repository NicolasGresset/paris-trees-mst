#include "../include/manageSIGINT.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigIntitialise(sigset_t *masked, sigset_t *old) {

  printf("^C will be taken into account when finishing to write in the binary "
         "file.\n");

  sigemptyset(masked);       // initialise le set masked (vide)
  sigaddset(masked, SIGINT); // ajoute SIGINT au set masked
  sigprocmask(SIG_SETMASK, masked,
              old); // met ce qu'il y avait dans masked dans old
}

void sigHandle(struct sigaction *ignore, sigset_t *pending, sigset_t *old) {

  struct sigaction saved;

  sigpending(pending); // ajoute tous les signaux (ici SIGINT) en attente dans
                       // le set pending

  sigemptyset(
      &ignore->sa_mask); // initialise le set sa_mask de la structure ignore
  ignore->sa_flags = 0;

  sigaction(SIGINT, ignore,
            &saved); // donne nouveau comportement après ^C d'après ignore et
                     // stocke l'ancien dans sauvegarde

  sigprocmask(SIG_SETMASK, old, 0); // retour au comportemetn normal
  ignore->sa_handler = SIG_IGN;

  sigaction(SIGINT, &saved, 0); // reprend l'ancien comportement
}