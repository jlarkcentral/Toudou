#ifndef LISTEEVENEMENT_H
#define LISTEEVENEMENT_H

#include <string>
#include <vector>
#include <algorithm>

#include "evenement.h"

using namespace std;

class ListeEvenement
{
public:
    vector<Evenement> liste;
    string titre;
    bool fini;

    ListeEvenement(string unTitre);

    vector<Evenement> getListe();

    void addEvenement(Evenement unEvenement);
    void delEvenement(int index);

    string getTitre();
    void setTitre(string unTitre);

    bool getFini();
    void setFini(bool unBool);
};

#endif // LISTEEVENEMENT_H
