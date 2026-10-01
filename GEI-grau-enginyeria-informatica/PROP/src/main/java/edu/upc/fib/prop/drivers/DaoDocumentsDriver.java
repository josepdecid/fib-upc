package edu.upc.fib.prop.drivers;

import edu.upc.fib.prop.exceptions.AlreadyExistingDocumentException;
import edu.upc.fib.prop.models.Document;
import edu.upc.fib.prop.models.DocumentsCollection;
import edu.upc.fib.prop.persistence.dao.documents.DaoDocuments;
import edu.upc.fib.prop.persistence.dao.documents.impl.DaoDocumentsImpl;
import edu.upc.fib.prop.utils.IOUtils;

import java.io.File;
import java.sql.Connection;
import java.sql.SQLException;

public class DaoDocumentsDriver {

    private static DaoDocuments daoDocuments = new DaoDocumentsImpl();

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

    private static void testCreateDocument() {
        printResult("Introduce data to insert a new document");
        String title = IOUtils.askForString("Title");
        String author = IOUtils.askForString("Author");
        String owner = IOUtils.askForString("Owner");
        Document document = new Document(title, author, "fake", owner);
        try {
            daoDocuments.createNewDocument(c, document);
            printResult("Author created in the DB");
        } catch (AlreadyExistingDocumentException e) {
            printResult("Document already exists in the system");
        }
    }

    private static void testGetAllDocuments() {
        DocumentsCollection documentsCollection = daoDocuments.getAllDocuments(c);
        if (documentsCollection.getDocuments().isEmpty()) {
            printResult("There are no documents in the system");
        } else {
            printResult("All documents");
            System.out.println(String.format("%-45s %-25s %-25s",
                    "Title", "Author", "Owner"));
            System.out.println(String.format("%-45s %-25s %-25s",
                    "-----", "------", "-----"));
            for (Document document : documentsCollection.getDocuments()) {
                System.out.println(String.format("%-45s %-25s %-25s",
                        document.getTitle(), document.getAuthor(), document.getUser()));
            }
        }
    }

    private static void testUpdateDocument() {
        System.out.println("Choose document to update");
        String oldTitle = IOUtils.askForString("Old title");
        String oldAuthor = IOUtils.askForString("Old author");
        Document oldDocument = new Document(oldTitle, oldAuthor, "fake");

        String newTitle = IOUtils.askForString("New title");
        String newAuthor = IOUtils.askForString("New author");
        Document newDocument = new Document(newTitle, newAuthor, "fake");

        try {
            daoDocuments.editExistingDocument(c, oldDocument, newDocument);
        } catch (AlreadyExistingDocumentException e) {
            e.printStackTrace();
        }
        printResult("Document updated successfully");
    }

    private static void testUpdateDocumentWithEmail() {
        System.out.println("Enter old email");
        String oldEmail = IOUtils.askForString("Old email");

        System.out.println("New email");
        String newEmail = IOUtils.askForString("New email");

        daoDocuments.updateDocumentOwner(c, oldEmail, newEmail);
        printResult("Document updated successfully");
    }

    private static void testDeleteDocumentWithTitleAndAuthor() {
        System.out.println("Choose document to delete by title and author");
        String title = IOUtils.askForString("Title");
        String author = IOUtils.askForString("Author");
        Document document = new Document(title, author, "fake");

        daoDocuments.deleteExistingDocument(c, document);
        printResult("Document deleted successfully");
    }

    private static void testDeleteDocumentWithUser() {
        System.out.println("Choose document to delete by owner");
        String user = IOUtils.askForString("Owner");

        daoDocuments.deleteDocuments(c, user);
        printResult("Document deleted successfully");
    }

    public static void main(String[] args) {
        createConnection();
        do {
            printResult("Select test to perform");
            System.out.println("1- Create document");
            System.out.println("2- Get all documents");
            System.out.println("3- Update document");
            System.out.println("4- Update document when change owner email");
            System.out.println("5- Delete documents by title-author");
            System.out.println("6- Delete documents by owner");
            System.out.println("0- Exit");
            int option = IOUtils.askForInt("Select an option", 0, 6);
            switch (option) {
                case 1:
                    testCreateDocument();
                    break;
                case 2:
                    testGetAllDocuments();
                    break;
                case 3:
                    testUpdateDocument();
                    break;
                case 4:
                    testUpdateDocumentWithEmail();
                    break;
                case 5:
                    testDeleteDocumentWithTitleAndAuthor();
                    break;
                case 6:
                    testDeleteDocumentWithUser();
                    break;
                default:
                    closeConnectionAndRemoveDB();
                    return;
            }
            IOUtils.enterToContinue();
        } while(true);
    }

}
