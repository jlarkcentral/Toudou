#ifndef TACHE_H
#define TACHE_H

#include <QTreeWidgetItem>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <QDateTime>

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

    QDateTime getDate();
    void setDate(QDateTime Date);

    vector<Tache> getPreconditions();
    void addPrecondition(Tache uneTache);

    vector<Tache *> getSousTaches();
    void addSousTache(Tache * uneTache);

    void delSousTache(Tache * uneTache);

    QTreeWidgetItem* getMatchingItem();
    void setMatchingItem(QTreeWidgetItem* item);

    Tache* getTacheParent();
    void setTacheParent(Tache* uneTache);

    //void xmlToTache(TiXmlElement *element, QTreeWidgetItem *item);
    //void parseElementToTache(TiXmlElement * element, Tache *tache,QTreeWidgetItem * item);

    void createXml(string nomFichier);
    void addTacheInXml(TiXmlDocument doc, TiXmlElement * element);

    void display();

private:
    string nom;
    bool fini;
    QDateTime date;
    QTreeWidgetItem * matchingItem;
    vector<Tache> preconditions;
    vector<Tache*> sousTaches;
    Tache * tacheParent;
};

#endif // TACHE_H
