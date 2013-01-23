#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <string>

using namespace std;

class Evenement
{
public:
    string tache;
    bool fini;

    Evenement(string uneTache);

    string getTache();
    void setTache(string uneTache);

    bool getFini();
    void setFini(bool unBool);
};

#endif // EVENEMENT_H
