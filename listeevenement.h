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
    ListeEvenement(string unTitre);
    ~ListeEvenement();

    vector<Evenement> getListe();

    void addEvenement(Evenement unEvenement);
    void delEvenement(int index);

    string getTitre();
    void setTitre(string unTitre);

    bool getFini();
    void setFini(bool unBool);

    string getDate();
    void setDate(string Date);


private:
    vector<Evenement> liste;
    string titre;
    bool fini;
    string date;
};

#endif // LISTEEVENEMENT_H
