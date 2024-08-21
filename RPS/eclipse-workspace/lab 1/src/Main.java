import java.util.*; // for Scanner

/**
 * Main class of the application, containing the entry point.
 * @author Alexandr Kategov
 * @version 1.0
 */
public class Main {

    /**
     * Prints the menu with available operations.
     */
    public static void printMenu() {
        System.out.println("1) a + b");
        System.out.println("2) a - b");
        System.out.println("3) a * b");
        System.out.println("4) a / b");
        System.out.println("5) a % b");
        System.out.println("0) Выход");
    }

    /**
     * Prompts the user for input and validates to ensure an integer is entered.
     *
     * @param s the Scanner object used for reading input
     * @return the integer entered by the user
     */
    public static int input(Scanner s) {
        while (s.hasNextInt() == false) { // Continues to prompt the user until a valid integer is entered
            System.out.print("Введите целое число: ");
            s.next(); // Skip the invalid input
        }
        return s.nextInt(); // Return the entered integer
    }

    /**
     * Entry point of the application.
     *
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in); // Create a Scanner object for reading input
        int key; // Variable to store the user's choice of operation

        do {
            System.out.print("Введите число a: ");
            SmallInteger a = new SmallInteger(input(scan));
            System.out.print("Введите число b: ");
            SmallInteger b = new SmallInteger(input(scan));
            System.out.println();
            printMenu();

            key = input(scan);
            switch (key) {
            case 1: // Perform addition and display the result
                System.out.println(a.getValue() + " + " + b.getValue() + " = " + a.add(b).getValue() + "\n");
                break;

            case 2: // Perform subtraction and display the result
                System.out.println(a.getValue() + " - " + b.getValue() + " = " + a.sub(b).getValue() + "\n");
                break;

            case 3: // Perform multiplication and display the result
                System.out.println(a.getValue() + " * " + b.getValue() + " = " + a.mul(b).getValue() + "\n");
                break;

            case 4: // Perform integer division and display the result
                System.out.println(a.getValue() + " / " + b.getValue() + " = " + a.integerDivision(b).getValue() + "\n");
                break;

            case 5: // Perform remainder division and display the result
                System.out.println(a.getValue() + " % " + b.getValue() + " = " + a.remainderDivision(b).getValue() + "\n");
                break;

            default:
                break;
            }
        } while (key != 0); // Continue until the user chooses to exit (0)

        scan.close();
    }
}
