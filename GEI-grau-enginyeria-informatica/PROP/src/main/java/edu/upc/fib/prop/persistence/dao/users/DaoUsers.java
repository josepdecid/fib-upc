package edu.upc.fib.prop.persistence.dao.users;

import edu.upc.fib.prop.exceptions.AlreadyExistingUserException;
import edu.upc.fib.prop.exceptions.InvalidDetailsException;
import edu.upc.fib.prop.exceptions.UserNotFoundException;
import edu.upc.fib.prop.models.User;

import java.sql.Connection;
import java.sql.SQLException;

/**
 * Data Access Object for users in persistence.
 */
public interface DaoUsers {

    /**
     * Creates a user in persistence.
     * @param c DB connection.
     * @param user User to register.
     * @throws SQLException when SQLiteDB related error.
     */
    void registerNewUser(Connection c, User user) throws SQLException;

    /**
     * Checks email - password combination to login an user.
     * @param c DB connection.
     * @param email Account email.
     * @param password Hashed password from the one that the user has given.
     * @return User that matches the details.
     * @throws UserNotFoundException when user's email doesn't exist in DB.
     * @throws InvalidDetailsException when details doesn't match for a user.
     * @throws SQLException when SQLiteDB related error.
     */
    User checkDetails(Connection c, String email, String password)
            throws UserNotFoundException, InvalidDetailsException, SQLException;

    /**
     * Updates an user with new details.
     * @param c DB connection.
     * @param oldEmail Already existing account old email.
     * @param updatedUser User details to update.
     * @throws UserNotFoundException when user's email doesn't exist in DB.
     * @throws AlreadyExistingUserException when user's email already exists in DB.
     */
    void updateUser(Connection c, String oldEmail, User updatedUser)
            throws UserNotFoundException, AlreadyExistingUserException;

    /**
     * Deletes an user in persistence.
     * @param c DB connection.
     * @param user Already existing user to delete.
     * @throws UserNotFoundException when user's email doesn't exist in DB.
     * @throws SQLException when SQLiteDB related error.
     */
    void deleteUser(Connection c, User user) throws UserNotFoundException, SQLException;

    /**
     * Changes existing user avatar.
     * @param c DB connection.
     * @param email Account email.
     * @param avatar Desired avatar id.
     */
    void changeUserAvatar(Connection c, String email, int avatar);
}