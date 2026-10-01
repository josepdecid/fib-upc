package edu.upc.fib.prop.utils;


public class Constants {

    public static final String JDBC_DRIVER = "org.sqlite.JDBC";
    public static final String DB_TEST = "jdbc:sqlite:test.db";
    public static final String DB_DRIVERS = "jdbc:sqlite:drivers.db";
    public static final String DB_DEVELOPMENT = "jdbc:sqlite:development.db";

    public static final String CONNECT_BACKEND_MAGIC_WORD = "__CONNECT__BACKEND__";

    public static final String EMAIL_REGEX = "^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@((\\[[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\])|(([a-zA-Z\\-0-9]+\\.)+[a-zA-Z]{2,}))$";
    public static final String SENTENCE_SEPARATION_REGEX = "[.?!]\\s";
    public static final String WORD_SEPARATION_REGEX = "[.,]\\s|\\s|[.]";
    static final String NUMBER_REGEX = "-?\\d+(\\.\\d+)?";
}
