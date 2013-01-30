#include "tache.h"

Tache::Tache(string uneTache)
{
    tache = uneTache;
}

string Tache::getTache()
{
    return tache;
}

void Tache::setTache(string uneTache)
{
    tache = uneTache;
}

bool Tache::getFini()
{
    return fini;
}

void Tache::setFini(bool unBool)
{
    for (int i = 0; i < preconditions.size() ;i++){
        if (!preconditions.at(i).getFini()){
            return;
        }
    }
    fini = unBool;
}

string Tache::getDate()
{
    return date;
}

void Tache::setDate(string uneDate)
{
    date = uneDate;
}

vector<Tache> Tache::getPreconditions()
{
    return preconditions;
}

void Tache::addPrecondition(Tache uneTache)
{
    preconditions.push_back(uneTache);
}
