package edu.urv.mai.imas.helpers;

import jade.util.Logger;

import java.util.logging.Level;

public class LoggerUtils {
    public static void log(Logger logger, Level level, String message) {
        if (logger.isLoggable(level)) {
            logger.log(level, message);
        } else {
            System.err.println("Unable to log " + level.toString());
        }
    }
}
