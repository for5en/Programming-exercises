import java.util.ArrayList;

class Ksiazka
{
    String tytul;
    ArrayList<Pisarz> autorzy = new ArrayList<Pisarz>();

    Ksiazka(String tytul, Pisarz autor, Pisarz... autorzy)
    {
        // KONSTRUKTOR PRZYJMUJE AUTORA (GLOWNEGO), A DALEJ POZOSTALYCH
        this.tytul = tytul;
        this.autorzy.add(autor);
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

interface Obserwator
{
    void powiadomienie(Ksiazka k);
} 

class Pisarz 
{
    String pseudonim;
    ArrayList<Obserwator> w = new ArrayList<Obserwator>();
    ArrayList<Ksiazka> ksiazki = new ArrayList<Ksiazka>();

    // KONSTRUKTOR PRZYJMUJE PSEUDONIM I KOLEJNO OBSERWATOROW
    Pisarz (String pseudonim, Obserwator... obserwatorzy)
    {
        this.pseudonim = pseudonim;
        for(Obserwator o : obserwatorzy)
        {
            this.w.add(o);
        }
    }

    // FUNKCJA POMOCNICZA KTORA POWIADAMIA WSZYSTKICH OBSERWUJACYCH
    private void powiadom(Ksiazka ksiazka)
    {
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

    // FUNKCJA PRZYJMUJACA TYTUL I AUTOROW (POBOCZNYCH)
    void napisz(String tytul, Pisarz... autorzy)
    {
        // TWORZE NOWA KSIAZKE PODAJAC TYTUL, AUTORA GLOWNEGO I AUTOROW POBOCZNYCH
        Ksiazka ksiazka = new Ksiazka(tytul, this, autorzy);

        // WYWOLUJE FUNKCJE ZE NAPISANO KSIAZKE WE WSZYSTKICH AUTORACH
        this.ejnapisales(ksiazka);
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
    char nazwa;
    
    Wydawnictwo(char nazwa)
    {
        this.nazwa = nazwa;
    }

    void wydajKsiazke(Ksiazka ksiazka) {
        System.out.println("Wydaje ksiazkę " + ksiazka);
    }

    public void powiadomienie(Ksiazka ksiazka)
    {
        if(ksiazka.tytul.charAt(0) == this.nazwa) this.wydajKsiazke(ksiazka);
    }

    public String toString()
    {
        return Character.toString(nazwa);
    }
}

class Czytelnik implements Obserwator
{
    public void powiadomienie(Ksiazka k)
    {
        System.out.println("Nowa ksiazka " + k);
    }
}

class Blog implements Obserwator
{
    public void powiadomienie(Ksiazka k)
    {
        System.out.println("Zapraszam do recenzji " + k);
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
}

public class Literatura
{
    public static void main(String[] args)
    {
        Wydawnictwo a = new Wydawnictwo('T');
        Koneser k = new Koneser("Julka");
        Koneser m = new Koneser("Adam");

        Pisarz pisarz = new Pisarz("Litwos", a);
        Pisarz ja = new Pisarz("Orzel", k, m);
        
        pisarz.napisz("Trylogia");
        ja.napisz("TAISD", pisarz);
        
    }
}