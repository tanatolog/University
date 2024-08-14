import java.util.*;

public class Main {

	public static void printMenu() {
		System.out.println("1) a + b");
		System.out.println("2) a - b");
		System.out.println("3) a * b");
		System.out.println("4) a / b");
		System.out.println("5) a % b");
		System.out.println("0) Выход");
	}

	public static int input(Scanner s) {
		while (true) {
			if (s.hasNextInt() == false) {
				System.out.print("Введите целое число: ");
				s.next();
			} else {
				return (s.nextInt());
			}
		}
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int key;

		do {
			System.out.print("Введите число a: ");
			SmallInteger a = new SmallInteger(input(scan));
			System.out.print("Введите число b: ");
			SmallInteger b = new SmallInteger(input(scan));
			System.out.println();
			printMenu();

			key = input(scan);
			switch (key) {
			case 1:
				System.out.println(a.getValue() + " + " + b.getValue() + " = " + a.add(b) + "\n");
				break;

			case 2:
				System.out.println(a.getValue() + " - " + b.getValue() + " = " + a.sub(b) + "\n");
				break;

			case 3:
				System.out.println(a.getValue() + " * " + b.getValue() + " = " + a.mul(b) + "\n");
				break;

			case 4:
				System.out.println(a.getValue() + " / " + b.getValue() + " = " + a.integerDivision(b) + "\n");
				break;

			case 5:
				System.out.println(a.getValue() + " % " + b.getValue() + " = " + a.remainderDivision(b) + "\n");
				break;

			default:
				break;
			}
		} while (key != 0);

		scan.close();
	}

}
