#!/bin/sh

TARGET=testBinary

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
make testBinary >> $LOG 2>&1 || fail
./$TARGET >> $LOG 2>&1 || fail
coloredEcho "OK" green


annoncer "Test binarité"
./$TARGET >> $LOG 2>&1 || fail
coloredEcho "OK" green

annoncer "Execution avec Valgrind"
valgrind --error-exitcode=43 --leak-check=full -q ./$TARGET >> $LOG 2>&1 || fail
coloredEcho "OK" green

exit 0