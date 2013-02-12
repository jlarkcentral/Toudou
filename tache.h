#ifndef TACHE_H
#define TACHE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#define TIXML_USE_STL
#include "tinyxml.h"

using namespace std;

class Tache
{

public:
    Tache(string uneTache);
    Tache();
    string getTache();
    void setTache(string uneTache);

    bool getFini();
    void setFini(bool unBool);

    string getDate();
    void setDate(string Date);

    vector<Tache> getPreconditions();

    vector<Tache> getSousTaches();

    void addPrecondition(Tache uneTache);

    void xmlToTache();
    void tacheToXml();

private:
    string tache;
    bool fini;
    string date;
    vector<Tache> preconditions;
    vector<Tache> sousTaches;
};

#endif // TACHE_H
