#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;
//----------LOCUINTA------------
class Locuinta{
private:
protected:
    string numeClient;
    int suprafataUtila;
    int pret;
    int y;
    float discount;
    unsigned int id;
    static unsigned int numarTotalLocuinte;
public:

    Locuinta(){numarTotalLocuinte++; id = numarTotalLocuinte;};

    Locuinta(string numeClient, int suprafataUtila, float discount);

    Locuinta(const Locuinta &l);

    ~Locuinta();

    virtual Locuinta operator=(const Locuinta &l);

    friend istream& operator>>(istream&, Locuinta&);

    friend ostream& operator<<(ostream&, Locuinta&);

    virtual void citire(istream &in);

    virtual void afisare(ostream &out);

    virtual void calculChirie(int x, int y);

    static void numarObiecte(){cout << numarTotalLocuinte << "\n";}
};
unsigned int Locuinta::numarTotalLocuinte;
//----------Constructori-----------
Locuinta::Locuinta(string numeClient, int suprafataUtila, float discout){
    numarTotalLocuinte++;
    this->numeClient = numeClient;
    this->suprafataUtila = suprafataUtila;
    this->discount = discout;
}

Locuinta::Locuinta(const Locuinta &l){
    numarTotalLocuinte++;
    numeClient = l.numeClient;
    suprafataUtila = l.suprafataUtila;
    discount = l.discount;
}

//--------------Desctructor------------
Locuinta::~Locuinta(){
    numarTotalLocuinte--;
    numeClient.resize(0);
    suprafataUtila = 0;
    discount = 0;
}
//------------Operatori si IO-----------------
Locuinta Locuinta::operator=(const Locuinta &l){
    numeClient = l.numeClient;
    suprafataUtila = l.suprafataUtila;
    discount = l.discount;
    return *this;
}


void Locuinta::citire(istream &in){
    cout << "Introdu numele clientului: ";
    in >> numeClient;

    cout << "Introdu suprafata utila: ";
    in >> suprafataUtila;
    while(suprafataUtila <= 0){
        cout << "EROARE! \n Introdu o suprafata utila mai mare decat 0 \n";
        in >> suprafataUtila;
    }

    cout << "Introdu discountul: ";
    in >> discount;
    while(discount < 0 || discount > 100){
        cout << "EROARE! \n Introdu un discount intre 0 si 100 \n";
        in >>discount;
    }

    cout << "Introdu pretul: ";
    in >> pret;

    cout << "Se aplica discount?[y/n]";
    char c;
    cin >> c;
    if(c=='y')
        y = 1;
    else y = 0;

}

void Locuinta::afisare(ostream &out){
    out << "ID: " << id << "\n";
    out << "Nume client: " << numeClient << "\n";
    out << "Suprafata Utila: " << suprafataUtila << "\n";
    out << "Discount: " << discount << "\n";
    calculChirie(pret,y);
}

istream& operator>>(istream &in, Locuinta &l){
    l.citire(in);
    return in;
}

ostream& operator<<(ostream &out, Locuinta &l){
    l.afisare(out);
    return out;
}

//----------Alte functii------------
void Locuinta::calculChirie(int x, int y){
    cout << "Locuinta trebuie sa fie casa sau apartament pentru a calcula chiria \n";
}

//-----------APARTAMENT---------------
class Apartament:public Locuinta{
private:
protected:
    int etaj;
public:
    Apartament():Locuinta(){};

    Apartament(string numeClient, int suprafataUtila, float discount, int etaj);

    Apartament(const Apartament &a);

    ~Apartament();

    friend istream& operator>>(istream&, Apartament&);

    friend ostream& operator<<(ostream&, const Apartament&);

    void citire(istream &in);

    void afisare(ostream &out);

    Apartament operator=(const Apartament &a);

    void calculChirie(int x, int y);
};
//----------CONSTRUCTORI--------------
Apartament::Apartament(string numeClient, int suprafataUtila, float discount, int etaj):Locuinta(numeClient,suprafataUtila,discount){
    this->etaj = etaj;
}

Apartament::Apartament(const Apartament &a):Locuinta(a){
    etaj = a.etaj;
}
//----------DESTRUCTORI----------
Apartament::~Apartament(){
    etaj = 0;
}
//-----------IO--------------
istream& operator>>(istream &in, Apartament &a){
    a.citire(in);
    return in;
}

ostream& operator<<(ostream &out, Apartament &a){
    a.afisare(out);
    return out;
}


void Apartament::citire(istream &in){
    Locuinta::citire(in);
    cout << "Introdu etajul: ";
    in >> etaj;
    while(etaj < 0){
        cout << "EROARE! Introduceti un etaj mai mare sau egal cu 0";
        in >> etaj;
    }
}

void Apartament::afisare(ostream &out){
    Locuinta::afisare(out);
    cout << "Etaj: " << etaj << "\n";
}
//----------OPERATORI-------------
Apartament Apartament::operator=(const Apartament &a){
    numeClient = a.numeClient;
    suprafataUtila = a.suprafataUtila;
    discount = a.discount;
    etaj = a.etaj;
    return *this;
}

//------------ALTE FUNCTII------------
void Apartament::calculChirie(int x, int y){
    float chirie;
    chirie = x*suprafataUtila*(1-y*discount/100.0);
    cout << "Chiria apartamentului este " << chirie << "\n";
}
//------------CASA----------------
class Casa:public Locuinta{
private:
    int suprafataCurte;
protected:
public:

    Casa():Locuinta(){};

    Casa(string numeClient, int suprafataUtila, float discount, int suprafataCurte );

    Casa(const Casa &c);

    ~Casa();

    friend istream& operator>>(istream&, Casa&);

    friend ostream& operator<<(ostream&, const Casa&);

    void citire(istream &in);

    void afisare(ostream &out);

    Casa operator=(const Casa &c);

    void calculChirie(int x, int y);

};

//--------------CONSTRUCTORI-----------------

Casa::Casa(string numeClient, int suprafataUtila, float discount, int suprafataCurte):Locuinta(numeClient,suprafataUtila,discount){
    this->suprafataCurte = suprafataCurte;
}

Casa::Casa(const Casa &c):Locuinta(c){
    suprafataCurte = c.suprafataCurte;
}

//-----------DESTRUCTORI----------------
Casa::~Casa(){
    suprafataCurte = 0;
}

//------------IO------------------
istream& operator>>(istream& in, Casa &c){
    c.citire(in);
    return in;
}

ostream& operator<<(ostream &out, Casa &c){
    c.afisare(out);
    return out;
}

void Casa::citire(istream &in){
    Locuinta::citire(in);
    cout << "Introdu suprafata curte: ";
    cin >> suprafataCurte;
    while(suprafataCurte < 0){
        cout << "EROARE! Introdu o suprafata mai mare sau egala cu 0 \n Noua valoare pentru suprafata curte: ";
        cin >> suprafataCurte;
    }
}

void Casa::afisare(ostream &out){
    Locuinta::afisare(out);
    cout << "Suprafata Curte: " << suprafataCurte << "\n";
}

//--------------ALTE FUNCTII------------

void Casa::calculChirie(int x, int y){
    float chirie;
    chirie = x*(suprafataUtila + 0.2*suprafataCurte) * (1-y*discount/100.0);
    cout << "Chiria casei este: " << chirie << "\n";
}

//---------AGENTIE IMOBILIARA------------
class AgentieImobiliara{
private:
    vector<Locuinta*> locuinta;
    static unsigned int numar;
    unsigned int id;
protected:
public:

    AgentieImobiliara(){numar++; id = numar;}

    ~AgentieImobiliara(){locuinta.resize(0);}

    friend istream& operator>>(istream&, AgentieImobiliara&);

    friend ostream& operator<<(ostream&, const AgentieImobiliara&);

};

unsigned int AgentieImobiliara::numar;

istream& operator>>(istream &in, AgentieImobiliara &a){
    int numarLocuinte;
    cout << "Introdu numarul de locuinte al agentiei";
    cin >> numarLocuinte;
    while(numarLocuinte < 0){
        cout << "EROARE! Introdu un numar mai mare sau egal cu 0. \n Noua valoare: ";
        cin >> numarLocuinte;
    }
    a.locuinta.reserve(numarLocuinte);
    for(int i = 0; i < numarLocuinte; i++){
        int optiune;
        cout << "Introdu tipul de locuinta: \n 1) Locuinta \n 2) Apartament \n 3) Casa \n";
        cin >> optiune;
        switch(optiune){
            case 1:{
                a.locuinta.push_back(new Locuinta);
                break;
            }
            case 2:{
                a.locuinta.push_back(new Apartament);
                break;
            }
            case 3:{
                a.locuinta.push_back(new Casa);
                break;
            }
            default:{
                a.locuinta.push_back(new Locuinta);
                break;
            }
        }
        cin >> *(a.locuinta[i]);
    }
}

ostream& operator<<(ostream &out, const AgentieImobiliara &a){
    cout << "Agentia imobiliara " << a.id << "\n";
    for(int i = 0; i < a.locuinta.size(); i++){
        cout << *(a.locuinta[i]);
    }
}

void meniu(){
    cout <<"1) Introdu o agentie \n";
    cout <<"2) Vezi toate agentiile \n";
    cout << "0) Exit \n";
}

int main(){
    char option = 'a';
    vector<AgentieImobiliara> a;
    int numarAgentii = 0;
    while(option != '0'){
        meniu();
        cin >> option;
        if(option == '1'){
            numarAgentii++;
            a.resize(numarAgentii);
            cin >> a[numarAgentii-1];
        }
        else if(option == '2')
            for(int i = 0; i < numarAgentii; i++)
                cout << "\n \n" << a[i];
        else cout << "Introdu o varianta valida";

    }
    return 0;
}
