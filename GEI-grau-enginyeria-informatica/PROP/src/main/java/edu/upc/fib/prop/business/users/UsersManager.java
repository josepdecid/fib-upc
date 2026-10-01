package edu.upc.fib.prop.business.users;

import edu.upc.fib.prop.exceptions.InvalidDetailsException;
import edu.upc.fib.prop.models.User;

public interface UsersManager {

    /**
     * Gets current user logged in the system.
     * @return Currently logged in user.
     */
    User getCurrentUser();

    /**
     * Sets a new current logged user.
     * @param currentUser User to set as currently logged in.
     */
    void setCurrentUser(User currentUser);

    /*--------------- Create */

    /**
     * Creates user from input data with hashed password.
     * @param email Email of the new user.
     * @param name Name of the new user.
     * @param password Non-secured password.
     * @param password2 Repeated password.
     * @return User with prepared data.
     */
    User register(String email, String name, String password, String password2) throws InvalidDetailsException;

    /*--------------- Read */

    /**
     * Checks if login input details are correct.
     * @param email Email of the user.
     * @param password Non-secured password.
     * @return Hashed password.
     */
    String login(String email, String password) throws InvalidDetailsException;

    /*--------------- Update */

    /**
     * Creates user from input data with hashed password.
     * @param newEmail New email of the user.
     * @param newName New name of the user.
     * @param newPassword New password of the user.
     */
    void editAccount(String newEmail, String newName, String newPassword) throws InvalidDetailsException;

    /*--------------- Delete */

    /**
     * Removes current user from the system.
     */
    void logout();

}
