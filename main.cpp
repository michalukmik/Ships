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
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;


/** \brief Klasa pole. Pole jest podstawowa "jednostka" na ktora zachodza operacje.
 *Mapa bedzie sie skladac z pol, tak samo jak i statki. Kazde pole powinno posiadac dwie skladowe polozenia, jak i znak ktory okresla
 *typ statku oraz jak jest widoczny na mapie.
 */

class Pole
{
private:
    int x,y;/**< Skladowe polozenia, "x" w poziomi, a "y" w pionie. */
    int typ;/**< Typ pola, na poczatku woda i bok planszy.*/
    char znak;/**< w jaki sposob pole widac na planszy */
public:
    Pole(int x_=0,int y_=0,int typ_=0, char znak_='.'):x(x_),y(y_),typ(typ_),znak(znak_){}/**< Konstruktor klassy pole. */

    void ustaw_polozenie(int x_,int y_){x=x_ ;y=y_;}/**< Ustawienie polozenia */

    void ustaw_typ(int typ_){typ=typ_;}/**< Ustaw typ */
    void ustaw_znak(char znak_){znak=znak_;}

    int zwroc_x(){return x;}/**< Zwraca x */
    int zwroc_y(){return y;}/**< Zwraca y */
    int zwroc_typ(){return typ;}/**< Zwraca typ */
    char zwroc_znak(){return znak;}

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
    int n; /**< Rozmiar planszy to (n-1)x(n-1), bo zerowy rz¹d jest poswiacony na oznaczenia ulatwiajace wybor wspolrzedncyh */
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
                        Pole p(i,j,0,'.');
                        vec[i].push_back(p);
                    }
        }

    }



    void ustaw_bok(bool side,bool num_char)/**< side góra/bok(1/0),num_char cyfry/litery(1/0) */
    {
        vec[0][0].ustaw_znak(' ');
        vec[0][0].ustaw_typ(1);
        if((side==1)&&(num_char==1)) for(int i=1;i<=n;i++){vec[0][i].ustaw_znak(48+i); vec[0][i].ustaw_typ(1);}

        else if((side==1)&&(num_char==0)) for(int i=1;i<=n;i++){vec[0][i].ustaw_znak(64+i); vec[0][i].ustaw_typ(1);}

        else if((side==0)&&(num_char==1)) for(int i=1;i<=n-1;i++){vec[i][0].ustaw_znak(48+i);vec[i][0].ustaw_typ(1);}

        else if((side==0)&&(num_char==0)) for(int i=1;i<=n-1;i++){vec[i][0].ustaw_znak(64+i);vec[i][0].ustaw_typ(1);}

    }


    void ustaw_znak(int x,int y,char a)
    {
        vec[x][y].ustaw_znak(a);
    }
    void ustaw_typ(int x,int y,int typ)
    {
        vec[x][y].ustaw_typ(typ);
    }
    char zwroc_znak(int x, int y)
    {
        vec[x][y].zwroc_znak();
    }

    int zwroc_typ(int x,int y)
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
                        cout << vec[i][j].zwroc_znak()<<" ";
                    }
                    cout << endl;
        }

    }
    }

    void rysuj_typ()
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

      void zaznacz_pudlo_na_mojej(int x, int y)
    {

         if(sprawdz_obecnosc_znaku('o'))
        {
            zmien_znaki_na_znaki('o','.');
            zmien_znaki_na_znaki('O','o');
            vec[x][y].ustaw_znak('O');
        }
        else if(sprawdz_obecnosc_znaku('O'))
            {
                zmien_znaki_na_znaki('O','o');
                vec[x][y].ustaw_znak('O');
            }

        else vec[x][y].ustaw_znak('O');
    }

    bool sprawdz_obecnosc_znaku(char wybrany_znak)
    {
        for(int i=1;i<n;i++)
        {
                for(int j=1;j<n;j++)
                    {
                        if(vec[i][j].zwroc_znak()==wybrany_znak)return true;
                    }
        }
        return false;
    }
     void zmien_znaki_na_znaki(char wybrany_znak_,char nowy_znak)
     {
           for(int i=1;i<n;i++)
        {
                for(int j=1;j<n;j++)
                    {
                        if(vec[i][j].zwroc_znak()==wybrany_znak_)vec[i][j].ustaw_znak(nowy_znak);
                    }
        }
     }
     void zaznacz_pudlo_na_mapie_trafien(int x,int y)
     {
          if(sprawdz_obecnosc_znaku('O'))
            {
                zmien_znaki_na_znaki('O','o');
                vec[x][y].ustaw_znak('O');
            }
        else vec[x][y].ustaw_znak('O');
     }

};

class Statek
{
private:
    vector <Pole> polozenie_masztow; /**< Tablica zawierajaca polozenie czesci statkow */
    char znak_statku;/**< typ char statku  */
    int dlugosc;/**< Ilosc masztow */
    bool kierunek;/**< Pionowo/poziomo (1/0) */
    int strzal;/**< Ilosc strzalow ktore moze oddac statek */
    int zasieg;/**< ilosc pol ktore moze przeplynac statek*/
    bool stan;/**< (1/0) plywa/nie plywa */
    int typ_statku;
    string nazwa_typu_statku;
public:
    Statek(int typ_statku_=3,int dlugosc_=3):typ_statku(typ_statku_),dlugosc(dlugosc_){stworz_statek();stworz_tablice_polozenie_mastow();}

    void stworz_statek()
    {
        if(typ_statku==2)
        {
            nazwa_typu_statku="Motorowka";
            znak_statku='M';
            strzal=0;
            zasieg=2;
            stan=1;
        }
        else if(typ_statku==3)
        {
            nazwa_typu_statku="Niszczyciel";
            znak_statku='N';
            strzal=1;
            zasieg=1;
            stan=1;
        }
         else if(typ_statku==4)
        {
            nazwa_typu_statku="Torpedowiec";
            znak_statku='T';
            strzal=2;
            zasieg=0;
            stan=1;
        }
    }


    void stworz_tablice_polozenie_mastow()
    {
        Pole p;
        for(int i=0;i<dlugosc;i++)
            {
                polozenie_masztow.push_back(p);
                polozenie_masztow[i].ustaw_znak(znak_statku);
                polozenie_masztow[i].ustaw_typ(typ_statku);
            }
    }


    void ustaw_typ_statku(int i){typ_statku=i;stworz_statek();}
    void ustaw_znak_statku(char znak_statku_){znak_statku=znak_statku_;}
    char zwroc_znak_statku(){return znak_statku;}
    void ustaw_dlugosc(int dlugosc_){dlugosc=dlugosc_; stworz_tablice_polozenie_mastow();}
    int zwroc_dlugosc(){return dlugosc;}
    void ustaw_kierunek(bool kierunek_){kierunek=kierunek_;}
    bool zwroc_kierunek(){return kierunek;}
    void ustaw_strzal(int strzal_){strzal=strzal_;}
    int zwroc_strzal(){return strzal;}
    void ustaw_zasieg(int zasieg_){zasieg=zasieg_;}
    int zwroc_zasieg(){return zasieg;}
    void zmien_stan(bool stan_){stan=stan_;}
    int zwroc_stan(){return stan;}
    string zwroc_nazwe_typu_statku(){return nazwa_typu_statku;}

    void rand_start_position(Plansza &p)
    {
        bool a=false;
        while(a==false)
       {
            int x=rand()%(p.size()-1)+1;
            int y=rand()%(p.size()-1)+1;
            kierunek=rand()%2;
            if(can_i_place_ship(p,x,y))
            {
                place_ship(p,x,y);
                a=true;
            }
            else a=false;

        }

    }



    void place_ship(Plansza &p,int x, int y)
    {
        if(kierunek==1) place_ship_vertical(p,x,y);
        else if(kierunek==0) place_ship_horizontal(p,x,y);
    }

    void place_ship_horizontal(Plansza &p,int x, int y)
    {
        for(int i=y;i<y+dlugosc;i++)
        {
            polozenie_masztow[i-y].ustaw_polozenie(x,i);
            p.ustaw_znak(x,i,znak_statku);
            p.ustaw_typ(x,i,typ_statku);
        }
    }

    void place_ship_vertical(Plansza &p,int x, int y)
    {
         for(int i=x;i<x+dlugosc;i++)
        {
            polozenie_masztow[i-x].ustaw_polozenie(i,y);
            p.ustaw_znak(i,y,znak_statku);
            p.ustaw_typ(i,y,typ_statku);
        }
    }


    bool can_i_place_ship(Plansza p, int x, int y)
    {
        if(kierunek==1)
        {
            if(can_i_place_ship_vertically(p,x,y)) return true;
            else return false;
        }
        else if(kierunek==0)
        {
            if(can_i_place_ship_horizontally(p,x,y)) return true;
            else return false;
        }
    }

    bool can_i_place_ship_horizontally(Plansza p, int x, int y)
    {
        if(y-1+dlugosc<p.size())
        {
        for(int i=x-1;(i<=x+1)&&(i<p.size());i++)
         {
             for(int j=y-1;(j<=y+dlugosc)&&(j<p.size());j++)
             {
                 if(p.zwroc_typ(i,j)>1) return false;
             }
         }
         return true;
        }
        else return false;
    }
    bool can_i_place_ship_vertically(Plansza p, int x, int y)
    {
        if(x-1+dlugosc<p.size())
        {
        for(int i=x-1;(i<=x+dlugosc)&&(i<p.size());i++)
         {
             for(int j=y-1;(j<=y+1)&&(j<p.size());j++)
             {
                 if(p.zwroc_typ(i,j)>1) return false;
             }
         }
         return true;
        }
        else return false;
    }
    void wypisz_polzenie_masztow()
    {
        for(int i=0;i<polozenie_masztow.size();i++) cout << polozenie_masztow[i].zwroc_x()<< " " <<polozenie_masztow[i].zwroc_y()<< endl;
    }

    bool sprawdz_czy_moze_ruszyc(Plansza p, int dx, int dy)
    {
        for(int i=0;i<dlugosc;i++) p.ustaw_typ(polozenie_masztow[i].zwroc_x(),polozenie_masztow[i].zwroc_y(),0);
        if(zasieg==0)
        {
            cout << "Ten statek nie porusza sie"<< endl;
            return false;
        }
        else if((kierunek==1)&&(dy==0)&&(dx<=zasieg))
        {
            if(can_i_place_ship(p,polozenie_masztow[0].zwroc_x()+dx,polozenie_masztow[0].zwroc_y()))return true;
            else
            {
                cout << "Ruch niemozliwy"<< endl;
                return false;
            }
        }
        else if((kierunek==0)&&(dx==0)&&(dy<=zasieg))
        {
            if(can_i_place_ship(p,polozenie_masztow[0].zwroc_x(),polozenie_masztow[0].zwroc_y()+dy))return true;
            else
            {
                cout << "Ruch niemozliwy"<< endl;
                return false;
            }
        }
        else
        {
                cout<< "Zle wspolrzedne, prosze podac inne"<< endl;
                return false;
        }

    }

    void rusz_statek(Plansza &p,int dx, int dy)
    {

        for(int i=0;i<dlugosc;i++) p.ustaw_typ(polozenie_masztow[i].zwroc_x(),polozenie_masztow[i].zwroc_y(),0);
        for(int i=0;i<dlugosc;i++) p.ustaw_znak(polozenie_masztow[i].zwroc_x(),polozenie_masztow[i].zwroc_y(),'.');
        place_ship(p,polozenie_masztow[0].zwroc_x()+dx,polozenie_masztow[0].zwroc_y()+dy);

    }

    void statek_trafiony(Plansza &p)
    {
        for(int i=0;i<dlugosc;i++) p.ustaw_typ(polozenie_masztow[i].zwroc_x(),polozenie_masztow[i].zwroc_y(),9);
        for(int i=0;i<dlugosc;i++) p.ustaw_znak(polozenie_masztow[i].zwroc_x(),polozenie_masztow[i].zwroc_y(),'X');
    }
    bool sprawdz_czy_statek_trafiony(Plansza p, int x,int y)
    {
         for(int i=0;i<dlugosc;i++)
         {
             if((polozenie_masztow[i].zwroc_x()==x)&&(polozenie_masztow[i].zwroc_y()==y))
             {
                 stan=0;
                 return true;
             }
         }
         return false;
    }

    bool sprawdz_czy_statek_mozna_wybrac(int x,int y)
     {
         for(int i=0;i<dlugosc;i++)
         {
             if((polozenie_masztow[i].zwroc_x()==x)&&(polozenie_masztow[i].zwroc_y()==y))
             {
                 if(stan==1) return true;
                 else if(stan==0)
                 {
                     cout << "Okret zatopiony, wybierz inny." << endl;
                     return false;
                 }
             }
         }
         return false;
    }

};


class Wspolrzedne
{
private:
    string Napis;
    int x, y;
public:
    Wspolrzedne(string Napis_="00"):Napis(Napis_){}
    void podaj_Napis_i_zapis_xy()
    {
        bool a=true;
         do{
        cin >> Napis;
        if(Napis.size()==2)a=false;
        else cout << "Podano niewlasciwe wspolrzedne, prosze sprobowac ponownie"<<endl;
        }while(a);
        przekonwertuj_napis_na_xy();
    }
    void przekonwertuj_napis_na_xy()
    {
            if((Napis[0]>60)&&(Napis[1]>60)) ustaw_xy(Napis[0]-64,Napis[1]-64);

            else if((Napis[0]>60)&&(Napis[1]<60)) ustaw_xy(Napis[0]-64,Napis[1]-48);

            else if((Napis[0]<60)&&(Napis[1]>60)) ustaw_xy(Napis[0]-48,Napis[1]-64);

            else if((Napis[0]<60)&&(Napis[1]<60)) ustaw_xy(Napis[0]-48,Napis[1]-48);

    }
    void ustaw_xy(int x_,int y_){x=x_;y=y_;}
    int zwroc_x(){return x;}
    int zwroc_y(){return y;}
};

class Gracz
{
private:
    string nazwa_gracza;
    Plansza plansza;
    Plansza plansza_trafien;
    Statek s[4];
    Wspolrzedne napis_na_xy;
    int numer_wybranego_statku;
public:
    Gracz(string nazwa_gracza_="Player"):nazwa_gracza(nazwa_gracza_){inicializuj_poczatkowe_ustawienie();}
    void inicializuj_poczatkowe_ustawienie()
    {
        plansza.ustaw_bok(1,0);
        plansza.ustaw_bok(0,1);
        plansza_trafien.ustaw_bok(1,0);
        plansza_trafien.ustaw_bok(0,1);
        s[0].ustaw_dlugosc(4);
        s[1].ustaw_dlugosc(3);
        s[2].ustaw_dlugosc(2);
        s[3].ustaw_dlugosc(2);
        for(int i=0;i<4;i++)
        {
                s[i].ustaw_typ_statku(rand()%3+2);
                s[i].rand_start_position(plansza);
        }
    }
    void wybierz_statek()
    {
      napis_na_xy.podaj_Napis_i_zapis_xy();
     for(int i=0;i<4;i++)
        {
            if( s[i].sprawdz_czy_statek_mozna_wybrac(napis_na_xy.zwroc_x(),napis_na_xy.zwroc_y()))
                {
                     numer_wybranego_statku=i;
                     break;
                }
            else numer_wybranego_statku=-1;
        }
        if(numer_wybranego_statku>=0)cout << s[numer_wybranego_statku].zwroc_nazwe_typu_statku()<< " zostal/a wybrany."<< endl;
        else
        {
            cout << "Pole jest puste lub statek jest zatopiony, prosze wybrac jeszcze raz."<< endl;
            wybierz_statek();
        }
    }

      void plyn_statkiem()
    {
         if(numer_wybranego_statku>=0)
         {
             if(s[numer_wybranego_statku].zwroc_zasieg()!=0)
             {
                 int x,y;
                 cout << "Prosze podac przesuniecie pionowe i poziome"<< endl;
                 cin >> x >> y;
                 if(s[numer_wybranego_statku].sprawdz_czy_moze_ruszyc(plansza,x,y)) s[numer_wybranego_statku].rusz_statek(plansza,x,y);
                 else
                 {
                     plyn_statkiem();
                 }

             }
             else cout << "Wybrany statek nie porusza sie."<< endl;

         }
    }
    void rysuj_plansz(){plansza.rysuj();}
    void rysuj_plansz_trafien(){plansza_trafien.rysuj();}


   void pojedynczy_strzal(Gracz &gracz2)
   {
       bool pudlo=false;
       napis_na_xy.podaj_Napis_i_zapis_xy();
       for(int i=0;i<4;i++)
       {
           if(gracz2.s[i].sprawdz_czy_statek_trafiony(gracz2.plansza,napis_na_xy.zwroc_x(),napis_na_xy.zwroc_y()))
           {
               cout<< "Statek trafiony i zatopiony!"<< endl;
               gracz2.s[i].statek_trafiony(gracz2.plansza);
               gracz2.s[i].statek_trafiony(plansza_trafien);
               pudlo=false;
               break;

           }
           else pudlo=true;
       }
       if(pudlo)
       {
           cout << "Pudlo"<<endl;
           gracz2.plansza.zaznacz_pudlo_na_mojej(napis_na_xy.zwroc_x(),napis_na_xy.zwroc_y());
           plansza_trafien.zaznacz_pudlo_na_mapie_trafien(napis_na_xy.zwroc_x(),napis_na_xy.zwroc_y());
       }
   }
   void strzelaj(Gracz &gracz2)
   {
      if(s[numer_wybranego_statku].zwroc_strzal()>0)
    {
        cout<<"Masz do oddania "<< s[numer_wybranego_statku].zwroc_strzal() << " strzalow."<<endl;
            for(int i=0;i<s[numer_wybranego_statku].zwroc_strzal();i++)
            {
                cout<< "Prosze podac wspolrzedne ostrzalu:"<<endl;
                pojedynczy_strzal(gracz2);
                rysuj_plansz_trafien();
            }
      }
      else cout<<"Wybrany statek nie strzela"<<endl;
   }
   bool sprawdz_czy_zyje()
   {
       if((s[0].zwroc_stan()==false)&&(s[1].zwroc_stan()==false)&&(s[2].zwroc_stan()==false)&&(s[3].zwroc_stan()==false)) return true;
       else return false;
   }
   void ustaw_nazwe_gracz(string nazwa_){nazwa_gracza=nazwa_;}
   string zwroc_nazwe_gracz(){return nazwa_gracza;}
   void ruch_gracza(Gracz &gracz2)
   {
       cout<<"Ruch "<< nazwa_gracza<<". Nacisnij Enter.."<<endl;
       getch();
       rysuj_plansz();
       cout<< "Prosze wybrac statek"<<endl;
       wybierz_statek();
       plyn_statkiem();
       rysuj_plansz();
       rysuj_plansz_trafien();
       strzelaj(gracz2);
       cout<<"Koniec ruch. Prosze sie zamienic."<<endl;
       Sleep(4000);
       system("cls");
  }
};

class Gra
{
private:
    Gracz gracz1,gracz2;
public:
    Gra(){gracz1.ustaw_nazwe_gracz("Gracz .1.");gracz2.ustaw_nazwe_gracz("Gracz .2.");}
    void gra_wlasciwa()
    {

        do{
            gracz1.ruch_gracza(gracz2);
            if(gracz2.sprawdz_czy_zyje())
            {
                system("cls");
                cout<< "WYGRYWA "<< gracz1.zwroc_nazwe_gracz()<<endl;
                break;
            }
            gracz2.ruch_gracza(gracz1);
            if(gracz1.sprawdz_czy_zyje())
            {
                system("cls");
                cout<< "WYGRYWA "<< gracz2.zwroc_nazwe_gracz()<<endl;
                break;
            }
        }while(true);

    }

};


int main()
{
srand(time(NULL));
Gra g;
g.gra_wlasciwa();
  return 0;
}

