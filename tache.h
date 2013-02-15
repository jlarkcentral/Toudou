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
    string getNom();
    void setNom(string uneTache);

    bool getFini();
    void setFini(bool unBool);

    string getDate();
    void setDate(string Date);

    vector<Tache> getPreconditions();
    void addPrecondition(Tache uneTache);

    vector<Tache> getSousTaches();
    void addSousTache(Tache uneTache);

    void xmlToTache();
    void createXml();

    void addTacheInXml(TiXmlDocument doc, TiXmlElement *element);

    void display();

private:
    string nom;
    bool fini;
    string date;
    vector<Tache> preconditions;
    vector<Tache> sousTaches;
};

#endif // TACHE_H
