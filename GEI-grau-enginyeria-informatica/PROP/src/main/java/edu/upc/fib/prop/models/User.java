package edu.upc.fib.prop.models;

public class User {

    final private String DEFAULT_AVATAR = "1";

    private String email;
    private String name;
    private String password;
    private Boolean admin;
    private String avatar;

    public User(String email, String name, String password) {
        this.email = email;
        this.name = name;
        this.password = password;
        this.admin = Boolean.FALSE;
        this.avatar = DEFAULT_AVATAR;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getAvatar() {return avatar;}

    public void setAvatar(String avatar) {this.avatar = avatar;}

    public Boolean getAdmin() {
        return admin;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        User user = (User) o;

        return email != null ? email.equals(user.email) : user.email == null
                && (name != null ? name.equals(user.name) : user.name == null
                && (password != null ? password.equals(user.password) : user.password == null
                && (admin != null ? admin.equals(user.admin) : user.admin == null)));
    }
}
