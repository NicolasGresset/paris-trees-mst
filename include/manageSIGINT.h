#pragma once
#include <signal.h>
#include <unistd.h>

void sigIntitialise(sigset_t *masked, sigset_t *old);

void sigHandle(struct sigaction *ignore, sigset_t *pending, sigset_t *old);