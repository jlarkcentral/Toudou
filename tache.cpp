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

void Tache::xmlToTache()
{

}

void Tache::tacheToXml()
{
    TiXmlDocument doc("../Toudou/xml/"+nom+".xml");

    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
    TiXmlElement * element = new TiXmlElement( nom );
    TiXmlText * text = new TiXmlText( "World" );
    element->LinkEndChild( text );
    doc.LinkEndChild( decl );
    doc.LinkEndChild( element );
    doc.SaveFile();

    // DOC tinyxml -> ajout root puis noeud depuis liste sous taches

}
