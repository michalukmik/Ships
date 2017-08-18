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
 */

class Plansza
{
private:
    vector  <vector <Pole>> vec; /**< Plansza to tablica dwu wektorowa NxN pol. */
    int n; /**< Rozmiar planszy to (n-1)x(n-1), bo zerowy rząd jest poswiacony na oznaczenia ulatwiajace wybor wspolrzedncyh */
public:
    Plansza(int n_=8):n(n_){stworz(n_);}/**< Iniciuje podstawowa plansze, bez bokow. Plansza ma podstawowe wymiary 8x8. */

    void stworz(int n_)/**< Funkcja odpowiedzialna za tworzenie tablicy wektorowej pol NxN. */
    {
        for(int i=0;i<n_;i++)
        {
            vec.push_back(vector<Pole>());
                for(int j=0;j<n_;j++)
                    {
                        vec[i].push_back((i,j,'.'));
                    }
        }

    }
    void rysuj()
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



int main()
{

    return 0;
}
