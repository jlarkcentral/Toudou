#include "tache.h"

using namespace std;

Tache::Tache(string uneTache)
{
    nom = uneTache;
}

Tache::Tache(QTreeWidgetItem *item,bool withSousTaches)
{
    nom = item->text(0).toStdString();
    daterel = item->text(1).toStdString();
    if(withSousTaches){
        for(int i=0 ; i<item->childCount() ; i++){
        Tache * st = new Tache(item->child(i),withSousTaches);
        this->addSousTache(st);
        }
    }

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

int Tache::getDate()
{
    return date;
}

void Tache::setDate(int i)
{
    date = i;
}

QDate Tache::getDateabs()
{
    return dateabs;
}

void Tache::setDateabs(QDate uneDate)
{
    dateabs = uneDate;
}

string Tache::getDaterel()
{
    return daterel;
}

void Tache::setDaterel(string s)
{
    daterel = s;
}

vector<Tache> Tache::getPreconditions()
{
    return preconditions;
}

void Tache::setPreconditions(vector<Tache> pr)
{
    preconditions = pr;
}

void Tache::addPrecondition(Tache uneTache)
{
    preconditions.push_back(uneTache);
}

vector<Tache*> Tache::getSousTaches()
{
    return sousTaches;
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

// Pour les tests
void Tache::afficherPreconds()
{
    for(int i=0 ; i<preconditions.size() ; ++i)
    {
        cout << preconditions[i].getNom() << endl;
    }
}

// initialiser le fichier xml
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

// remplir le fichier xml tache par tache
void Tache::addTacheInXml(TiXmlDocument doc,TiXmlElement * element)
{
    TiXmlElement * newElement = new TiXmlElement("tache");
    newElement->SetAttribute("nom",nom);

    if(date==1){
        newElement->SetAttribute("dateAbs",dateabs.toString().toStdString());
    }
    else if(date==2){
        newElement->SetAttribute("dateRel",daterel);
    }
    // TODO : modif avec les nouvelles dates
    // newElement->SetAttribute("date",date.toString().toStdString());
    element->LinkEndChild( newElement );

    for (int i=0 ; i<sousTaches.size() ; i++){
        Tache * sousTache = sousTaches.at(i);
        sousTache->addTacheInXml(doc,newElement);
    }
}

// remplir le fichier xml tache par tache pour template
void Tache::addTacheInXmlTemplate(TiXmlDocument doc,TiXmlElement * element)
{
    TiXmlElement * newElement = new TiXmlElement("tache");
    newElement->SetAttribute("nom",nom);

    element->LinkEndChild( newElement );

    for (int i=0 ; i<sousTaches.size() ; i++){
        Tache * sousTache = sousTaches.at(i);
        sousTache->addTacheInXml(doc,newElement);
    }
}

