package edu.upc.fib.prop.exceptions;

public class AlreadyExistingDocumentException extends Exception {

    public AlreadyExistingDocumentException() {
        super("Already existing document for the pair title - author");
    }

}
