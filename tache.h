#ifndef TACHE_H
#define TACHE_H

#include <QTreeWidgetItem>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <QDate>

#define TIXML_USE_STL
#include "tinyxml.h"

using namespace std;

class Tache
{

public:
    Tache(string uneTache);
    Tache(QTreeWidgetItem *item, bool withSousTaches);
    string getNom();
    void setNom(string uneTache);

    bool getFini();
    void setFini(bool unBool);

    int getDate();
    void setDate(int i);

    QDate getDateabs();
    void setDateabs(QDate Date);

    string getDaterel();
    void setDaterel(string s);

    vector<Tache> getPreconditions();
    void setPreconditions(vector<Tache> pr);
    void addPrecondition(Tache uneTache);

    vector<Tache *> getSousTaches();
    void addSousTache(Tache * uneTache);

    void delSousTache(Tache * uneTache);

    QTreeWidgetItem* getMatchingItem();
    void setMatchingItem(QTreeWidgetItem* item);

    Tache* getTacheParent();
    void setTacheParent(Tache* uneTache);

    // Pour les tests
    void afficherPreconds();

    //void xmlToTache(TiXmlElement *element, QTreeWidgetItem *item);
    //void parseElementToTache(TiXmlElement * element, Tache *tache,QTreeWidgetItem * item);

    void createXml(string nomFichier);
    void addTacheInXml(TiXmlElement *element);
    void addTacheInXmlTemplate(TiXmlDocument doc,TiXmlElement * element);

private:
    string nom;
    bool fini;
    int date;   // 1 si date absolue, 2 si date relative, 3 si aucune date. Par dfaut : aucune date.
    QDate dateabs;
    string daterel;
    QTreeWidgetItem * matchingItem;
    vector<Tache> preconditions;
    vector<Tache*> sousTaches;
    Tache * tacheParent;
};

#endif // TACHE_H
