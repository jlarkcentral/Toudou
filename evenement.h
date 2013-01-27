#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <string>
#include <vector>

using namespace std;

class Evenement
{

public:
    Evenement(string uneTache, string uneDate);

    string getTache();
    void setTache(string uneTache);

    bool getFini();
    void setFini(bool unBool);

    string getDate();
    void setDate(string Date);

    vector<Evenement> getPrecondition();

    void addPrecondition(Evenement unEvenement);

private:
    string tache;
    bool fini;
    string date;
    vector<Evenement> precondition;
};

#endif // EVENEMENT_H
