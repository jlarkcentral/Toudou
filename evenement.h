#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <string>

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

private:
    string tache;
    bool fini;
    string date;
};

#endif // EVENEMENT_H
