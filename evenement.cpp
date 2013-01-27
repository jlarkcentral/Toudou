#include "evenement.h"

Evenement::Evenement(string uneTache, string uneDate)
{
    tache = uneTache;
    date = uneDate;
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

string Evenement::getDate()
{
    return date;
}

void Evenement::setDate(string uneDate)
{
    date = uneDate;
}

vector<Evenement> Evenement::getPrecondition()
{
    return precondition;
}

void Evenement::addPrecondition(Evenement unEvenement)
{
    precondition.push_back(unEvenement);
}
