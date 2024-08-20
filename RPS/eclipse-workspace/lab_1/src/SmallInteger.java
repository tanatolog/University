/**
 * Class for handling integers within the range [-10000, 10000].
 * 
 * @author Alexandr Kategov
 * @version 1.0
 */
public class SmallInteger {
    private int value; // Stores the value of the number
    private static final int MAX_VALUE = 10000; // Maximum allowable value
    private static final int MIN_VALUE = -10000; // Minimum allowable value

    /**
     * Primary constructor that accepts an integer and checks if it is within the valid range.
     *
     * @param value the integer value to be stored
     * @throws RuntimeException if the value is out of the valid range [-10000, 10000]
     */
    public SmallInteger(int value) {
        if (value > MAX_VALUE || value < MIN_VALUE) {
            throw new RuntimeException("Value out of range");
        }
        this.value = value;
    }

    /**
     * Copy constructor that creates a new object based on an existing one.
     *
     * @param other the SmallInteger object to copy
     */
    public SmallInteger(SmallInteger other) {
        this(other.value); // Calls the primary constructor
    }

    /**
     * Adds two SmallInteger objects.
     *
     * @param arg the SmallInteger to add
     * @return a new SmallInteger containing the result of the addition
     * @throws RuntimeException if the result is out of the valid range [-10000, 10000]
     */
    public SmallInteger add(SmallInteger arg) {
        int result = this.value + arg.value;
        if (result > MAX_VALUE || result < MIN_VALUE) {
            throw new RuntimeException("Result out of range");
        }
        return new SmallInteger(result);
    }

    /**
     * Subtracts one SmallInteger object from another.
     *
     * @param arg the SmallInteger to subtract
     * @return a new SmallInteger containing the result of the subtraction
     * @throws RuntimeException if the result is out of the valid range [-10000, 10000]
     */
    public SmallInteger sub(SmallInteger arg) {
        int result = this.value - arg.value;
        if (result > MAX_VALUE || result < MIN_VALUE) {
            throw new RuntimeException("Result out of range");
        }
        return new SmallInteger(result);
    }

    /**
     * Multiplies two SmallInteger objects.
     *
     * @param arg the SmallInteger to multiply by
     * @return a new SmallInteger containing the result of the multiplication
     * @throws RuntimeException if the result is out of the valid range [-10000, 10000]
     */
    public SmallInteger mul(SmallInteger arg) {
        int result = this.value * arg.value;
        if (result > MAX_VALUE || result < MIN_VALUE) {
            throw new RuntimeException("Result out of range");
        }
        return new SmallInteger(result);
    }

    /**
     * Performs integer division of one SmallInteger object by another.
     *
     * @param arg the SmallInteger to divide by
     * @return a new SmallInteger containing the result of the division
     * @throws ArithmeticException if division by zero occurs
     */
    public SmallInteger integerDivision(SmallInteger arg) {
        if (arg.value == 0) {
            throw new ArithmeticException("Division by zero");
        }
        int result = this.value / arg.value;
        return new SmallInteger(result);
    }

    /**
     * Finds the remainder of the division of one SmallInteger object by another.
     *
     * @param arg the SmallInteger to divide by
     * @return a new SmallInteger containing the remainder of the division
     * @throws ArithmeticException if division by zero occurs
     */
    public SmallInteger remainderDivision(SmallInteger arg) {
        if (arg.value == 0) {
            throw new ArithmeticException("Division by zero");
        }
        int result = this.value % arg.value;
        return new SmallInteger(result);
    }

    /**
     * Gets the current value.
     *
     * @return the integer value stored in this SmallInteger
     */
    public int getValue() {
        return this.value;
    }
}