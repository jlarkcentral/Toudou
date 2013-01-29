#ifndef TACHE_H
#define TACHE_H

#include <string>
#include <vector>

using namespace std;

class Tache
{

public:
    Tache(string uneTache);

    string getTache();
    void setTache(string uneTache);

    bool getFini();
    void setFini(bool unBool);

    string getDate();
    void setDate(string Date);

    vector<Tache> getPreconditions();

    void addPrecondition(Tache uneTache);

private:
    string tache;
    bool fini;
    string date;
    vector<Tache> preconditions;
    vector<Tache> sousTaches;
};

#endif // TACHE_H