package edu.upc.fib.prop.drivers;

import edu.upc.fib.prop.business.search.SearchDocument;
import edu.upc.fib.prop.business.search.impl.SearchDocumentImpl;
import edu.upc.fib.prop.exceptions.DocumentNotFoundException;
import edu.upc.fib.prop.exceptions.InvalidDetailsException;
import edu.upc.fib.prop.models.Document;
import edu.upc.fib.prop.models.DocumentsCollection;
import edu.upc.fib.prop.utils.IOUtils;

public class SearchDocumentDriver {

    private static SearchDocument searchDocument = new SearchDocumentImpl();

    private static DocumentsCollection documentsCollection;

    private static void printResult(String s) {
        System.out.println("\n---- " + s + " ----\n");
    }

    private static DocumentsCollection createDocumentsCollection() {
        DocumentsCollection documentsCollection = new DocumentsCollection();
        do {
            System.out.println("Enter a new document:");
            String name = IOUtils.askForString("Title");
            String author = IOUtils.askForString("Author");
            String user = IOUtils.askForString("Owner");
            if (name.equals("-1") && author.equals("-1")) {
                return documentsCollection;
            }
            try {
                documentsCollection.addDocument(new Document(name, author, user));
            } catch (InvalidDetailsException e) {
                System.out.println("That input data was invalid!");
            }
        } while(true);
    }

    private static void testFilterAuthor() {
        String authorName = IOUtils.askForString("Author to search his/her documents");
        try {
            DocumentsCollection filteredDocuments = searchDocument.filterByAuthor(documentsCollection, authorName);
            System.out.println("Next documents found in the system written by " + authorName + ":");
            for (Document document: filteredDocuments.getDocuments()) {
                System.out.println("- " + document.getTitle());
            }
        } catch (DocumentNotFoundException e) {
            System.out.println("Non matching documents");
        }
    }

    private static void testFilterTitleAndAuthor() {
        String title = IOUtils.askForString("Title");
        String author = IOUtils.askForString("Author");
        try {
            Document document = searchDocument.filterByTitleAndAuthor(documentsCollection, title, author);
            System.out.println("Found document " + document.getTitle() + " author " + document.getAuthor());
        } catch (DocumentNotFoundException e) {
            System.out.println("Non matching documents");
        }
    }

    public static void main(String[] args) {
        printResult("First insert some documents (all -1 to exit)");
        documentsCollection = createDocumentsCollection();
        do {
            printResult("Select test to perform");
            System.out.println("1- Filter by author");
            System.out.println("2- Filter by title and author");
            System.out.println("0- Exit");
            int option = IOUtils.askForInt("Select an option", 0, 3);
            switch (option) {
                case 1:
                    testFilterAuthor();
                    break;
                case 2:
                    testFilterTitleAndAuthor();
                    break;
                default:
                    return;
            }
            IOUtils.enterToContinue();
        } while(true);
    }

}
