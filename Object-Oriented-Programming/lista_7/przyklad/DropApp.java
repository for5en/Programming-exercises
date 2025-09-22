import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import java.awt.Container;  
import java.awt.FlowLayout;

class DropExample extends JFrame {

    String[] dniTyg = { "Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela" };

    public DropExample() {
        setTitle("Dropp Example");
        // setSize(400, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        Container container = getContentPane();
        container.setLayout(new FlowLayout());
        // container.setLayout(new GridLayout(0, 1));
        JComboBox<String> comboBox = new JComboBox<>(dniTyg);
        // comboBox.setEditable(true);
        JLabel label = new JLabel("Nic nie wybrano");
        comboBox.addActionListener(e -> {
            String selectedItem = (String) comboBox.getSelectedItem();
            label.setText("Wybrano: " + selectedItem);
        });
        container.add(comboBox);
        container.add(label);
        setSize(400, 200);
        setVisible(true);
    }
}

public class DropApp {
    public static void main(String[] args) {
        DropExample example = new DropExample();
        example.setVisible(true);
    }
}