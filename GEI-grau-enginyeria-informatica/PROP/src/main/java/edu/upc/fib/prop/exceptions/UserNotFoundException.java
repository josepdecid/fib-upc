package edu.upc.fib.prop.exceptions;

public class UserNotFoundException extends Exception {

    public UserNotFoundException() {
        super("User not found in the system");
    }

}
