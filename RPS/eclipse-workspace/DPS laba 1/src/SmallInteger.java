public class SmallInteger {
	private int value;
	private static final int MAX_VALUE = 10000;
	private static final int MIN_VALUE = -10000;

	public SmallInteger(int value) {
		if (value > MAX_VALUE || value < MIN_VALUE) {
			throw new RuntimeException("Value out of range");
		}
		this.value = value;
	}

	public SmallInteger(SmallInteger other) {
		this.value = other.value;
	}

	public SmallInteger add(SmallInteger arg) {
		int result = this.value + arg.value;
		if (result > MAX_VALUE || result < MIN_VALUE) {
			throw new RuntimeException("Value out of range");
		}
		return new SmallInteger(result);
	}

	public SmallInteger sub(SmallInteger arg) {
		int result = this.value - arg.value;
		if (result > MAX_VALUE || result < MIN_VALUE) {
			throw new RuntimeException("Value out of range");
		}
		return new SmallInteger(result);
	}

	public SmallInteger mul(SmallInteger arg) {
		int result = this.value * arg.value;
		if (result > MAX_VALUE || result < MIN_VALUE) {
			throw new RuntimeException("Value out of range");
		}
		return new SmallInteger(result);
	}

	public SmallInteger integerDivision(SmallInteger arg) {
		if (arg.value == 0) {
			throw new ArithmeticException("Division by zero");
		}
		int result = this.value / arg.value;
		return new SmallInteger(result);
	}

	public SmallInteger remainderDivision(SmallInteger arg) {
		if (arg.value == 0) {
			throw new ArithmeticException("Division by zero");
		}
		int result = this.value % arg.value;
		return new SmallInteger(result);
	}

	public int getValue() {
		return this.value;
	}

	public String toString() {
		return String.valueOf(this.value);
	}
}