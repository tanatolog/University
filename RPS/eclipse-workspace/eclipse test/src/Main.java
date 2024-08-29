import java.util.*;


public class Main {
	
	public static void printMenu() {
		System.out.println("1) Получить массив простых чисел");
		System.out.println("2) Получить случайное число");
		System.out.println("\n\n0) Выход");
	}

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		
		int key;
		
		do {
			printMenu();
			key = s.nextInt();
			
			switch (key) {
			case 1: 
				System.out.print("Введите размер массива: ");
				int len = s.nextInt();
				int[] arr = Prime.getRandomArray(len);
				
				for(int i = 0; i < len; i++) System.out.print(arr[i] + " ");
				System.out.print("\n");
				break;
			
			case 2:
				System.out.print(Prime.getRandomPrime() + "\n");
				break;

			default:
				break;
			}
		} while (key != 0);
		
		
		s.close();
	}

}
