#include "listeevenement.h"

ListeEvenement::ListeEvenement(string unTitre)
{
    titre = unTitre;
}

string ListeEvenement::getTitre()
{
    return titre;
}

void ListeEvenement::setTitre(string unTitre)
{
    titre = unTitre;
}

bool ListeEvenement::getFini()
{
    return fini;
}

void ListeEvenement::setFini(bool unBool)
{
    fini = unBool;
    for (uint i = 0; i<liste.size(); i++){
        liste.at(i).setFini(unBool);
    }
}

vector<Evenement> ListeEvenement::getListe()
{
    return liste;
}

void ListeEvenement::addEvenement(Evenement unEvenement)
{
    liste.push_back(unEvenement);
}

void ListeEvenement::delEvenement(int index)
{
    liste.erase(index);
}
