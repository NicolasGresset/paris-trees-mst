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
make clean
make
coloredEcho "OK" green

annoncer "test correspondance genre - identifiant"
./$TARGET -i inpath -o out -c save >> $LOG 2>&1
./testCorres >> $LOG 2>&1  || fail

coloredEcho "OK" green

annoncer "Execution avec Valgrind"
valgrind ./testCorres >> $LOG 2>&1  || fail

coloredEcho "OK" green


exit 0