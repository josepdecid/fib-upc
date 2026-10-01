package edu.upc.fib.prop.business.users.impl;

import edu.upc.fib.prop.business.users.UsersManager;
import edu.upc.fib.prop.exceptions.InvalidDetailsException;
import edu.upc.fib.prop.models.User;
import edu.upc.fib.prop.utils.Constants;
import edu.upc.fib.prop.utils.StringUtils;

import java.security.NoSuchAlgorithmException;

public class UsersManagerImpl implements UsersManager {

    private User currentUser;

    public User getCurrentUser() {
        return this.currentUser;
    }

    public void setCurrentUser(User currentUser) {
        this.currentUser = currentUser;
    }

    @Override
    public User register(String email, String name, String password, String password2) throws InvalidDetailsException {
        if (!email.equals("") && !name.equals("") && !password.equals("") && !password2.equals("")) {
            if (email.matches(Constants.EMAIL_REGEX)) {
                if (password.equals(password2)) {
                    try {
                        String pwd = StringUtils.hashData(password);
                        return new User(email, name, pwd);
                    } catch (NoSuchAlgorithmException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
        throw new InvalidDetailsException();
    }

    @Override
    public String login(String email, String password) throws InvalidDetailsException {
        if (email.equals("") || password.equals("") || !email.matches(Constants.EMAIL_REGEX)) {
            throw new InvalidDetailsException();
        }
        try {
            return StringUtils.hashData(password);
        } catch (NoSuchAlgorithmException e) {
            throw new InvalidDetailsException();
        }
    }

    @Override
    public void editAccount(String newEmail, String newName, String newPassword) throws InvalidDetailsException {
        if (newEmail.equals("") || newName.equals("") || newPassword.equals("")
                || !newEmail.matches(Constants.EMAIL_REGEX)) {
            throw new InvalidDetailsException();
        }
    }

    @Override
    public void logout() {
        setCurrentUser(null);
    }

}
