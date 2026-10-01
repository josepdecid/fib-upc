package edu.upc.fib.prop.persistence.dao.users.impl;

import edu.upc.fib.prop.exceptions.AlreadyExistingUserException;
import edu.upc.fib.prop.exceptions.InvalidDetailsException;
import edu.upc.fib.prop.exceptions.UserNotFoundException;
import edu.upc.fib.prop.models.User;
import edu.upc.fib.prop.persistence.dao.users.DaoUsers;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class DaoUsersImpl implements DaoUsers {

    @Override
    public void registerNewUser(Connection c, User user) throws SQLException {
        Statement statement = c.createStatement();
        String query = String.format("INSERT INTO users VALUES('%s', '%s', '%s', '%s', '%d');",
                user.getEmail(), user.getName(), user.getPassword(), user.getAvatar(), 0);
        int inserted = statement.executeUpdate(query);
        if (inserted != 1)
            throw new SQLException();
        statement.close();
    }

    @Override
    public User checkDetails(Connection c, String email, String password)
            throws UserNotFoundException, InvalidDetailsException, SQLException {
        Statement statement = c.createStatement();
        String query = String.format("SELECT * FROM users WHERE email='%s';", email);
        ResultSet rs = statement.executeQuery(query);
        if (rs.next()) {
            String authEmail = rs.getString("email");
            String authName = rs.getString("user_name");
            String authPassword = rs.getString("password");
            String avatar = rs.getString("avatar");
            if (authEmail.equals(email) && authPassword.equals(password)) {
                User u = new User(authEmail, authName, authPassword);
                u.setAvatar(avatar);
                return u;
            } else {
                throw new InvalidDetailsException();
            }
        } else {
            throw new UserNotFoundException();
        }
    }

    @Override
    public void updateUser(Connection c, String oldEmail, User updatedUser)
            throws UserNotFoundException, AlreadyExistingUserException {
        Statement statement = null;
        try {
            statement = c.createStatement();
            String query = String.format("UPDATE users SET email='%s', user_name='%s', password='%s', avatar='%s' WHERE email='%s';",
                    updatedUser.getEmail(), updatedUser.getName(), updatedUser.getPassword(), updatedUser.getAvatar(), oldEmail);
            int updated = statement.executeUpdate(query);
            if (updated != 1) {
                throw new UserNotFoundException();
            }
        } catch (SQLException e) {
            throw new AlreadyExistingUserException();
        } finally {
            try {
                if (statement != null) {
                    statement.close();
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void deleteUser(Connection c, User user) throws UserNotFoundException, SQLException {
        Statement statement = c.createStatement();
        String query = String.format("DELETE FROM users WHERE email='%s';", user.getEmail());
        int deleted = statement.executeUpdate(query);
        if (deleted != 1)
            throw new UserNotFoundException();
        statement.close();
    }

    @Override
    public void changeUserAvatar(Connection c, String email, int avatar) {
        try {
            Statement statement = c.createStatement();
            String query = String.format("UPDATE users SET avatar='%d' WHERE email LIKE '%s'", avatar, email);
            statement.executeUpdate(query);
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

}
