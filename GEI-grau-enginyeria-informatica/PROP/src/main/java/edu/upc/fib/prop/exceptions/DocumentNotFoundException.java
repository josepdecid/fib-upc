package edu.upc.fib.prop.exceptions;

public class DocumentNotFoundException extends Exception {

    public DocumentNotFoundException() {
        super("Document not found in the system");
    }

}
