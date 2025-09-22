import javax.swing.*;
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.*;
import java.awt.event.*;

class Ksiazka implements ActionListener
{
    String tytuł;
    String autor;
    int wydanie;
  
    public Ksiazka(String t, String a, int w)
    {
        this.tytuł = t; this.autor = a; this.wydanie = w;
    }
  
    public String toString()
    {
        return "Książka " + this.tytuł + " " + this.autor + " " + this.wydanie;
    }
  
    private void createGUI()
    {
        JFrame frame = new JFrame("Edycja książki");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Container kontener = frame.getContentPane();
        GridLayout layout = new GridLayout(4, 2);
        // FlowLayout layout = new FlowLayout();
        kontener.setLayout(layout);
    
        JLabel autor_etykieta = new JLabel("Autor");
        kontener.add(autor_etykieta);
        JTextField autor = new JTextField(this.autor, 40);
        // autor_etykieta.setLabelFor(autor);
        kontener.add(autor);
    
        JLabel tytuł_etykieta = new JLabel("Tytuł");
        kontener.add(tytuł_etykieta);
        JTextField tytuł = new JTextField(this.tytuł, 40);
        kontener.add(tytuł);
       
        JLabel wydanie_etykieta = new JLabel("Wydanie");
        kontener.add(wydanie_etykieta);
        JTextField wydanie = new JTextField(Integer.toString(this.wydanie), 40);
        kontener.add(wydanie);
    
        JButton b = new JButton("Zapisz");
        b.addActionListener(this);
        kontener.add(b);

        frame.pack();
        frame.setVisible(true);
    }
  
   
    public void actionPerformed(ActionEvent e)
    {
        System.out.println("Naciśnięto przycisk");
    }
  
    public void Edycja()
    {
        this.createGUI();
    }
}


/*
 * Wykorzystanie kontrolki:
 *  void createGUI(Ksiazka k)
    {
        JFrame frame = new JFrame("Edycja danych");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Container kontener = frame.getContentPane();
        kontener.setLayout(new FlowLayout());

        KsiazkaSwing ks = new KsiazkaSwing(k);
        kontener.add(ks);

        JButton b = new JButton("Zapisz");
        b.addActionListener(e -> System.out.println("Naciśnięto przycisk"));
        b.addActionListener(ks);
        kontener.add(b);

        frame.pack();
        frame.setVisible(true);
    }
 */
class KsiazkaSwing extends JPanel implements ActionListener
{
    private JTextField tytuł;
    private JTextField autor;
    private JTextField wydanie;

    Ksiazka model;
  
    public KsiazkaSwing(Ksiazka k)
    {
        // swingowe
        model = k;
        JLabel autor_etykieta = new JLabel("Autor");
        this.autor = new JTextField(k.autor, 40);
        // autor_etykieta.setLabelFor(autor);
        JLabel tytuł_etykieta = new JLabel("Tytuł");
        this.tytuł = new JTextField(k.tytuł, 40);
        JLabel wydanie_etykieta = new JLabel("Wydanie");
        this.wydanie = new JTextField(Integer.toString(k.wydanie), 40);

        setLayout(new GridLayout(4, 2));
        add(autor_etykieta);
        add(autor);
        add(tytuł_etykieta);
        add(tytuł);
        add(wydanie_etykieta);
        add(wydanie);
  }

    public void actionPerformed(ActionEvent e)
    {
        // Zapisz zmiany do obiektu Ksiazka
        model.tytuł = tytuł.getText();
        System.out.println("Zmiana tytułu: " + tytuł.getText());
        model.autor = autor.getText();
        System.out.println("Zmiana autora: " + tytuł.getText());
        model.wydanie = Integer.parseInt(wydanie.getText());
        System.out.println("Zapisano zmiany: " + model);
        // Można dodać kod do aktualizacji obiektu Ksiazka
    }   
}