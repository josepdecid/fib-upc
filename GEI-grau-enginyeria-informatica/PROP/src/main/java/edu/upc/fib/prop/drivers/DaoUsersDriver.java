package edu.upc.fib.prop.drivers;

import edu.upc.fib.prop.exceptions.AlreadyExistingUserException;
import edu.upc.fib.prop.exceptions.InvalidDetailsException;
import edu.upc.fib.prop.exceptions.UserNotFoundException;
import edu.upc.fib.prop.models.User;
import edu.upc.fib.prop.persistence.dao.users.DaoUsers;
import edu.upc.fib.prop.persistence.dao.users.impl.DaoUsersImpl;
import edu.upc.fib.prop.utils.IOUtils;

import java.io.File;
import java.sql.Connection;
import java.sql.SQLException;

public class DaoUsersDriver {

    private static DaoUsers daoUsers = new DaoUsersImpl();

    private static Connection c;

    private static void printResult(String s) {
        System.out.println("\n---- " + s + " ----\n");
    }

    private static void createConnection() {
        try {
            c = DriversUtils.createConnectionAndDB();
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static void closeConnectionAndRemoveDB() {
        File f = new File("drivers.db");
        f.delete();
        try {
            c.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void testRegisterUser() {
        printResult("Introduce data to insert a new user");
        String email = IOUtils.askForString("Email");
        String name = IOUtils.askForString("Name");
        String password = IOUtils.askForString("Password");
        User user = new User(email, name, password);

        try {
            daoUsers.registerNewUser(c, user);
            printResult("Successfully inserted into the DB");
        } catch (SQLException e) {
            printResult("Already existing user!");
        }
    }

    private static void testCheckDetails() {
        printResult("Introduce data to check for an existing user");
        String email = IOUtils.askForString("Email");
        String password = IOUtils.askForString("Password");

        try {
            daoUsers.checkDetails(c, email, password);
            printResult("Successful details match");
        } catch (UserNotFoundException | SQLException e) {
            printResult("User not found!");
        } catch (InvalidDetailsException e) {
            printResult("Invalid details!");
        }
    }

    private static void testUpdateUser() {
        printResult("Introduce data to update an existing user");
        String oldEmail = IOUtils.askForString("Old user email to update");
        String newEmail = IOUtils.askForString("New email");
        String newName = IOUtils.askForString("New name");
        String newPassword = IOUtils.askForString("New password");
        User user = new User(newEmail, newName, newPassword);

        try {
            daoUsers.updateUser(c, oldEmail, user);
            printResult("Successful details update");
        } catch (UserNotFoundException e) {
            printResult("User not found!");
        } catch (AlreadyExistingUserException e) {
            printResult("Details match another already existing user");
        }
    }

    private static void testDeleteUser() {
        printResult("Introduce data to delete an existing user");
        String email = IOUtils.askForString("User email");
        try {
            daoUsers.deleteUser(c, new User(email, "fake", "fake"));
            printResult("User successfully deleted!");
        } catch (UserNotFoundException | SQLException e) {
            printResult("User not found!");
        }
    }

    public static void main(String[] args) {
        createConnection();
        do {
            printResult("Select test to perform");
            System.out.println("1- Create author");
            System.out.println("2- Get all authors");
            System.out.println("3- Get author by name");
            System.out.println("0- Exit");
            int option = IOUtils.askForInt("Select an option", 0, 3);
            switch (option) {
                case 1:
                    testRegisterUser();
                    break;
                case 2:
                    testCheckDetails();
                    break;
                case 3:
                    testUpdateUser();
                    break;
                case 4:
                    testDeleteUser();
                    break;
                default:
                    closeConnectionAndRemoveDB();
                    return;
            }
            IOUtils.enterToContinue();
        } while(true);
    }

}
