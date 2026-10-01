package edu.upc.fib.prop.drivers;

import edu.upc.fib.prop.utils.Constants;
import edu.upc.fib.prop.utils.FileUtils;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

class DriversUtils {

    static Connection createConnectionAndDB() throws SQLException, ClassNotFoundException {
        Class.forName(Constants.JDBC_DRIVER);
        Connection c = DriverManager.getConnection(Constants.DB_DRIVERS);
        Statement statement = c.createStatement();
        String sql = FileUtils.readFile("src/main/resources/sql/dbInitializer.sql");
        statement.executeUpdate(sql);
        statement.close();
        return c;
    }

}
