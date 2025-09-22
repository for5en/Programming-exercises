using System;
using System.Collections;
using System.Collections.Generic;

abstract class Expression : IEnumerable<Expression>
{
    public abstract IEnumerator<Expression> GetEnumerator();
    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }

    public abstract float evaluate(Dictionary<string,float> dane);
    public abstract Expression derivative(string var);
    //public abstract string ToString();
    public abstract bool Equals(Expression obj);

    public static Expression operator +(Expression left, Expression right)
    {
        return new Add(left, right);
    }
    public static Expression operator -(Expression left, Expression right)
    {
        return new Subtract(left, right);
    }
    public static Expression operator *(Expression left, Expression right)
    {
        return new Multiplicate(left, right);
    }
    public static Expression operator /(Expression left, Expression right)
    {
        return new Divide(left, right);
    }
}

class Const : Expression
{
    public float val;

    private Const(float val)
    {
        this.val = val;
    }

    private static Dictionary<float,Const> saved = new Dictionary<float,Const>();
    public static Const GetC(float val)
    {
        if(saved.ContainsKey(val)) return saved[val];
        saved[val] = new Const(val);
        return saved[val];
    }

    public override float evaluate(Dictionary<string,float> dane)
    {
        return val;
    }

    public override Expression derivative(string var)
    {
        return GetC(0);
    }

    public override string ToString()
    {
        return val.ToString();
    }

    public override bool Equals(Expression obj)
    {
        if(this.GetType() != obj.GetType()) return false;
        
        if(this.val != ((Const)obj).val) return false;
        return true;
    }

    public override IEnumerator<Expression> GetEnumerator()
    {
        yield break;
    }
}

class Variable : Expression
{
    public string var;

    public Variable(string var)
    {
        this.var = var;
    }

    public override float evaluate(Dictionary<string,float> dane)
    {
        if(dane.ContainsKey(var) == true) return dane[var];
        else
        {
            Console.WriteLine("BLAD");
            return 0;
        }
    }

    public override Expression derivative(string var)
    {
        if(this.var == var) return new Variable(var);
        else return Const.GetC(0);
    }

    public override string ToString()
    {
        return var;
    }

    public override bool Equals(Expression obj)
    {
        if(this.GetType() != obj.GetType()) return false;
        
        if(this.var != ((Variable)obj).var) return false;
        return true;
    }

    public override IEnumerator<Expression> GetEnumerator()
    {
        yield break;
    }
}

class Add : Expression
{
    Expression left;
    Expression right;

    public Add(Expression left, Expression right)
    {
        this.left = left;
        this.right = right;
    }

    public override float evaluate(Dictionary<string,float> dane)
    {
        if(left == null || right == null)
        {
            Console.WriteLine("BLAD");
            return 0;
        }
        return left.evaluate(dane) + right.evaluate(dane);
    }

    public override Expression derivative(string var)
    {
        if(left == null || right == null)
        {
            Console.WriteLine("BLAD");
            return null;
        }
        return new Add(left.derivative(var), right.derivative(var));
    }

    public override string ToString()
    {
        return "(" + left.ToString() + " + " + right.ToString() + ")";
    }

    public override bool Equals(Expression obj)
    {
        if(this.GetType() != obj.GetType()) return false;
        if(this.left == null || ((Add)obj).left == null) return false;
        if(this.right == null || ((Add)obj).right == null) return false;

        if(this.left.Equals(((Add)obj).left) && this.right.Equals(((Add)obj).right)) return true;
        if(this.right.Equals(((Add)obj).left) && this.left.Equals(((Add)obj).right)) return true;

        return false;
    }

    public override IEnumerator<Expression> GetEnumerator()
    {
        yield return left;
        foreach(Expression exp in left)
        {
            yield return exp;
        }
        yield return right;
        foreach(Expression exp in right)
        {
            yield return exp;
        }
        yield break;
    }
}

class Subtract : Expression
{
    Expression left;
    Expression right;

    public Subtract(Expression left, Expression right)
    {
        this.left = left;
        this.right = right;
    }

    public override float evaluate(Dictionary<string,float> dane)
    {
        if(left == null || right == null)
        {
            Console.WriteLine("BLAD");
            return 0;
        }
        return left.evaluate(dane) - right.evaluate(dane);
    }

    public override Expression derivative(string var)
    {
        if(left == null || right == null)
        {
            Console.WriteLine("BLAD");
            return null;
        }
        return new Subtract(left.derivative(var), right.derivative(var));
    }

    public override string ToString()
    {
        return "(" + left.ToString() + " - " + right.ToString() + ")";
    }

    public override bool Equals(Expression obj)
    {
        if(this.GetType() != obj.GetType()) return false;
        if(this.left == null || ((Subtract)obj).left == null) return false;
        if(this.right == null || ((Subtract)obj).right == null) return false;

        if(this.left.Equals(((Subtract)obj).left) && this.right.Equals(((Subtract)obj).right)) return true;

        return false;
    }

    public override IEnumerator<Expression> GetEnumerator()
    {
        yield return left;
        foreach(Expression exp in left)
        {
            yield return exp;
        }
        yield return right;
        foreach(Expression exp in right)
        {
            yield return exp;
        }
        yield break;
    }
}

class Multiplicate : Expression
{
    Expression left;
    Expression right;

    public Multiplicate(Expression left, Expression right)
    {
        this.left = left;
        this.right = right;
    }

    public override float evaluate(Dictionary<string,float> dane)
    {
        if(left == null || right == null)
        {
            Console.WriteLine("BLAD");
            return 0;
        }
        return left.evaluate(dane) * right.evaluate(dane);
    }

    public override Expression derivative(string var)
    {
        if(left == null || right == null)
        {
            Console.WriteLine("BLAD");
            return null;
        }
        return new Add(new Multiplicate(left.derivative(var), right), new Multiplicate(right.derivative(var), left));
    }

    public override string ToString()
    {
        return "(" + left.ToString() + " * " + right.ToString() + ")";
    }

    public override bool Equals(Expression obj)
    {
        if(this.GetType() != obj.GetType()) return false;
        if(this.left == null || ((Multiplicate)obj).left == null) return false;
        if(this.right == null || ((Multiplicate)obj).right == null) return false;

        if(this.left.Equals(((Multiplicate)obj).left) && this.right.Equals(((Multiplicate)obj).right)) return true;
        if(this.right.Equals(((Multiplicate)obj).left) && this.left.Equals(((Multiplicate)obj).right)) return true;

        return false;
    }

    public override IEnumerator<Expression> GetEnumerator()
    {
        yield return left;
        foreach(Expression exp in left)
        {
            yield return exp;
        }
        yield return right;
        foreach(Expression exp in right)
        {
            yield return exp;
        }
        yield break;
    }
}

class Divide : Expression
{
    Expression left;
    Expression right;

    public Divide(Expression left, Expression right)
    {
        this.left = left;
        this.right = right;
    }

    public override float evaluate(Dictionary<string,float> dane)
    {
        if(left == null || right == null)
        {
            Console.WriteLine("BLAD");
            return 0;
        }
        return left.evaluate(dane) / right.evaluate(dane);
    }

    public override Expression derivative(string var)
    {
        if(left == null || right == null)
        {
            Console.WriteLine("BLAD");
            return null;
        }
        return new Divide(new Subtract(new Multiplicate(left.derivative(var), right), new Multiplicate(right.derivative(var), left)), new Multiplicate(right, right));
    }

    public override string ToString()
    {
        return "(" + left.ToString() + " / " + right.ToString() + ")";
    }

    public override bool Equals(Expression obj)
    {
        if(this.GetType() != obj.GetType()) return false;
        if(this.left == null || ((Divide)obj).left == null) return false;
        if(this.right == null || ((Divide)obj).right == null) return false;

        if(this.left.Equals(((Divide)obj).left) && this.right.Equals(((Divide)obj).right)) return true;

        return false;
    }

    public override IEnumerator<Expression> GetEnumerator()
    {
        yield return left;
        foreach(Expression exp in left)
        {
            yield return exp;
        }
        yield return right;
        foreach(Expression exp in right)
        {
            yield return exp;
        }
        yield break;
    }
}





class Program
{
    public static void Main()
    {
        Dictionary<string,float> dane = new Dictionary<string, float>();
        dane["a"] = 5;
        dane["b"] = 2;
        dane["c"] = -7;
        dane["d"] = 3;

        // ((a + 5) + b) * (c / d)
        Expression expr1 = ((new Variable("a") + Const.GetC(5)) + new Variable("b")) * (new Variable("c") / new Variable("d"));
        Console.WriteLine(expr1.ToString());

        // (c / d) * (b + (5 + a))
        Expression expr2 = (new Variable("c") / new Variable("d")) * (new Variable("b") + (Const.GetC(5) + new Variable("a")));
        Console.WriteLine(expr2.ToString());

        // (d / c) * (b + (5 + a))
        Expression expr3 = (new Variable("d") / new Variable("c")) * (new Variable("b") + (Const.GetC(5) + new Variable("a")));
        Console.WriteLine(expr3.ToString());

        if(expr1.Equals(expr2) == true) Console.WriteLine("ROWNE!");
        if(expr1.Equals(expr3) == false) Console.WriteLine("NIE ROWNE!");
        if(Const.GetC(10) == Const.GetC(10)) Console.WriteLine("10 i 10 maja te same adresy\n");

        foreach(Expression exp in expr1)
        {
            Console.WriteLine(exp.ToString());
        }
    }
}