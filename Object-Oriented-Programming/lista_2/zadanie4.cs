using System;
using System.Collections.Generic;

class KolejneSlowaFibonacciego
{
    protected string a = "";
    protected string b = "";
    protected string c = "";

    public KolejneSlowaFibonacciego()
    {
        a = "a";
        b = "b";
    }

    public KolejneSlowaFibonacciego(string a, string b)
    {
        this.a = a;
        this.b = b;
    }

    public string next()
    {
        string res = a;
        c = b + a;
        a = b;
        b = c;

        return res;
    }
}



class JakiesSlowoFibonacciego
{
    protected string a = "";
    protected string b = "";
    protected string c = "";
    protected List<string> policzone = new List<string> {};
    protected int dl = 3;

    public JakiesSlowoFibonacciego()
    {
        a = "a";
        b = "b";
        policzone.Add(a);
        policzone.Add(b);
        policzone.Add(b+a);
    }

    public JakiesSlowoFibonacciego(string a, string b)
    {
        this.a = a;
        this.b = b;
        policzone.Add(a);
        policzone.Add(b);
        policzone.Add(b+a);
    }

    public string slowo(int id)
    {
        if(dl<id)
        {
            c = policzone[dl-1];
            b = policzone[dl-2];
            a = policzone[dl-3];
            
            for(int i=dl; i<id; i++)
            {
                a = b;
                b = c;
                c = b+a;
                policzone.Add(c);
            }
            dl = id;
        }

        return policzone[id-1];
    }
}

class Program
{
    public static void Main()
    {
        KolejneSlowaFibonacciego kfibbase = new KolejneSlowaFibonacciego();
        for(int i=1; i<=10; i++) Console.WriteLine(kfibbase.next());
        Console.WriteLine("\n");

        KolejneSlowaFibonacciego kfib = new KolejneSlowaFibonacciego("xax", "yy");
        for(int i=1; i<=10; i++) Console.WriteLine(kfib.next());
        Console.WriteLine("\n");

        JakiesSlowoFibonacciego jfibbase = new JakiesSlowoFibonacciego();
        Console.WriteLine(jfibbase.slowo(1));
        Console.WriteLine(jfibbase.slowo(3));
        Console.WriteLine(jfibbase.slowo(5));
        Console.WriteLine(jfibbase.slowo(10));
        Console.WriteLine("\n");

        JakiesSlowoFibonacciego jfib = new JakiesSlowoFibonacciego("xax","yy");
        Console.WriteLine(jfib.slowo(1));
        Console.WriteLine(jfib.slowo(3));
        Console.WriteLine(jfib.slowo(5));
        Console.WriteLine(jfib.slowo(10));
        Console.WriteLine("\n");
    }
}