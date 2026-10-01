package edu.upc.fib.prop.exceptions;

public class AlreadyExistingUserException extends Exception {

    public AlreadyExistingUserException() {
        super("Already existing user with this email");
    }

}
