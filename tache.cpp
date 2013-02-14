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

vector<Tache> Tache::getSousTaches()
{
    return sousTaches;
}

void Tache::addPrecondition(Tache uneTache)
{
    preconditions.push_back(uneTache);
}

void Tache::addSousTache(Tache uneTache)
{
    sousTaches.push_back(uneTache);
}

void Tache::xmlToTache()
{

}

void Tache::createXml()
{
    TiXmlDocument doc("../Toudou/xml/"+nom+".xml");

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
    element->LinkEndChild( newElement );
    TiXmlText * text = new TiXmlText( nom);
    newElement->LinkEndChild( text );

    for (int i=0 ; i<sousTaches.size() ; i++){
        Tache sousTache = sousTaches.at(i);
        //sousTache.addTacheInXml(doc,newElement);
        TiXmlElement * newnewElement = new TiXmlElement("tache");
        newElement->LinkEndChild( newnewElement );
        TiXmlText * newtext = new TiXmlText( sousTache.getNom());
        newnewElement->LinkEndChild( newtext );

        for (int i=0 ; i<sousTache.getSousTaches().size() ; i++){
            Tache soussousTache = sousTache.getSousTaches().at(i);
            soussousTache.addTacheInXml(doc,newnewElement);
        }
    }

    doc.SaveFile();
}

void Tache::display()
{
    cout << nom << endl;
    for (int i=0 ; i<getSousTaches().size() ; i++){
        Tache st = getSousTaches().at(i);
        st.display();
    }
}
