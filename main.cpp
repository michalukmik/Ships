/** \mainpage
\brief Gra w statki dla dwoch osob.
 *Gra w statki dla dwoch osob. W grze wystepuja rozne typy statkow, ktore moga sie przemieszczaczacz i strzelac.
 *  Raz trafiony statek jest unieszkodliwiony, tzn. nie moze wykonywac ruchu, ale zajmiuje teren.
 * Statki nie mogą znajdować się na sasiadujacych polach.
 * Ruch gracza polega na wybraniu statku i w zaleznosci od typu ,przemieszczenie ,a nastepnie oddanie strzalu.
 *Gra konczy sie jak ktorys z graczy straci wszytskie statki.
 *
 *Plasza powinna mieć wymiary 8x8, z mozliwoscia zmiany rozmiaru. Jeden bok powinnien zawierac litery albabetu, a drugi cyfry.
 *Pole powinno sie wybierac podajac podajac kordynaty np.: A5.
 *Nowe klasy statkow powinny byc latwo dodawalne.
 *Statki poruszaja sie tylko w plaszczyznie w ktorej zostaly ustawione na poczatku.
 *Ulozenie poczatkowe statkow jest losowane.
 *
 */


#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

/** \brief Klasa pole. Pole jest podstawowa "jednostka" na ktora zachodza operacje.
 *Mapa bedzie sie skladac z pol, tak samo jak i statki. Kazde pole powinno posiadac dwie skladowe polozenia, jak i znak ktory okresla
 *typ statku oraz jak jest widoczny na mapie.
 */

class Pole
{
private:
    int x,y;/**< Skladowe polozenia, "x" w poziomi, a "y" w pionie. */
    char typ;/**< Typ pola, na poczatku woda i bok planszy.*/
public:
    Pole(int x_=0,int y_=0,int typ_='.'):x(x_),y(y_),typ(typ_){}/**< Konstruktor klassy pole. */

    void ustaw_polozenie(int x_,int y_){x=x_ ;y=y_;}/**< Ustawienie polozenia */

    void ustaw_typ(char typ_){typ=typ_;}/**< Ustaw typ */

    int zwroc_x(){return x;}/**< Zwraca x */
    int zwroc_y(){return y;}/**< Zwraca y */
    char zwroc_typ(){return typ;}/**< Zwraca typ */
};

/** \brief Klasa plansza jak nazwa wskazuje sluzy stworzeniu plansz.
 *Planasz o wymiarach NxN składa się z tablicy wektorowej zawiarajacej Pola.
 *W klasie powinno sie znajdowac rysowanie planszy, z uwzglednieniem funkcji rysujacej boki, jak rowniez system wybierania
 *pol i zmieniania ich typow, co bedzie niezbedne w klasie statek.
 *Plansza nie powinna być większ niz n=10, gdyz psuje funkcje tlumacz.
 */

class Plansza
{
private:
    vector  <vector <Pole>> vec; /**< Plansza to tablica dwu wektorowa NxN pol. */
    int n; /**< Rozmiar planszy to (n-1)x(n-1), bo zerowy rząd jest poswiacony na oznaczenia ulatwiajace wybor wspolrzedncyh */
public:
    Plansza(int n_=9):n(n_){stworz(n_);}/**< Iniciuje podstawowa plansze, z bokami bokow. Plansza ma podstawowe wymiary 9x9(pamietac o bokach) . */

    int size(){return n;}
    void stworz(int n_)/**< Funkcja odpowiedzialna za inicializowanie tablicy wektorowej pol NxN. */
    {
        for(int i=0;i<n_;i++)
        {
            vec.push_back(vector<Pole>());
                for(int j=0;j<n_;j++)
                    {
                        Pole p(i,j,'.');
                        vec[i].push_back(p);
                    }
        }

    }



    void ustaw_bok(bool side,bool num_char)/**< side góra/bok(1/0),num_char cyfry/litery(1/0) */
    {
        vec[0][0].ustaw_typ(' ');
        if((side==1)&&(num_char==1)) for(int i=1;i<=n;i++)vec[0][i].ustaw_typ(48+i);

        else if((side==1)&&(num_char==0)) for(int i=1;i<=n;i++)vec[0][i].ustaw_typ(64+i);

        else if((side==0)&&(num_char==1)) for(int i=1;i<=n-1;i++)vec[i][0].ustaw_typ(48+i);

        else if((side==0)&&(num_char==0)) for(int i=1;i<=n-1;i++)vec[i][0].ustaw_typ(64+i);

    }

    void wybierz_napisem(string napis, char a)/**< wybieranie wspolrzednych za pomoca np.:A1 na x,y, dla maks n=10, zmien typ na a */
    {
        if(napis.size()==2)
        {
            if((napis[0]>60)&&(napis[1]>60)) wybierz(napis[0]-64,napis[1]-64,a);

            else if((napis[0]>60)&&(napis[1]<60)) wybierz(napis[0]-64,napis[1]-48,a);

            else if((napis[0]<60)&&(napis[1]>60)) wybierz(napis[0]-48,napis[1]-64,a);

            else if((napis[0]<60)&&(napis[1]<60)) wybierz(napis[0]-48,napis[1]-48,a);
        }

        else cout << "Podano nieprawidlowe wspolrzedne"<< endl;
    }

    void wybierz(int x,int y,char a)
    {
        vec[x][y].ustaw_typ(a);
    }
    char zwroc_typ(int x, int y)
    {
        vec[x][y].zwroc_typ();
    }


    void rysuj()/**< Funkcja odpowiedzialna za rysowanie planszy */
    {
       {
        for(int i=0;i<n;i++)
        {
                for(int j=0;j<n;j++)
                    {
                        cout << vec[i][j].zwroc_typ()<<" ";
                    }
                    cout << endl;
        }

    }
    }


};

/** \brief Klasa statek odpowiada ustawienie(poczatkowe rowniez), ruch, strzal, zatopienie.
 *
 */


class Statek
{
private:
    vector <Pole> polozenie_masztow; /**< Tablica zawierajaca polozenie czesci statkow */
    char rodzaj;/**< typ char statku  */
    int dlugosc;/**< Ilosc masztow */
    bool kierunek;/**< Pionowo/poziomo (1/0) */
    int strzal;/**< Ilosc strzalow ktore moze oddac statek */
    int zasieg;/**< ilosc pol ktore moze przeplynac statek*/
    bool stan;/**< (1/0) plywa/nie plywa */
public:
    Statek(char rodzaj_='S',int dlugosc_=3,int strzal_=1,int zasieg_=0):rodzaj(rodzaj_),dlugosc(dlugosc_),strzal(strzal_),zasieg(zasieg_){stworz_statek();}

    void stworz_statek()
    {
        Pole p;
        for(int i=0;i<dlugosc;i++)
            {
                polozenie_masztow.push_back(p);
                polozenie_masztow[i].ustaw_typ(rodzaj);
            }
    }



    void ustaw_rodzaj(char rodzaj_){rodzaj=rodzaj_;}
    char zwroc_rodzaj(){return rodzaj;}
    void ustaw_dlugosc(int dlugosc_){dlugosc=dlugosc_;}
    int zwroc_dlugosc(){return dlugosc;}
    void ustaw_kierunek(bool kierunek_){kierunek=kierunek_;}
    void ustaw_strzal(int strzal_){strzal=strzal_;}
    void ustaw_zasieg(int zasieg_){zasieg=zasieg_;}
    void zmien_stan(bool stan_){stan=stan_;}

    void rand_start_xy(Plansza &p)
    {
        for(int i=0;i<dlugosc;i++) p.wybierz(9,9,rodzaj);
    }

    bool can_i_place_ship(Plansza p, int dx, int dy)
    {

    }
    bool can_i_place_ship_vertical(Plansza p,int dx, int dy)
    {
        bool a;
        for(int i=dx-1;(i<=dx+2)&&(i<=p.size());i++)
        {
            for(int j=dy-1;(i<=dy-1+dlugosc)&&(i<=p.size());i++)
            {
                if(p.zwroc_typ(dx,dy)!='S')
            }
        }
    }

};

int main()
{

  Plansza p;
  p.ustaw_bok(1,0);
  p.ustaw_bok(0,1);
  p.rysuj();


  return 0;
}
