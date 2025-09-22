using System;
using System.Collections.Generic;

abstract class Expression
{
    public abstract int evaluate(Dictionary<string,int> dane);
    public abstract Expression derivative(string var);
    public abstract string ToString(Expression obj);
}

class Operator : Expression
{
    protected string val;
    protected Expression l;
    protected Expression r;

    public Operator()
    {
        val = "";
        l = null;
        r = null;
    }

    public Operator(string newVal)
    {
        val = newVal;
        l = null;
        r = null;
    }

    public Operator(string newVal, Expression newL, Expression newR)
    {
        val = newVal;
        l = newL;
        r = newR;
    }

    public override int evaluate(Dictionary<string,int> dane)
    {
        if(l == null || r == null) 
        {
            Console.WriteLine("BLAD");
            return 0;
        }

        switch(val)
        {
            case "+":
                return l.evaluate(dane) + r.evaluate(dane);
            case "-":
                return l.evaluate(dane) - r.evaluate(dane);
            case "*":
                return l.evaluate(dane) * r.evaluate(dane);
            case "/":
                return l.evaluate(dane) / r.evaluate(dane);
            default:
                Console.WriteLine("BLAD");
                return 0;
        }
    }

    public override Expression derivative(string var)
    {
        if(l == null || r == null) 
        {
            Console.WriteLine("BLAD");
            return new Variable("0");
        }

        switch(val)
        {
            case "+":
                return new Operator("+", l.derivative(var), r.derivative(var));
            case "-":
                return new Operator("-", l.derivative(var), r.derivative(var));
            case "*":
                return new Operator("+", new Operator("*", l.derivative(var), r), new Operator("*", l, r.derivative(var)));
            case "/":
                return new Operator("/", new Operator("-", new Operator("*", l.derivative(var), r), new Operator("*", l, r.derivative(var))), new Operator("*", r, r));
            default:
                Console.WriteLine("BLAD");
                return new Variable("0");
        }
    }

    public override string ToString( obj)
}

class Variable : Expression
{
    protected string val;
    public Variable(string newVal)
    {
        val = newVal;
    }

    public override int evaluate(Dictionary<string,int> dane)
    {
        int result;
        if(int.TryParse(val, out result) == true) return result; // jesli mamy wartosc liczbowa to ja zwroc
        else if(dane.ContainsKey(val) == true) return dane[val]; // jesli jest to zmienna sprawdz czy ma przypisana wartosc i zwroc
        else return 0; // jesli jest to zmienna bez przypisanej wartosci to 0
    }

    public override Expression derivative(string var)
    {
        if(val == var) return new Variable("1");
        else return new Variable("0");
    }
}


class Program
{
    public static void Main()
    {
        ////////////////////////////////////////// TESTOWANIE EVALUATE //////////////////////////////////////////

        // (a + (b*c)) - ((d-3) * e)

        Variable a = new Variable("a");
        Variable b = new Variable("b");
        Variable c = new Variable("c");
        Variable d = new Variable("d");
        Variable e = new Variable("e");
        Variable three = new Variable("3");

        Operator minus = new Operator("-", d, three); // - po prawej
        Operator multl = new Operator("*", b, c); // * po lewej
        Operator plus = new Operator("+", a, multl); // + po lewej
        Operator mult = new Operator("*", minus, e); // * po prawej
        Operator root = new Operator("-", plus, mult); // - glowny

        Dictionary<string,int> dict = new Dictionary<string, int>();

        dict["a"] = 1;
        dict["b"] = 3;
        dict["c"] = -1;
        dict["d"] = 1;
        dict["e"] = 2;

        // (1 + (3*(-1))) - ((1-3) * 2) = (1 - 3) - (-4) = -2 + 4 = 2
        Console.WriteLine(root.evaluate(dict));


        ////////////////////////////////////////// TESTOWANIE POCHODNEJ //////////////////////////////////////////

        // ((2*x) + (((x*x) * x)) * (x + 5)) = 2x + (x^3 * (x+5)) = 2x + x^4 + 5x^3 = x^4 + 5x^3 + 2x

        Variable x = new Variable("x");
        Variable two = new Variable("2");
        Variable five = new Variable("5");

        Operator mult1 = new Operator("*", two, x);
        Operator mult2 = new Operator("*", x, x);
        Operator mult3 = new Operator("*", mult2, x);
        Operator plus2 = new Operator("+", x, five);
        Operator mult4 = new Operator("*", mult3, plus2);
        Operator plus1 = new Operator("+", mult1, mult4);

        dict["x"] = 4;

        // (x^4 + 5x^3 + 2x)' = 4x^3 + 15x^2 + 2 = 4*64 + 15*16 + 2 = 498
        Console.WriteLine(plus1.derivative("x").evaluate(dict));


        ////////////////////////////////////////// TESTOWANIE POCHODNEJ Z NIEWIADOMYMI //////////////////////////////////////////

        // (((x*x) * x) * (x + b)) / (a*x) = (x + b)x^3 / ax = (x^4 + bx^3) / ax = (x^3 + bx^2) / a
        
        mult1 = new Operator("*", a, x);
        mult2 = new Operator("*", x, x);
        mult3 = new Operator("*", mult2, x);
        plus2 = new Operator("+", x, b);
        mult4 = new Operator("*", mult3, plus2);
        Operator div = new Operator("/", mult4, mult1);

        dict["a"] = 5;
        dict["b"] = -2;
        dict["x"] = 3;

        // ((x^3 + bx^2) / a)' = ((x^2 * (x - 2)) / 5)' = x(3x - 4) / 5 = 3 * 5 / 5 = 3

        Console.WriteLine(div.derivative("x").evaluate(dict));
    }
}
