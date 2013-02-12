#include "tache.h"

using namespace std;

Tache::Tache(string uneTache)
{
    tache = uneTache;
}

string Tache::getTache()
{
    return tache;
}

void Tache::setTache(string uneTache)
{
    tache = uneTache;
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
    ofstream myfile;
      myfile.open ("../Toudou/xml/example.xml");
      myfile << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";

      TiXmlDocument doc("../Toudou/xml/example.xml");
      if(!doc.LoadFile()){
          cerr << "erreur lors du chargement" << endl;
          cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
          return;
      }
      // DOC tinyxml -> ajout root puis noeud depuis liste sous taches

      myfile.close();

}
