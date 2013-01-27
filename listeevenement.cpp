#include "listeevenement.h"

ListeEvenement::ListeEvenement(string unTitre, string uneDate)
{
    titre = unTitre;
    date = uneDate;
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
    for (uint i = 0; i<evenements.size(); i++){
        evenements.at(i).setFini(unBool);
    }
}

vector<Evenement> ListeEvenement::getEvenements()
{
    return evenements;
}

void ListeEvenement::addEvenement(Evenement unEvenement)
{
    evenements.push_back(unEvenement);
}

void ListeEvenement::delEvenement(int index)
{
    //liste.erase(index);
}

vector<ListeEvenement> ListeEvenement::getListes()
{
    return listes;
}

void ListeEvenement::addListeEvenement(ListeEvenement uneListe)
{
    listes.push_back(uneListe);
}

void ListeEvenement::delListeEvenement(int index)
{
    //liste.erase(index);
}

string ListeEvenement::getDate()
{
    return date;
}

void ListeEvenement::setDate(string uneDate)
{
    date = uneDate;
}

void ListeEvenement::delEvenementsFinis()
{
    for(vector<Evenement>::iterator it = evenements.begin(); it != evenements.end(); ++it) {

    }
}
