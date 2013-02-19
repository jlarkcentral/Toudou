#include "tache.h"

using namespace std;

Tache::Tache(string uneTache)
{
    nom = uneTache;
    fini = false;
    ordon = false;
}

Tache::Tache(QTreeWidgetItem *item,bool withSousTaches)
{
    nom = item->text(0).toStdString();
    daterel = item->text(1).toStdString();
    if(withSousTaches){
        for(int i=0 ; i<item->childCount() ; i++){
        Tache * st = new Tache(item->child(i),withSousTaches);
        st->setFini(false);
        this->addSousTache(st);
        }
    }
    fini = false;
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

bool Tache::getOrdon()
{
    return ordon;
}

void Tache::setOrdon(bool b)
{
    ordon = b;
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
    string stringnom = "../Toudou/xml/"+nomFichier+".xml";
    const char * charnom = stringnom.c_str();
    TiXmlDocument doc(charnom);

    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
    doc.LinkEndChild( decl );
    TiXmlElement * firstElement = new TiXmlElement( "racine" );
    doc.LinkEndChild( firstElement );

    addTacheInXml(firstElement);

    doc.SaveFile();

}

// remplir le fichier xml tache par tache
void Tache::addTacheInXml(TiXmlElement * element)
{
    const char * chartache("tache");
    TiXmlElement * newElement = new TiXmlElement(chartache);
    const char * charnom("nom");
    const char * chardateAbs("dateAbs");
    const char * chardateRel("dateRel");
    const char * charchecked("checked");
    const char * charordonnee("ordonnee");

    const char * nomtache = nom.c_str();
    newElement->SetAttribute(charnom,nomtache);

    if(date==1){
        const char * dateAbstache = dateabs.toString().toStdString().c_str();
        newElement->SetAttribute(chardateAbs,dateAbstache);
    }
    else if(date==2){
        const char * dateReltache = daterel.c_str();
        newElement->SetAttribute(chardateRel,dateReltache);
    }

    newElement->SetAttribute(charchecked,fini);
    newElement->SetAttribute(charordonnee,ordon);

    element->LinkEndChild( newElement );

    for (int i=0 ; i<sousTaches.size() ; i++){
        Tache * sousTache = sousTaches.at(i);
        sousTache->addTacheInXml(newElement);
    }
}

// remplir le fichier xml tache par tache pour template
void Tache::addTacheInXmlTemplate(TiXmlDocument doc, TiXmlElement * element)
{
    TiXmlElement * newElement = new TiXmlElement("tache");
    const char * charnom = nom.c_str();
    newElement->SetAttribute("nom",charnom);

    element->LinkEndChild( newElement );

    for (int i=0 ; i<sousTaches.size() ; i++){
        Tache * sousTache = sousTaches.at(i);
        sousTache->addTacheInXml(newElement);
    }
}

