package edu.upc.fib.prop.drivers;

import edu.upc.fib.prop.business.users.UsersManager;
import edu.upc.fib.prop.business.users.impl.UsersManagerImpl;
import edu.upc.fib.prop.exceptions.InvalidDetailsException;
import edu.upc.fib.prop.models.User;
import edu.upc.fib.prop.utils.IOUtils;

public class UsersManagerDriver {

    private static UsersManager usersManager = new UsersManagerImpl();

    private static void printResult(String s) {
        System.out.println("\n---- " + s + " ----\n");
    }

    private static void testRegister() {
        printResult("Introduce data to register a new user");
        String email = IOUtils.askForString("Email");
        String username = IOUtils.askForString("Username");
        String password = IOUtils.askForString("Password");
        String password2 = IOUtils.askForString("Repeat password");
        try {
            User user = usersManager.register(email, username, password, password2);
            printResult("User ready to register with following data:");
            System.out.println("- Email -> " + user.getEmail());
            System.out.println("- Username -> " + user.getName());
            System.out.println("- Hashed Password -> " + user.getPassword());
            System.out.println("New data accepted and will be processed");
        } catch (InvalidDetailsException e) {
            printResult("Invalid input data!");
        }
    }

    private static void testLogin() {
        printResult("Introduce data to login");
        String email = IOUtils.askForString("Email");
        String password = IOUtils.askForString("Password");
        try {
            String hashedPassword = usersManager.login(email, password);
            printResult("Valid data!");
            System.out.println("- Hashed Password -> " + hashedPassword);
            System.out.println("Data accepted and will be processed");
        } catch (InvalidDetailsException e) {
            printResult("Invalid input data!");
        }
    }

    private static void testUpdate() {
        printResult("Enter new data to set");
        String email = IOUtils.askForString("New email");
        String username = IOUtils.askForString("New username");
        String password = IOUtils.askForString("New password");
        try {
            usersManager.editAccount(email, username, password);
            System.out.println("New data accepted and will be processed");
        } catch (InvalidDetailsException e) {
            printResult("Invalid input data!");
        }
    }

    public static void main(String[] args) {
        do {
            printResult("Select test to perform");
            System.out.println("1- Register");
            System.out.println("2- Login");
            System.out.println("3- Update");
            System.out.println("0- Exit");
            int option = IOUtils.askForInt("Select an option", 0, 3);
            switch (option) {
                case 1:
                    testRegister();
                    break;
                case 2:
                    testLogin();
                    break;
                case 3:
                    testUpdate();
                    break;
                default:
                    return;
            }
            IOUtils.enterToContinue();
        } while(true);
    }
}
