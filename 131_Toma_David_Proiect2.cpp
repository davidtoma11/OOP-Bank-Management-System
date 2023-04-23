#include <iostream>
#include <string>
#include <vector>

using namespace std;


class OperatiuniContBancar // clasa abstracta
{
public:
    virtual void depunere(double suma) = 0;
    virtual void retragere(double suma) = 0;
};

class ContBancar : public OperatiuniContBancar
{
protected:
    string nume; // numele titularului contului bancar
    double sold; // soldul contului bancar
    int iban; // iban - ul contului bancar

public:

    // setteri si getteri
    void setnume(string n)
    {
        nume = n;
    }

    string getnume() const
    {
        return nume;
    }

    void setsold(double s)
    {
        sold = s;
    }

    double getsold() const
    {
        return sold;
    }

    void setiban(int ib)
    {
        iban = ib;
    }

    int getiban() const
    {
        return iban;
    }

    ContBancar(string n, double s, int ib) // constructorul cu toti parametrii
    {
        nume = n;
        sold = s;
        iban = ib;
    }

    ContBancar() // construcorul fara parametrii
    {
        nume = "";
        sold = 0.0;
        iban = 0000000;
    }

    virtual ~ContBancar() // destructor
    {

    }

    ContBancar(const ContBancar& c) // copy constructor
    {
        nume = c.nume;
        sold = c.sold;
        iban = c.iban;
    }

    ContBancar& operator=(const ContBancar& c) // operatorul egal
    {
        if (this == &c) // verificare auto-asignare
            return *this;
        nume = c.nume;
        sold = c.sold;
        iban = c.iban;
        return *this;
    }

    friend istream& operator>>(istream& in, ContBancar& c) // operatorul de citire
    {
        cout << "Introduceti numele titularului: " << endl;
        in >> c.nume;
        cout << "Introduceti soldul initial: " << endl;
        in >> c.sold;
        cout << "Introduceti iban-ul: " << endl;
        in >> c.iban;
        cout << endl;
        return in;
    }

    friend ostream& operator<<(ostream& out, const ContBancar& c) // operatorul de afișare
    {
        out << "Titular: " << c.nume << endl;
        out << "Sold: " << c.sold << " lei" << endl;
        out << "IBAN: " << c.iban << endl;
        return out;
    }

    void depunere(double valoare) override
    {
        sold += valoare;
    }

    void retragere(double valoare) override
    {
        if (sold - valoare >= 0)
        {
            sold -= valoare;
        }
        else
        {
            cout << "Fonduri insuficiente" << endl;
        }
    }

    void AccesareBancomat(ContBancar& cont)  // exemplificarea conceptului de polimorfism
    {
        int ok = 1;
        while(ok == 1)
        {
            int x = 0;
            while(x != 1 && x != 2)
            {
                cout << "Selectati optiunea dorita" << endl;
                cout << "1 - Depunere // 2 - Retragere :" ;
                cin >> x;
                cout << endl;
                if (x == 1)
                {
                    double depunere;
                    cout << "Introduceti suma pe care doriti sa o depuneti: " ;
                    cin >> depunere;
                    cont.depunere(depunere);
                    cout << endl;
                    cout << "Suma dvs a fost depusa cu succes! " << endl;
                }

                if(x == 2)
                {
                    double retragere;
                    cout << "Introduceti suma pe care doriti sa o retrageti: ";
                    cin >> retragere;
                    cont.retragere(retragere);
                    cout << endl;
                    cout << "Suma dvs a fost retrasa cu succes! " << endl;
                }
                if(x != 1 && x != 2)
                    cout << "Cifra introdusa este incorecta! Va rugam sa mai incercati! ";
            }

            cout << "Doriti sa continuati efectuati si alta tranzactie ?" << endl;
            cout << "1 - DA // 0 - NU : ";
            cin >> ok;
            cout << endl;


        }
        cout << endl;
        cout << "Va mai asteptam curand! ";
    }


};

class ContCurent : public ContBancar
{
protected:
    double commision;
    int nr_tranzactii;

public:
    // setteri si getteri
    void setcommision(double c)
    {
        commision = c;
    }

    double getcommision() const
    {
        return commision;
    }

    void setnr_tranzactii(int nr)
    {
        nr_tranzactii = nr;
    }

    int getnr_tranzactii() const
    {
        return nr_tranzactii;
    }

    ContCurent(string n, double s, int ib, double c, int nr) : ContBancar(n,s,ib), commision(c),nr_tranzactii(nr) {} // constructorul cu toti parameterii

    ContCurent() : ContBancar(), commision(0), nr_tranzactii(0) {} // constructorul fara parametrii
    ContCurent(const ContCurent& c) : ContBancar(c), commision(c.commision), nr_tranzactii(c.nr_tranzactii) {} // copy constructor
    virtual ~ContCurent() {} // destructorul
    ContCurent& operator=(const ContCurent& c) // operatorul de egalitate
    {
        if (this == &c) // verificare auto-asignare
            return *this;
        nume = c.nume;
        sold = c.sold;
        iban = c.iban;
        commision = c.commision;
        nr_tranzactii = c.nr_tranzactii;
        return *this;
    }

    friend istream& operator >>(istream& in, ContCurent& c) // operatorul de citire
    {
        cout << "Introduceti numele titularului: " << endl;
        in >> c.nume;
        cout << "Introduceti soldul initial: " << endl;
        in >> c.sold;
        cout << "Introduceti iban-ul: " << endl;
        in >> c.iban;
        cout << "Introduceti commisionul: " << endl;
        in >> c.commision;
        cout << "Introduceti numarul tranzactiilor deja efectuate: " << endl;
        in >> c.nr_tranzactii;
        cout << endl;
        return in;
    }

    friend ostream& operator<<(ostream& out, const ContCurent& c) // operatorul de afișare
    {
        out << "Titular: " << c.nume << endl;
        out << "Sold: " << c.sold << " lei" << endl;
        out << "IBAN: " << c.iban << endl;
        out << "Commision: " << c.commision << endl;
        out << "Numar tranzactii: " << c.nr_tranzactii << endl;
        return out;
    }

    // exemplificare concept de virtualizare
    void depunere(double suma) override
    {
        sold += suma;
        sold -= (suma*commision);
        nr_tranzactii ++ ;
    }

    void retragere(double suma) override
    {
        if(suma > sold)
            cout << "Fonduri insuficiente !" << endl;
        else
            sold -= suma;
            nr_tranzactii ++;
    }

    double numar_tranzactii_efectuate()
    {
        return nr_tranzactii;
    }


};

class ContEconomii : public ContBancar
{
protected:
    float dobanda;
    int nr_luni;

public:
    // setteri si getteri
    void setdobanda(float d)
    {
        dobanda = d;
    }

    float getdobanda() const
    {
        return dobanda;
    }

    void setnr_luni(int nr)
    {
        nr_luni = nr;
    }

    int getnr_luni() const
    {
        return nr_luni;
    }

    ContEconomii(string n, double s, int ib, float d, int nr): ContBancar(n,s,ib), dobanda(d), nr_luni(nr) {} //constructorul cu toti parametrii
    ContEconomii() : ContBancar(), dobanda(0), nr_luni(0) {} // constructorul fara parametrii
    ContEconomii(const ContEconomii& c) : ContBancar(c), dobanda(c.dobanda), nr_luni(c.nr_luni) {} // copy constructor
    virtual ~ContEconomii() {} // destructorul
    ContEconomii& operator=(const ContEconomii& c) // operatorul de egalitate
    {
        if (this == &c) // verificare auto-asignare
            return *this;
        nume = c.nume;
        sold = c.sold;
        iban = c.iban;
        dobanda = c.dobanda;
        nr_luni = c.nr_luni;
        return *this;
    }

    friend istream& operator >>(istream& in, ContEconomii& c) // operatorul de citire
    {
        cout << "Introduceti numele titularului: " << endl;
        in >> c.nume;
        cout << "Introduceti soldul initial: " << endl;
        in >> c.sold;
        cout << "Introduceti iban-ul: " << endl;
        in >> c.iban;
        cout << "Introduceti dobanda aferenta depozitului: " << endl;
        in >> c.dobanda;
        cout << "Introduceti numarul de luni: " << endl;
        in >> c.nr_luni;
        cout << endl;
        return in;
    }

    friend ostream& operator<<(ostream& out, const ContEconomii& c) // operatorul de afișare
    {
        out << "Titular: " << c.nume << endl;
        out << "Sold: " << c.sold << " lei" << endl;
        out << "IBAN: " << c.iban << endl;
        out << "Dobanda: " << c.dobanda << endl;
        out << "Numarul de luni: " << c.nr_luni << endl;
        return out;
    }

    // exemplificare concept de virtualizare
    void depunere(double suma) override
    {
        sold += suma;
    }

    void retragere(double suma) override
    {
        if(suma > sold)
            cout << "Fonduri insuficiente !" << endl;
        else
            sold -= suma;
    }

    void CalculDobanda()
    {
        float dob = getdobanda();
        int luni = getnr_luni();
        double s = getsold();
        int x = 5;
        while(x != 1 && x != 0) // se actualizeaza sau nu datele depozitului
        {
            cout << "Datele introduse sunt corecte ?" << endl;
            cout << "1 - DA // 0 - NU ";
            cin >> x;
            cout << endl;
            if(x == 0)
            {
                cout << "Introduceti soldul: " << endl;
                cin >> s;
                cout << "Introduceti dobanda aferenta depozitului: " << endl;
                cin >> dob;
                cout << "Introduceti numarul de luni: " << endl;
                cin >> luni;

            }

            if(x != 1 && x != 0)
                cout << "Cifra introdusa este incorecta! Va rugam sa mai incercati! ";
        }
        cout << "Dobanda: " << dob << " /// Numar luni: " << luni << endl;
        cout << endl;
        cout << "Sold Initial: " << s << endl;

        float aux = s;
        for(int i = 1; i <= luni; i++)
        {
            int y = s*dob;
            s += y;
            cout << "Luna " << i << " - Sold: " << s << ",Dobanda acumulata: +" << y << " lei" << endl;
        }
        cout << "Dobanda total acumulata: " << s - aux << " lei";
    }


};

class ContPremium : public ContCurent, public ContEconomii // mostenirea diamant
{
private:
    int tranzactii_gratuite;
    bool cashback;

public:

    // setteri si getteri
    void set_tranzactii_gratuite(int tg)
    {
        tranzactii_gratuite = tg;
    }

    int get_tranzactii_gratuite() const
    {
        return tranzactii_gratuite;
    }

    void setcashback(bool cb)
    {
        cashback = cb;
    }

    bool getcashback() const
    {
        return cashback;
    }


    ContPremium(string n, double s, int ib, double c, int nr, float d, int nr_l, double tg, bool cb)
    : ContCurent(n, s, ib, c, nr), ContEconomii(n, s, ib, d, nr_l), tranzactii_gratuite(tg), cashback(cb) {} // constructorul cu tori parametrii

    ContPremium() : ContCurent(), ContEconomii(), tranzactii_gratuite(0), cashback(false) {} // constructorul fara parametrii

    ContPremium(const ContCurent& cc, const ContEconomii& ce, int tg, bool cb)
    : ContCurent(cc), ContEconomii(ce), tranzactii_gratuite(tg), cashback(cb) // constructorul ce combina doua obiecte
    {
        ContCurent::nume = cc.getnume();
        ContCurent::sold = cc.getsold() + ce.getsold();
    }

    ContPremium(const ContPremium& c)
    : ContCurent(c), ContEconomii(c), tranzactii_gratuite(c.tranzactii_gratuite), cashback(c.cashback) {} // copy constructorul

    virtual ~ContPremium() {} // destructorul
    ContPremium& operator=(const ContPremium& c) // operatorul egal
    {
        if (this == &c)
            return *this;

        ContCurent::operator=(c);
        ContEconomii::operator=(c);
        tranzactii_gratuite = c.tranzactii_gratuite;
        cashback = c.cashback;

        return *this;
    }

    friend istream& operator >>(istream& in, ContPremium& c) // operatorul de citire
    {
        ContCurent& cc = c;
        ContEconomii& ce = c;

        cout << "Introduceti numele titularului: " << endl;
        in >> c.ContCurent::nume;
        cout << "Introduceti soldul initial: " << endl;
        in >> c.ContCurent::sold;
        cout << "Introduceti iban-ul: " << endl;
        in >> c.ContCurent::iban;
        cout << "Introduceti commisionul pentru contul curent: " << endl;
        in >> c.commision;
        cout << "Introduceti numarul de tranzactii pentru contul curent: " << endl;
        in >> c.nr_tranzactii;
        cout << "Introduceti dobanda aferenta depozitului: " << endl;
        in >> c.dobanda;
        cout << "Introduceti numarul de luni deja trecute din depozit: " << endl;
        in >> c.nr_luni;
        cout << "Introduceti numarul de tranzactii gratuite permise: " << endl;
        in >> c.tranzactii_gratuite;
        cout << "Introduceti daca Clientul beneficiaza de un cashback de 5%(1/0): " << endl;
        in >> c.cashback;
        cout << endl;

        return in;
    }

    friend ostream& operator<<(ostream& out, const ContPremium& c) // operatorul de afisare
    {
        out << "Titular: " << c.ContCurent::nume << endl;
        out << "Sold: " << c.ContCurent::sold << " lei" << endl;
        out << "IBAN: " << c.ContCurent::iban << endl;
        out << "Commision cont curent: " << c.commision << endl;
        out << "Numar tranzactii cont curent: " << c.nr_tranzactii << endl;
        out << "Dobanda aferenta depozitului: " << c.dobanda << endl;
        out << "Numarul de luni deja trecute din depozit: " << c.nr_luni << endl;
        out << "Numar tranzactiilor gratuite permise: " << c.tranzactii_gratuite << endl;
        out << "Clientul beneficiaza de un cashback de 5%(1/0) ? " << c.cashback << endl;
        out << endl;
    }

    void VerificareTranzactiiGratuite(ContPremium& c)
    {
        int x = c.tranzactii_gratuite - c.nr_tranzactii;
        if (x > 0)
            cout << "Mai aveti " << x << " tranzactii gratuite" << endl;
        else
            cout << "Nu mai aveti tranzactii gratuite! " << endl;
    }


};


int main()
{
    int lista = 1;

    vector <ContBancar> ConturiBancare;
    vector <ContCurent> ConturiCurente;
    vector <ContEconomii> ConturiEconomii;
    vector <ContPremium> ConturiPremium;

    ContBancar Alex("Alex",500,1323411);
    ContBancar Iosif("Iosif",1100,7224141);
    ContBancar Albert("Albert",3000,3564680);
    ConturiBancare.push_back(Alex);
    ConturiBancare.push_back(Iosif);
    ConturiBancare.push_back(Albert);

    ContCurent DavidCC("David", 1900, 5058321, 0, 130);
    ContCurent Andrei("Andrei",200,2238926,0.02,0);
    ContCurent Leonard("Leonard",8000,1030811,0.01,150);
    ConturiCurente.push_back(DavidCC);
    ConturiCurente.push_back(Andrei);
    ConturiCurente.push_back(Leonard);

    ContEconomii DavidCE("David", 200000, 3438900, 7.4, 6);
    ContEconomii Daniela("Daniela", 150000, 3100072, 7, 6);
    ContEconomii Marius("Marius", 1000000, 7844122, 4, 12);
    ConturiEconomii.push_back(DavidCE);
    ConturiEconomii.push_back(Daniela);
    ConturiEconomii.push_back(Marius);

    ContPremium DavidCP(DavidCC,DavidCE,3,true);
    ConturiPremium.push_back(DavidCP);


    int start = 1;

    while(start == 1) // meniul interactiv
    {
        int clasa = -1;
        cout << "1 - Clasa Cont Bancar" << endl;
        cout << "2 - Clasa Cont Curent" << endl;
        cout << "3 - Clasa Cont Economii" << endl;
        cout << "4 - Clasa Cont Premium" << endl;
        cout << "0 - Inchidere Program" << endl;
        while(clasa < 0 || clasa > 4)
        {
            cout << "Introduceti cifra: ";
            cin >> clasa;
            cout << endl;
            if(clasa < 0 || clasa > 4)
            {
                cout << "Tasta incorecta !" << endl;
            }

            if(clasa == 1) // clasa ContBancar
            {
                cout << "CONT BANCAR" << endl;
                cout << endl;
                int c1 = -1;
                cout << "1 - Afisare lista conturi" << endl;
                cout << "2 - Adaugare cont" << endl;
                cout << "3 - Bancomat" << endl;
                cout << "0 - Meniu principal:" << endl;

                cout << "Introduceti cifra: ";
                cin >> c1;
                cout << endl;
                while (c1 >= 1 || c1 <= 3)
                {
                    if(c1 == 1)
                    {
                        if(ConturiBancare.size() == 0)
                            cout << "Nu avem conturi in lista!" << endl;
                        else
                        {
                            for (int i = 0; i < ConturiBancare.size(); i++)
                            {
                                cout << ConturiBancare[i];
                                cout << endl;
                            }
                        }

                    }

                    if(c1 == 2)
                    {
                        ContBancar cont;
                        cin >> cont;
                        ConturiBancare.push_back(cont);
                    }

                    if(c1 == 3)
                    {
                        int i;
                        bool ok = false;
                        while(ok == false)
                        {
                            cout << "Introdu ibanul clientului: ";
                            cin >> i;
                            for (int i = 0; i < ConturiBancare.size(); i++)
                            {
                                if(ConturiBancare[i].getiban() == i)
                                {
                                    ok = true;
                                    ConturiBancare[i].AccesareBancomat(ConturiBancare[i]);
                                }
                            }
                            if(ok == false)
                                cout << "IBAN incorect !" << endl;
                        }
                    }



                }

            }

            if(clasa == 2) // clasa ContCurent
            {
                cout << "CONT CURENT" << endl;
                cout << endl;
                int c1 = -1;
                cout << "1 - Afisare lista conturi" << endl;
                cout << "2 - Adaugare cont" << endl;
                cout << "3 - Bancomat" << endl;
                cout << "4 - Numar Tranzactii efectuate" << endl;
                cout << "0 - Meniu principal:" << endl;

                cout << "Introduceti cifra: ";
                cin >> c1;
                cout << endl;
                while (c1 >= 1 || c1 <= 3)
                {
                    if(c1 == 1)
                    {
                        if(ConturiCurente.size() == 0)
                            cout << "Nu avem conturi in lista!" << endl;
                        else
                        {
                            for (int i = 0; i < ConturiCurente.size(); i++)
                            {
                                cout << ConturiCurente[i];
                                cout << endl;
                            }
                        }

                    }

                    if(c1 == 2)
                    {
                        ContCurent cont;
                        cin >> cont;
                        ConturiCurente.push_back(cont);
                    }

                    if(c1 == 3)
                    {
                        int i;
                        bool ok = false;
                        while(ok == false)
                        {
                            cout << "Introdu ibanul clientului: ";
                            cin >> i;
                            for (int i = 0; i < ConturiCurente.size(); i++)
                            {
                                if(ConturiCurente[i].getiban() == i)
                                {
                                    ok = true;
                                    ConturiCurente[i].AccesareBancomat(ConturiCurente[i]);
                                }
                            }
                            if(ok == false)
                                cout << "IBAN incorect !" << endl;
                        }
                    }

                    if(c1 == 4)
                    {
                        int i;
                        bool ok = false;
                        while(ok == false)
                        {
                            cout << "Introdu ibanul clientului: ";
                            cin >> i;
                            for (int i = 0; i < ConturiCurente.size(); i++)
                            {
                                if(ConturiCurente[i].getiban() == i)
                                {
                                    ok = true;
                                    ConturiCurente[i].numar_tranzactii_efectuate();
                                }
                            }
                            if(ok == false)
                                cout << "IBAN incorect !" << endl;
                        }
                    }



                }


            }

            if(clasa == 3) // clasa ContEconomii
            {
                cout << "CONT ECONOMII" << endl;
                cout << endl;
                int c1 = -1;
                cout << "1 - Afisare lista conturi" << endl;
                cout << "2 - Adaugare cont" << endl;
                cout << "3 - Bancomat" << endl;
                cout << "4 - Raport dobanda" << endl;
                cout << "0 - Meniu principal:" << endl;

                cout << "Introduceti cifra: ";
                cin >> c1;
                cout << endl;
                while (c1 >= 1 || c1 <= 3)
                {
                    if(c1 == 1)
                    {
                        if(ConturiEconomii.size() == 0)
                            cout << "Nu avem conturi in lista!" << endl;
                        else
                        {
                            for (int i = 0; i < ConturiEconomii.size(); i++)
                            {
                                cout << ConturiEconomii[i];
                                cout << endl;
                            }
                        }

                    }

                    if(c1 == 2)
                    {
                        ContEconomii cont;
                        cin >> cont;
                        ConturiEconomii.push_back(cont);
                    }

                    if(c1 == 3)
                    {
                        int i;
                        bool ok = false;
                        while(ok == false)
                        {
                            cout << "Introdu ibanul clientului: ";
                            cin >> i;
                            for (int i = 0; i < ConturiEconomii.size(); i++)
                            {
                                if(ConturiEconomii[i].getiban() == i)
                                {
                                    ok = true;
                                    ConturiEconomii[i].AccesareBancomat(ConturiEconomii[i]);
                                }
                            }
                            if(ok == false)
                                cout << "IBAN incorect !" << endl;
                        }
                    }

                    if(c1 == 4)
                    {
                        int i;
                        bool ok = false;
                        while(ok == false)
                        {
                            cout << "Introdu ibanul clientului: ";
                            cin >> i;
                            for (int i = 0; i < ConturiEconomii.size(); i++)
                            {
                                if(ConturiEconomii[i].getiban() == i)
                                {
                                    ok = true;
                                    ConturiEconomii[i].CalculDobanda();
                                }
                            }
                            if(ok == false)
                                cout << "IBAN incorect !" << endl;
                        }
                    }
                    }



                }

            if(clasa == 4) // clasa ContPremium
            {
                cout << "CONT PREMIUM" << endl;
                cout << endl;
                int c1 = -1;
                cout << "1 - Afisare lista conturi" << endl;
                cout << "2 - Adaugare cont" << endl;
                cout << "3 - Bancomat" << endl;
                cout << "4 - Verificare tranzactii gratuite" << endl;
                cout << "0 - Meniu principal:" << endl;

                cout << "Introduceti cifra: ";
                cin >> c1;
                cout << endl;
                while (c1 >= 1 || c1 <= 3)
                {
                    if(c1 == 1)
                    {
                        if(ConturiPremium.size() == 0)
                            cout << "Nu avem conturi in lista!" << endl;
                        else
                        {
                            for (int i = 0; i < ConturiPremium.size(); i++)
                            {
                                cout << ConturiPremium[i];
                                cout << endl;
                            }
                        }

                    }

                    if(c1 == 2)
                    {
                        ContPremium cont;
                        cin >> cont;
                        ConturiPremium.push_back(cont);
                    }

                    if(c1 == 3)
                    {
                        int i;
                        bool ok = false;
                        while(ok == false)
                        {
                            cout << "Introdu ibanul clientului: ";
                            cin >> i;
                            for (int i = 0; i < ConturiPremium.size(); i++)
                            {
                                if(ConturiPremium[i].ContCurent::getiban() == i)
                                {
                                    ok = true;

                                }
                            }
                            if(ok == false)
                                cout << "IBAN incorect !" << endl;
                        }
                     }

                     if(c1 == 4)
                     {
                        int i;
                        bool ok = false;
                        while(ok == false)
                        {
                            cout << "Introdu ibanul clientului: ";
                            cin >> i;
                            for (int i = 0; i < ConturiPremium.size(); i++)
                            {
                                if(ConturiPremium[i].ContCurent::getiban() == i)
                                {
                                    ok = true;
                                    ConturiPremium[i].VerificareTranzactiiGratuite(ConturiPremium[i]);
                                }
                            }
                            if(ok == false)
                                cout << "IBAN incorect !" << endl;
                        }
                     }

                }


            }

            if(clasa == 0)
            {
                start = 0;
            }
        }

    }
    cout << "Program finalizat !";
    return 0;
}
