#include <iostream>
#include <new>
#include <cstdlib>
#include <string.h>
#include <typeinfo>
using namespace std;

class Avocat{
    int cod;
    string nume;
    int nr_procese;
    int *vector_procese;

public:
    // CONSTRUCTOR DE INITIALIZARE
    Avocat();

    // CONSTRUCTOR PARAMETRIZAT
    Avocat(int,string,int);

    // CONSTRUCTOR DE COPIERE
    Avocat(const Avocat&);

    // OPERATOR DE ATRIBUIRE
    Avocat& operator=(const Avocat);

    // DESTRUCTOR
    virtual ~Avocat();

    // OPERATORI ISTREAM & OSTREAM
    friend istream& operator>>(istream&,Avocat&);
    friend ostream& operator<<(ostream&,const Avocat&);

    // CITIREA & AFISAREA A n OBIECTE
    friend void citire_n_obiecte();
    virtual void citire();
    virtual void afis();

    // OPERATOR > & <
    int operator>(Avocat);
    int operator<(Avocat);

    // SORTAREA UNEI LISTE DE AVOCATI DUPA NUMARUL DE PROCESE
    friend void sortare_nr_procese_c(Avocat*,int);
    friend void sortare_nr_procese_d(Avocat*,int);
};

class Avocat_Oficiu: public Avocat{
    string nume_client;
    int durata;

public:
    // CONSTRUCTOR DE INITIALIZARE
    Avocat_Oficiu();

    // CONSTRUCTOR PARAMETRIZAT
    Avocat_Oficiu(int,string,int,string,int);

    // CONSTRUCTOR DE COPIERE
    Avocat_Oficiu(const Avocat_Oficiu&);

    // OPERATOR DE ATRIBUIRE
    Avocat_Oficiu& operator=(const Avocat_Oficiu);

    // DESTRUCTOR
    ~Avocat_Oficiu();

    // OPERATORII ISTREAM & OSTREAM
    friend istream& operator>>(istream&,Avocat_Oficiu&);
    friend ostream& operator<<(ostream&,const Avocat_Oficiu&);

    // CITIREA & AFISAREA A n OBIECTE
    friend void citire_n_obiecte();
    void citire();
    void afis();
};

// CONSTRUCTOR DE INITIALIZARE
Avocat::Avocat(){}

// CONSTRUCTOR PARAMETRIZAT
Avocat::Avocat(int C,string N,int NR_P)
{
    cod=C;
    nume=N;

    try{
        vector_procese=new int[NR_P];
    }
    catch (bad_alloc xa){
        cout<<"Numarul de procese introdus este invalid! Mai incercati o data!"<<endl;
        exit(EXIT_FAILURE);
    }

    nr_procese=NR_P;
}

// CONSTRUCTOR DE COPIERE
Avocat::Avocat(const Avocat& A)
{
    cod=A.cod;
    nume=A.nume;

    try{
        vector_procese=new int[A.nr_procese];
    }
    catch (bad_alloc xa){
        cout<<"Numarul de procese introdus este invalid! Mai incercati o data!"<<endl;
        exit(EXIT_FAILURE);
    }

    nr_procese=A.nr_procese;
    for(int i=0;i<nr_procese;i++)
        vector_procese[i]=A.vector_procese[i];
}

// OPERATOR DE ATRIBUIRE
Avocat& Avocat::operator=(const Avocat A)
{
    if(this!=&A){
        cod=A.cod;
        nume=A.nume;
        vector_procese=new int[A.nr_procese];
        nr_procese=A.nr_procese;
        for(int i=0;i<nr_procese;i++)
            vector_procese[i]=A.vector_procese[i];
    }
    return *this;
}

// DESTRUCTOR
Avocat::~Avocat()
{
    delete[] vector_procese;
}

// OPERATORII PENTRU ISTREAM & OSTREAM
istream& operator>>(istream& in,Avocat& A)
{
    bool input_corect=false;
    while(!input_corect)
        try{
            cout<<"Codul avocatului: "; in>>A.cod;
            if(A.cod<0)throw 1;
            else input_corect=true;
        }
        catch(int x){
            cout<<"Codul avocatului introdus este invalid! Mai incercati o data!"<<endl;
        }

    input_corect=false;
    while(!input_corect)
        try{
            cout<<"Numele avocatului: "; in>>A.nume;
            int lungime_nume=(A.nume).size(),i;
            for(i=0;i<lungime_nume;i++)
                if(!isalpha(A.nume[i]))throw 1;
            input_corect=true;
        }
        catch(int x){
            cout<<"Numele avocatului introdus este invalid! Mai incercati o data!"<<endl;
        }

    input_corect=false;
    while(!input_corect)
        try{
            cout<<"Numarul de procese ale avocatului: ";
            in>>A.nr_procese;
            if(A.nr_procese<=0)throw 1;
            else input_corect=true;
        }
        catch(int x){
            cout<<"Numarul de procese introdus este invalid! Mai incercati o data!"<<endl;
        }

    try{
        A.vector_procese=new int[A.nr_procese];
    }
    catch (bad_alloc xa){
        cout<<"Numarul de procese introdus este invalid! Mai incercati o data!"<<endl;
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<A.nr_procese;i++){
        input_corect=false;
        while(!input_corect)
            try{
                cout<<"Suma primita pentru procesul "<<i+1<<": ";
                cin>>A.vector_procese[i];
                if(A.vector_procese[i]<=0)throw 1;
                else input_corect=true;
            }
            catch(int x){
                cout<<"Suma introdusa pentru procesul "<<i+1<<" este invalida! Mai incercati o data!"<<endl;
            }
    }
    return in;
}
ostream& operator<<(ostream& out,const Avocat& A)
{
    cout<<"Codul avocatului: "; out<<A.cod<<endl;
    cout<<"Numele avocatului: "; out<<A.nume<<endl;
    cout<<"Numarul de procese ale avocatului: "; out<<A.nr_procese<<endl;
    for(int i=0;i<A.nr_procese;i++){
        cout<<"Suma primita pentru procesul "<<i+1<<": ";
        out<<A.vector_procese[i]<<endl;
    }
    return out;
}

// AFISARE PRIN FUNCTIE VIRTUALA
void Avocat::citire()
{
    bool input_corect=false;
    while(!input_corect)
        try{
            cout<<"Codul avocatului: "; cin>>cod;
            if(cod<0)throw 1;
            else input_corect=true;
        }
        catch(int x){
            cout<<"Codul avocatului introdus este invalid! Mai incercati o data!"<<endl;
        }

    input_corect=false;
    while(!input_corect)
        try{
            cout<<"Numele avocatului: "; cin>>nume;
            int lungime_nume=nume.size(),i;
            for(i=0;i<lungime_nume;i++)
                if(!isalpha(nume[i]))throw 1;
            input_corect=true;
        }
        catch(int x){
            cout<<"Numele avocatului introdus este invalid! Mai incercati o data!"<<endl;
        }

    input_corect=false;
    while(!input_corect)
        try{
            cout<<"Numarul de procese ale avocatului: ";
            cin>>nr_procese;
            if(nr_procese<=0)throw 1;
            else input_corect=true;
        }
        catch(int x){
            cout<<"Numarul de procese introdus este invalid! Mai incercati o data!"<<endl;
        }

    try{
        vector_procese=new int[nr_procese];
    }
    catch (bad_alloc xa){
        cout<<"Numarul de procese introdus este invalid! Mai incercati o data!"<<endl;
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<nr_procese;i++){
        input_corect=false;
        while(!input_corect)
            try{
                cout<<"Suma primita pentru procesul "<<i+1<<": ";
                cin>>vector_procese[i];
                if(vector_procese[i]<=0)throw 1;
                else input_corect=true;
            }
            catch(int x){
                cout<<"Suma introdusa pentru procesul "<<i+1<<" este invalida! Mai incercati o data!"<<endl;
            }
    }
}
void Avocat::afis()
{
    cout<<"Codul avocatului: "<<cod<<endl;
    cout<<"Numele avocatului: "<<nume<<endl;
    cout<<"Numarul de procese ale avocatului: "<<nr_procese<<endl;
    for(int i=0;i<nr_procese;i++){
        cout<<"Suma primita pentru procesul "<<i+1<<": ";
        cout<<vector_procese[i]<<endl;
    }
}

// OPERATOR > & <
int Avocat::operator>(Avocat A)
{
    if(nr_procese>A.nr_procese)return 1;
    return 0;
}
int Avocat::operator<(Avocat A)
{
    if(nr_procese<A.nr_procese)return 1;
    return 0;
}

// SORTAREA UNEI LISTE DE AVOCATI DUPA NUMARUL DE PROCESE
// SORTARE CRESCATOARE
void sortare_nr_procese_c(Avocat *V_A,int NR_A)
{
    int i,j;
    for(i=0;i<NR_A-1;i++)
        for(j=i+1;j<NR_A;j++)
            if(V_A[i]>V_A[j])
                swap(V_A[i],V_A[j]);
}
// SORTARE DESCRESCATOARE
void sortare_nr_procese_d(Avocat *V_A,int NR_A)
{
    int i,j;
    for(i=0;i<NR_A-1;i++)
        for(j=i+1;j<NR_A;j++)
            if(V_A[i]<V_A[j])
                swap(V_A[i],V_A[j]);
}

// CONSTRUCTOR DE INITIALIZARE - DERIVATA
Avocat_Oficiu::Avocat_Oficiu():Avocat(){}

// CONSTRUCTOR PARAMETRIZAT - DERIVATA
Avocat_Oficiu::Avocat_Oficiu(int C,string N,int NR_P,string N_C,int D):Avocat(C,N,NR_P)
{
    nume_client=N_C;
    durata=D;
}

// CONSTRUCTOR DE COPIERE - DERIVATA
Avocat_Oficiu::Avocat_Oficiu(const Avocat_Oficiu& A_O):Avocat(A_O)
{
    nume_client=A_O.nume_client;
    durata=A_O.durata;
}

// OPERATOR DE ATRIBUIRE - DERIVATA
Avocat_Oficiu& Avocat_Oficiu::operator=(const Avocat_Oficiu A_O)
{
    if(this!=&A_O){
        this->Avocat::operator=(A_O);

        nume_client=A_O.nume_client;
        durata=A_O.durata;
    }
    return *this;
}

// DESTRUCTOR - DERIVATA
Avocat_Oficiu::~Avocat_Oficiu(){}

// OPERATORII PENTRU ISTREAM & OSTREAM - DERIVATA
istream& operator>>(istream& in,Avocat_Oficiu& A_O)
{
    in>>dynamic_cast<Avocat&>(A_O);

    bool input_corect=false;
    while(!input_corect)
        try{
            cout<<"Nume client: "; cin>>A_O.nume_client;
            int lungime_nume_client=A_O.nume_client.size(),i;
            for(i=0;i<lungime_nume_client;i++)
                if(!isalpha(A_O.nume_client[i]))throw 1;
            input_corect=true;
        }
        catch(int x){
            cout<<"Numele clientului introdus este invalid! Mai incercati o data!"<<endl;
        }

    input_corect=false;
    while(!input_corect)
        try{
            cout<<"Durata: ";
            cin>>A_O.durata;
            if(A_O.durata<=0)throw 1;
            else input_corect=true;
        }
        catch(int x){
            cout<<"Durata introdusa este invalida! Mai incercati o data!"<<endl;
        }
    return in;
}
ostream& operator<<(ostream& out,const Avocat_Oficiu& A_O)
{
    out<<dynamic_cast<const Avocat&>(A_O);

    cout<<"Nume client: "; out<<A_O.nume_client;
    cout<<"Durata: "; out<<A_O.durata;
    return out;
}

// CITIRE & AFISARE PRIN FUNCTIE VIRTUALA
void Avocat_Oficiu::citire()
{
    Avocat::citire();

    bool input_corect=false;
    while(!input_corect)
        try{
            cout<<"Nume client: "; cin>>nume_client;
            int lungime_nume_client=nume_client.size(),i;
            for(i=0;i<lungime_nume_client;i++)
                if(!isalpha(nume_client[i]))throw 1;
            input_corect=true;
        }
        catch(int x){
            cout<<"Numele clientului introdus este invalid! Mai incercati o data!"<<endl;
        }

    input_corect=false;
    while(!input_corect)
        try{
            cout<<"Durata: ";
            cin>>durata;
            if(durata<=0)throw 1;
            else input_corect=true;
        }
        catch(int x){
            cout<<"Durata introdusa este invalida! Mai incercati o data!"<<endl;
        }
}
void Avocat_Oficiu::afis()
{
    Avocat::afis();
    cout<<"Nume client: "<<nume_client<<endl;
    cout<<"Durata: "<<durata;
}

// CITIREA & AFISAREA A n OBIECTE
void citire_n_obiecte()
{
    int n,i,op;
    Avocat* *vector_avocati;

    bool input_corect=false;

    while(!input_corect)
        try{
            cout<<"Introduceti numarul de avocati: "; cin>>n;
            if(n<=0)throw 1;
            else input_corect=true;
        }
        catch(int x){
            cout<<"Numarul de avocati introdus este invalid! Mai incercati o data!"<<endl;
        }

    vector_avocati=new Avocat* [n];

    // CITIREA
    for(i=0;i<n;i++){
        bool input_citire=false;
        while(!input_citire){
            cout<<"Introduceti optiunea de citire: 1 pentru citirea unui avocat sau 2 pentru citirea unui avocat din oficiu";
            cout<<endl<<"Optiunea aleasa: "; cin>>op;
            switch(op)
            {
                case 1:{vector_avocati[i]=new Avocat(); input_citire=true; break;}
                case 2:{vector_avocati[i]=new Avocat_Oficiu(); input_citire=true; break;}
                default:{cout<<"Optiunea introdusa nu este valida! Mai incercati o data!"<<endl;}
            }
        }
        vector_avocati[i]->citire();
    }
    // AFISAREA
    for(i=0;i<n;i++){
        vector_avocati[i]->afis();
        cout<<endl;
    }
}

int main(){
    citire_n_obiecte();
    return 0;
}