package edu.upc.fib.sid.helpers;

import jade.util.Logger;

import java.util.logging.Level;

public class LoggerUtils {
    public static void log(Logger logger, Level level, String message) {
        if (logger.isLoggable(level)) {
            logger.log(level, message);
        } else {
            System.err.println(level.toString() + "is not loggable.");
        }
    }
}
