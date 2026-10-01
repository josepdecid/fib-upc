package edu.upc.fib.prop.drivers;

import edu.upc.fib.prop.business.search.SearchBooleanExpression;
import edu.upc.fib.prop.business.search.impl.SearchBooleanExpressionImpl;
import edu.upc.fib.prop.exceptions.InvalidDetailsException;
import edu.upc.fib.prop.exceptions.InvalidQueryException;
import edu.upc.fib.prop.models.Document;
import edu.upc.fib.prop.models.DocumentsCollection;
import edu.upc.fib.prop.models.DocumentsSet;
import edu.upc.fib.prop.utils.IOUtils;
import edu.upc.fib.prop.business.search.impl.SearchBooleanExpressionImpl.*;

public class DriversBooleanSearch{

    private static SearchBooleanExpression busqueda = new SearchBooleanExpressionImpl();

    private static void printResult(String s) {
        System.out.println("\n---- " + s + " ----\n");
    }

    public static void main(String[] args) {
        do {
        printResult("Insert a sentence to check");
        Document doc;
        DocumentsCollection doccol = new DocumentsCollection();
            String content = IOUtils.askForString("sentence");
            doc = new Document("titol", "autor", content );
            try {
                doccol.addDocument(doc);
            } catch (InvalidDetailsException e) {
                System.out.println("invalid details");
            }
            String expressio = IOUtils.askForString("Insert the boolean expression");
            try {
                DocumentsSet compleixen = busqueda.searchDocumentsByBooleanExpression(expressio, doccol);
                if(compleixen.size() == 0) printResult("your input DON'T satisfies the conditions");
                else printResult("your input satisfies the condition");
            } catch (InvalidQueryException e) {
                System.out.println("invalid query");
            }
        } while(true);
    }
}