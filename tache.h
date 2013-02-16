#ifndef TACHE_H
#define TACHE_H

#include <QTreeWidgetItem>

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

    vector<Tache *> getSousTaches();
    void addSousTache(Tache * uneTache);

    QTreeWidgetItem* getMatchingItem();
    void setMatchingItem(QTreeWidgetItem* item);

    void xmlToTache();
    void createXml(string nomFichier);

    void addTacheInXml(TiXmlDocument doc, TiXmlElement * element);

    void display();

private:
    string nom;
    bool fini;
    string date;
    QTreeWidgetItem * matchingItem;
    vector<Tache> preconditions;
    vector<Tache*> sousTaches;
};

#endif // TACHE_H
