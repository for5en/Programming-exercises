using System;

class IntStream
{
    protected int val = 0;

    virtual public int next()
    {
        return val++;
    }

    virtual public bool eos()
    {
        if(val == Int32.MaxValue) return true;
        else return false;
    }

    virtual public void reset()
    {
        val = 0;
    }
}

class FibStream : IntStream
{   
    private int a = 0;
    private int b = 1;
    private int c = 1;

    override public int next()
    {
        a = b;
        b = c;
        c = a + b;
        return a;
    }

    override public bool eos()
    {
        if(a >= Int32.MaxValue-b) return true;
        else return false;
    }

    override public void reset()
    {
        a = 0;
        b = 1;
        c = 1;
    }
}

class RandomStream : IntStream
{
    Random rnd = new Random();

    override public int next()
    {
        val = rnd.Next(Int32.MinValue, Int32.MaxValue);
        return val;
    }

    override public bool eos()
    {
        return false;
    }
}

class RandomWordStream
{
    private FibStream fibs = new FibStream();
    private RandomStream rnd = new RandomStream();

    private string genRandomWord(int len)
    {
        string randomWord = "";

        for(int i=1; i<=len; i++)
        {
            int val = rnd.next();
            if(val < 0) val = -val;
            if(val < 'a') val = val + 'a';
            val %= ('z'-'a'+1);
            val += 'a';
            randomWord = randomWord + (char)val;
            //Console.WriteLine(val);
        }

        return randomWord;
    }

    public string next()
    {
        if(fibs.eos() == true) reset();
        return genRandomWord(fibs.next());
    }

    public void reset()
    {
        fibs.reset();
    }
}

class Program
{
    public static void Main()
    {
        IntStream ints = new IntStream();
        Console.WriteLine(ints.next());
        Console.WriteLine(ints.next());
        Console.WriteLine(ints.next());
        Console.WriteLine(ints.next());
        ints.reset();
        Console.WriteLine(ints.next());
        Console.WriteLine(ints.next());
        Console.WriteLine("\n");
        

        RandomWordStream rndws = new RandomWordStream();
        Console.WriteLine(rndws.next());
        Console.WriteLine(rndws.next());
        Console.WriteLine(rndws.next());
        Console.WriteLine(rndws.next());
        Console.WriteLine(rndws.next());
        Console.WriteLine(rndws.next());
        Console.WriteLine(rndws.next());
        Console.WriteLine(rndws.next());
        Console.WriteLine(rndws.next());
    }
}