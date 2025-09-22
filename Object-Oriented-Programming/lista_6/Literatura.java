import java.util.ArrayList;
import java.util.Comparator;
import java.util.Collections;

interface Obserwator
{
    void powiadomienie(Ksiazka k);
    int priority();
} 

class porownajObs implements Comparator <Obserwator>
{
    public int compare(Obserwator a, Obserwator b)
    {
        if(a.priority() < b.priority()) return 1;
        else return -1;
    }
}

class Ksiazka
{
    String tytul;
    int rokpowstania;
    ArrayList<Pisarz> autorzy = new ArrayList<Pisarz>();

    Ksiazka(String tytul, int rokpowstania, ArrayList<Pisarz> autorzy)
    {
        // KONSTRUKTOR PRZYJMUJE AUTOROW
        this.tytul = tytul;
        this.rokpowstania = rokpowstania;
        for(Pisarz pisarz : autorzy)
        {
            this.autorzy.add(pisarz);
        }
    }

    public String toString()
    {
        // TWORZE JEDEN NAPIS Z AUTORAMI
        String autorstwo = "";
        for(Pisarz pisarz : autorzy)
        {
            autorstwo = autorstwo + pisarz + ", ";
        }
        
        // WYPISUJE AUTOROW BEZ PRZECINKA NA KONCU
        return tytul + " autorstwa " + autorstwo.substring(0, autorstwo.length()-2);
    }
}

class Pisarz 
{
    String pseudonim;
    int rokurodzenia;

    ArrayList<Obserwator> w = new ArrayList<Obserwator>();
    ArrayList<Ksiazka> ksiazki = new ArrayList<Ksiazka>();

    // KONSTRUKTOR PRZYJMUJE PSEUDONIM I KOLEJNO OBSERWATOROW
    Pisarz (String pseudonim, int rokurodzenia, Obserwator... obserwatorzy)
    {
        this.pseudonim = pseudonim;
        this.rokurodzenia = rokurodzenia;
        for(Obserwator o : obserwatorzy)
        {
            this.w.add(o);
        }
    }

    // FUNKCJA POMOCNICZA KTORA POWIADAMIA WSZYSTKICH OBSERWUJACYCH
    private void powiadom(Ksiazka ksiazka)
    {
        Collections.sort(w, new porownajObs());
        for(Obserwator o : w)
        {
            o.powiadomienie(ksiazka);
        }
    }
    
    // FUNKCJA POMOCNICZA KTORA DODAJE KSIAZKE DO ZBIORU NAPISANYCH I POWIADAMIA OBSERWUJACYCH
    public void ejnapisales(Ksiazka ksiazka)
    {
        this.ksiazki.add(ksiazka);
        powiadom(ksiazka);
    }

    // FUNKCJA PRZYJMUJACA TYTUL I AUTOROW
    void napisz(String tytul, int rokpowstania, Pisarz... autorzyTab)
    {
        ArrayList<Pisarz> autorzy = new ArrayList<Pisarz>();
        for(Pisarz autor : autorzyTab) autorzy.add(autor);
        autorzy.add(this);

        // TWORZE NOWA KSIAZKE PODAJAC TYTUL i AUTOROW
        Ksiazka ksiazka = new Ksiazka(tytul, rokpowstania, autorzy);

        // WYWOLUJE FUNKCJE ZE NAPISANO KSIAZKE WE WSZYSTKICH AUTORACH
        for(Pisarz autor : autorzy)
        {
            autor.ejnapisales(ksiazka);
        }
    }

    public String toString()
    {
        return pseudonim;
    }

    public void addObs(Obserwator o)
    {
        w.add(o);
    }
    public void delObs(Obserwator o)
    {
        w.remove(o);
    }
}

class Wydawnictwo implements Obserwator 
{
    String nazwa;
    int rokpowstania;
    
    Wydawnictwo(String nazwa, int rokpowstania)
    {
        this.nazwa = nazwa;
        this.rokpowstania = rokpowstania;
    }

    void wydajKsiazke(Ksiazka ksiazka) 
    {
        System.out.println("Wydaje ksiazkę " + ksiazka);
    }

    public void powiadomienie(Ksiazka ksiazka)
    {
        if(ksiazka.tytul.charAt(0) == nazwa.charAt(0)) this.wydajKsiazke(ksiazka);
    }

    public String toString()
    {
        return nazwa;
    }

    public int priority()
    {
        return 1;
    }
}

class Czytelnik implements Obserwator
{
    public void powiadomienie(Ksiazka k)
    {
        System.out.println("Nowa ksiazka " + k);
    }

    public int priority()
    {
        return 2;
    }
}

class Blog implements Obserwator
{
    String nazwa;

    Blog(String nazwa)
    {
        this.nazwa = nazwa;
    }

    public void powiadomienie(Ksiazka k)
    {
        System.out.println("Zapraszam do recenzji " + k);
    }

    public int priority()
    {
        return 3;
    }
}

class Koneser implements Obserwator
{
    String imie;

    Koneser(String imie)
    {
        this.imie = imie;
    }

    public void powiadomienie(Ksiazka k)
    {
        if(imie.charAt(imie.length()-1) == 'a') System.out.println("Pani " + imie + ", serdecznie polecam nowa ksiazke " + k);
        else System.out.println("Panie " + imie + ", serdecznie polecam nowa ksiazke " + k);
    }

    public int priority()
    {
        return 4;
    }
}

public class Literatura
{
    public static void main(String[] args)
    {
        Wydawnictwo a = new Wydawnictwo("Tojestwydawnictwo",1999);
        Koneser k = new Koneser("Julka");
        Koneser m = new Koneser("Adam");
        Blog b = new Blog("blooog");

        Pisarz pisarz = new Pisarz("Litwos",2000, a);
        Pisarz ja = new Pisarz("Orzel",2005, k, m, b);
        
        pisarz.napisz("Trylogia", 2000);
        System.out.println("\n");
        ja.napisz("TAISD", 2020, pisarz);
        
    }
}