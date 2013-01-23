#include "evenement.h"

Evenement::Evenement(string uneTache)
{
    tache = uneTache;
}

string Evenement::getTache()
{
    return tache;
}

void Evenement::setTache(string uneTache)
{
    tache = uneTache;
}

bool Evenement::getFini()
{
    return fini;
}

void Evenement::setFini(bool unBool)
{
    fini = unBool;
}
