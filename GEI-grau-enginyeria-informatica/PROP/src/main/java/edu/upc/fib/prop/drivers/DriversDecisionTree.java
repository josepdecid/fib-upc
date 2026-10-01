package edu.upc.fib.prop.drivers;

import edu.upc.fib.prop.business.search.SearchBooleanExpression;
import edu.upc.fib.prop.business.search.impl.SearchBooleanExpressionImpl;
import edu.upc.fib.prop.utils.IOUtils;

public class DriversDecisionTree {

    private static void printResult(String result) {
        System.out.println("\n---- " + result + " ----\n");
    }

    private static void testCheckBooleanExpression() {
        String booleanExpression = IOUtils.askForString("Type boolean expression");
        SearchBooleanExpression searchBooleanExpression = new SearchBooleanExpressionImpl();
        if (searchBooleanExpression.checkValidBooleanExpression(booleanExpression)) {
            printResult("Correct!");
        } else {
            printResult("Incorrect!");
        }
    }

    public static void main(String[] args) {
        do {
            printResult("Select test to perform");
            System.out.println("1- Check correctness");
            int option = IOUtils.askForInt("Select an option", 0, 6);
            switch (option) {
                case 1:
                    testCheckBooleanExpression();
                    break;
                default:
                    return;
            }
        } while (true);
    }
}