#!/bin/sh

TARGET=arbres

#
# Ce placer dans le répertoire courant
#
TESTDIR="$(cd "$(dirname "$0}")" && pwd)"
cd "$TESTDIR"

#
# Conserver une trace de toutes les actions
#
LOG="test.log"
rm -f "$LOG"
touch "$LOG"

#
# Importer les fonctions communes à tous les tests
#
. ./fonctions.sh

#
# Compilation du programme.
#

annoncer "Compilation"
make clean >> $LOG 2>&1 || fail
make >> $LOG 2>&1 || fail
coloredEcho "OK" green

annoncer "test fichier entrée inexistant"

./$TARGET -i "fichier inexistant" -o out -c save >> $LOG 2>&1 
if [ $? -ne 42 ]; then
  fail
fi
coloredEcho "OK" green

annoncer "test fichier sortie inexistant"

./$TARGET -i in -o "fichier inexistant" -c save >> $LOG 2>&1 
if [ $? -ne 42 ]; then
  fail
fi
coloredEcho "OK" green


exit 0