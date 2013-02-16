#include "tache.h"

using namespace std;

Tache::Tache(string uneTache)
{
    nom = uneTache;
}

string Tache::getNom()
{
    return nom;
}

void Tache::setNom(string uneTache)
{
    nom = uneTache;
}

bool Tache::getFini()
{
    return fini;
}

void Tache::setFini(bool unBool)
{
    fini = unBool;
}

string Tache::getDate()
{
    return date;
}

void Tache::setDate(string uneDate)
{
    date = uneDate;
}

vector<Tache> Tache::getPreconditions()
{
    return preconditions;
}

vector<Tache*> Tache::getSousTaches()
{
    return sousTaches;
}

void Tache::addPrecondition(Tache uneTache)
{
    preconditions.push_back(uneTache);
}

void Tache::addSousTache(Tache *uneTache)
{
    uneTache->setTacheParent(this);
    sousTaches.push_back(uneTache);
}

void Tache::delSousTache(Tache * uneTache)
{
    for(int i=0 ; i<sousTaches.size() ; i++ ){
        Tache * t = sousTaches.at(i);
        if (t==uneTache){
            sousTaches.erase(sousTaches.begin()+i);
        }
    }
}

QTreeWidgetItem* Tache::getMatchingItem()
{
    return matchingItem;
}

void Tache::setMatchingItem(QTreeWidgetItem *item)
{
    matchingItem = item;
}

Tache* Tache::getTacheParent()
{
    return tacheParent;
}

void Tache::setTacheParent(Tache *uneTache)
{
    tacheParent = uneTache;
}

void Tache::xmlToTache(TiXmlDocument doc,QTreeWidget * tree)
{
    TiXmlElement * element = doc.FirstChildElement()->FirstChildElement();

    while(element){
        this->setNom(element->Attribute("nom"));
        QTreeWidgetItem * newItem = new QTreeWidgetItem(tree->invisibleRootItem());
        tree->addTopLevelItem(newItem);
        this->setMatchingItem(newItem);
        newItem->setText(0,QString(nom.c_str()));

        parseElementToTache(element,this,newItem);
        element = element->NextSiblingElement();
    }
}

void Tache::parseElementToTache(TiXmlElement * element,Tache * tache,QTreeWidgetItem * item)
{
    TiXmlElement * elementChild = element->FirstChildElement();
    while(elementChild){

        Tache * newTache = new Tache(elementChild->Attribute("nom"));
        tache->addSousTache(newTache);
        QTreeWidgetItem * newItemChild = new QTreeWidgetItem(item);
        item->addChild(newItemChild);
        item->setText(0,QString(newTache->getNom().c_str()));
        tache->setMatchingItem(newItemChild);

        parseElementToTache(elementChild,newTache,newItemChild);

        elementChild = elementChild->NextSiblingElement();
    }
}


void Tache::createXml(string nomFichier)
{
    TiXmlDocument doc("../Toudou/xml/"+nomFichier+".xml");

    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
    doc.LinkEndChild( decl );
    TiXmlElement * firstElement = new TiXmlElement( "racine" );
    doc.LinkEndChild( firstElement );

    addTacheInXml(doc,firstElement);

    doc.SaveFile();

}

void Tache::addTacheInXml(TiXmlDocument doc,TiXmlElement * element)
{
    TiXmlElement * newElement = new TiXmlElement("tache");
    newElement->SetAttribute("nom",nom);
    newElement->SetAttribute("date",date);
    element->LinkEndChild( newElement );

    for (int i=0 ; i<sousTaches.size() ; i++){
        Tache * sousTache = sousTaches.at(i);
        sousTache->addTacheInXml(doc,newElement);
    }
}

// fonction bac a sable pour afficher - renvoie une erreur
void Tache::display()
{
    cout << nom << endl;
    for (int i=0 ; sousTaches.size() ; i++){
        Tache * t = sousTaches.at(i);
        t->display();
    }
}
