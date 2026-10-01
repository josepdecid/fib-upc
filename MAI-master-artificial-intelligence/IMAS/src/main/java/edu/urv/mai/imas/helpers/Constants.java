package edu.urv.mai.imas.helpers;

import jade.core.AID;

public class Constants {
    // Types
    public static final String USER = "USER";
    public static final String MANAGER = "MANAGER";
    public static final String CLASSIFIER = "CLASSIFIER";

    // Packages
    public static final String USER_PKG = "edu.urv.mai.imas.agents.UserAgent";
    public static final String MANAGER_PKG = "edu.urv.mai.imas.agents.ManagerAgent";
    public static final String CLASSIFIER_PKG = "edu.urv.mai.imas.agents.ClassifierAgent";

    // AIDs
    public static AID USER_AID;
    public static AID MANAGER_AID;

    // Settings
    public static final Boolean WEIGHTED_VOTING = Boolean.TRUE;

    // Actions
    public static final String TRAIN_ACTION = "TRAIN";
    public static final String TEST_ACTION = "TEST";
}
