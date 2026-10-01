package edu.upc.fib.prop.drivers;

import edu.upc.fib.prop.exceptions.AuthorNotFoundException;
import edu.upc.fib.prop.models.Author;
import edu.upc.fib.prop.models.AuthorsCollection;
import edu.upc.fib.prop.persistence.dao.authors.DaoAuthors;
import edu.upc.fib.prop.persistence.dao.authors.impl.DaoAuthorsImpl;
import edu.upc.fib.prop.utils.IOUtils;

import java.io.File;
import java.sql.Connection;
import java.sql.SQLException;

public class DaoAuthorsDriver {

    private static DaoAuthors daoAuthors = new DaoAuthorsImpl();

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

    private static void testCreateAuthor() {
        printResult("Introduce data to insert a new author");
        String author = IOUtils.askForString("Author name");
        try {
            daoAuthors.createAuthor(c, author);
            printResult("Author created in the DB");
        } catch (SQLException e) {
            printResult("Author already exists in the system");
        }
    }

    private static void testGetAllAuthors() {
        AuthorsCollection authorsCollection = daoAuthors.getAllAuthors(c);
        if (authorsCollection.getAuthors().isEmpty()) {
            printResult("There are no authors in the system");
        } else {
            printResult("All authors");
            for (Author author : authorsCollection.getAuthors()) {
                System.out.println("- " + author.getName());
            }
        }
    }

    private static void testGetAuthorByName() {
        printResult("Introduce data to look for an existing author");
        String author = IOUtils.askForString("Author name");
        try {
            daoAuthors.getAuthorByName(c, author);
            printResult("Author found -> " + author);
        } catch (AuthorNotFoundException e) {
            printResult("Author not found");
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
                    testCreateAuthor();
                    break;
                case 2:
                    testGetAllAuthors();
                    break;
                case 3:
                    testGetAuthorByName();
                    break;
                default:
                    closeConnectionAndRemoveDB();
                    return;
            }
            IOUtils.enterToContinue();
        } while(true);
    }

}
