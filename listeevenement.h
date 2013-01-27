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
    ListeEvenement(string unTitre,string uneDate);

    vector<Evenement> getEvenements();

    void addEvenement(Evenement unEvenement);
    void delEvenement(int index);

    vector<ListeEvenement> getListes();

    void addListeEvenement(ListeEvenement uneListe);
    void delListeEvenement(int index);

    string getTitre();
    void setTitre(string unTitre);

    bool getFini();
    void setFini(bool unBool);

    string getDate();
    void setDate(string Date);

    void delEvenementsFinis();


private:
    vector<Evenement> evenements;
    vector<ListeEvenement> listes;
    string titre;
    bool fini;
    string date;
};

#endif // LISTEEVENEMENT_H
