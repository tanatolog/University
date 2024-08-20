import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.math.BigInteger;

public class CalculatorGUI extends JFrame { //Сделать прием аргументов, ф. TakeData
	/**
	 * Buttons for numbers
	 */
	private JButton zero_button = new JButton("0");
	private JButton one_button = new JButton("1");
	private JButton two_button = new JButton("2");
	private JButton three_button = new JButton("3");
	private JButton four_button = new JButton("4");
	private JButton five_button = new JButton("5");
	private JButton six_button = new JButton("6");
	private JButton seven_button = new JButton("7");
	private JButton eight_button = new JButton("8");
	private JButton nine_button = new JButton("9");

	/**
	 * buttons for common operations
	 */
	private JButton add_button = new JButton("+");
	private JButton sub_button = new JButton("-");
	private JButton mul_button = new JButton("×");
	private JButton integerDivision_button = new JButton("/");
	private JButton remainderDivision = new JButton("%");
	private JButton answer_button = new JButton("=");

	/**
	 * buttons for non-standart operations
	 */
	private JButton delete_button = new JButton("D");
	private JButton clear_button = new JButton("C");

	/**
	 * fields for input and output
	 */
	private JLabel input_field = new JLabel("");
	private JTextField output_field = new JTextField("", 1);

	/**
	 * GridBagLayout
	 */
	ActionListener actionListener = new ButtonClick();
	GridBagLayout gridbag = new GridBagLayout();
	GridBagConstraints c = new GridBagConstraints();
	int operationType = 0; // + or - or / or * or %
	String innerPerformance = " ";
	boolean end = false;

	/**
	 * Function for buttons
	 */
	public void make_buttons(int gridwidth, double weightx, int gridx, int gridy, JButton button) {
		c.gridwidth = gridwidth;
		c.weightx = weightx;
		c.gridx = gridx;
		c.gridy = gridy;
		gridbag.setConstraints(button, c);
		add(button);
		button.setFont(new Font("Serif", Font.BOLD, 30));
		button.addActionListener(actionListener);
	}

	/**
	 * Function for action on operation button's press
	 */
	public void TakeNumber(int operation, String line, String arithmetic_operation) {
		if (operationType == 0) {
			innerPerformance = innerPerformance + line + arithmetic_operation;
			input_field.setText(innerPerformance);
			operationType = operation;
			line = "";
			output_field.setText(line);
		}
	}
	
	public void TakeOperation(int operation, String line, String arithmetic_operation) {
		if (operationType == 0) {
			innerPerformance = innerPerformance + line + arithmetic_operation;
			input_field.setText(innerPerformance);
			operationType = operation;
			line = "";
			output_field.setText(line);
		}
	}

	public void end(String line) {
		innerPerformance = " ";
		input_field.setText(innerPerformance);
		operationType = -1;
		line = "";
		output_field.setText(line);
		end = false;
	}

	/**
	 * Constructor for main window
	 */
	public CalculatorGUI() {
		super("Сalculator");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(500, 600);
		this.setLocationRelativeTo(null);
		input_field.setText(innerPerformance);
		setLayout(gridbag);
		c.weighty = 1.0;
		c.fill = GridBagConstraints.BOTH;

		/**
		 * Input_Field
		 */
		c.gridwidth = GridBagConstraints.REMAINDER;
		gridbag.setConstraints(input_field, c);
		add(input_field);
		input_field.setComponentOrientation(ComponentOrientation.RIGHT_TO_LEFT);
		input_field.setFont(new Font("Serif", Font.BOLD, 20));

		/**
		 * Text_Field
		 */
		gridbag.setConstraints(output_field, c);
		add(output_field);
		output_field.setComponentOrientation(ComponentOrientation.RIGHT_TO_LEFT);
		output_field.setFont(new Font("Serif", Font.BOLD, 40));

		/**
		 * Other buttons
		 */
		make_buttons(1, 1.0, 0, 2, seven_button);
		make_buttons(1, 1.0, 1, 2, eight_button);
		make_buttons(1, 1.0, 2, 2, nine_button);
		make_buttons(1, 1.0, 3, 2, delete_button);
		make_buttons(1, 1.0, 4, 2, clear_button);
		make_buttons(1, 1.0, 0, 4, four_button);
		make_buttons(1, 1.0, 1, 4, five_button);
		make_buttons(1, 1.0, 2, 4, six_button);
		make_buttons(1, 1.0, 3, 4, mul_button);
		make_buttons(1, 1.0, 4, 4, integerDivision_button);
		make_buttons(1, 1.0, 0, 5, one_button);
		make_buttons(1, 1.0, 1, 5, two_button);
		make_buttons(1, 1.0, 2, 5, three_button);
		make_buttons(1, 1.0, 3, 5, add_button);
		make_buttons(1, 1.0, 4, 5, sub_button);
		make_buttons(3, 1.0, 0, 6, zero_button);
		make_buttons(1, 1.0, 3, 6, remainderDivision);
		make_buttons(1, 1.0, 4, 6, answer_button);
	}

	/**
	 * Class for interacting with buttons
	 */
	public class ButtonClick implements ActionListener {

		public void actionPerformed(ActionEvent e) {
			String line = output_field.getText();
			if (line.indexOf("0") == 0) {
				line = "";
			}
			try {
				if (end == true) {
					end(line);
				}
				if (e.getSource() == answer_button) {
					switch (operationType) {
					case 1:
						// answer = arg1.Addition(arg1);

						break;
					case 2:
						// answer = arg1.Subtraction(arg1);

						break;
					case 3:
						// answer = arg1.Multiplication(arg1);

						break;
					case 4:
						// answer = arg1.Division(arg1);

						break;
					case 5:
						// answer = arg1.Division(arg1);

						break;

					}
					// label = label + line + " = " + answer.numerator + "/" + answer.denominator;
					input_field.setText(innerPerformance);
					line = "";
					output_field.setText(line);
					end = true;

				} else if (e.getSource() == clear_button) {
					end(line);

				} else if (e.getSource() == delete_button) {

					if (line.length() != 0)
						line = line.substring(0, line.length() - 1);
					output_field.setText(line);

				} else if (e.getSource() == add_button) {
					TakeOperation(1, line, " + ");

				} else if (e.getSource() == sub_button) {
					TakeOperation(2, line, " - ");

				} else if (e.getSource() == mul_button) {
					TakeOperation(3, line, " × ");

				} else if (e.getSource() == integerDivision_button) {
					TakeOperation(4, line, " / ");

				} else if (e.getSource() == remainderDivision) {
					TakeOperation(5, line, " % ");

				} else {
					if (e.getSource() == zero_button && line != "0") {

						output_field.setText(line + "0");

					} else if (e.getSource() == one_button) {
						output_field.setText(line + "1");

					} else if (e.getSource() == two_button) {
						output_field.setText(line + "2");

					} else if (e.getSource() == three_button) {

						output_field.setText(line + "3");

					} else if (e.getSource() == four_button) {

						output_field.setText(line + "4");

					} else if (e.getSource() == five_button) {

						output_field.setText(line + "5");

					} else if (e.getSource() == six_button) {

						output_field.setText(line + "6");

					} else if (e.getSource() == seven_button) {

						output_field.setText(line + "7");

					} else if (e.getSource() == eight_button) {

						output_field.setText(line + "8");

					} else if (e.getSource() == nine_button) {

						output_field.setText(line + "9");
					}
				}

			} catch (Exception ee) {
				end(line);
			}
		}
	}

}
