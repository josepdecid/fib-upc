package edu.upc.fib.prop.exceptions;

public class AuthorNotFoundException extends Exception {

    public AuthorNotFoundException() {
        super("Non existing author with this name");
    }

}
