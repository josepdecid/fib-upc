package edu.upc.fib.sid.helpers;

import edu.upc.fib.sid.agents.FactoryAgent;
import jade.core.AID;

import java.util.ArrayList;
import java.util.List;

public class Globals {
    public static AID RiverAID = null;
    public static AID TreatmentPlantAID = null;
    public static List<AID> FactoriesAIDs = new ArrayList<>();
    public static List<FactoryAgent> FactoriesInstances = new ArrayList<>();

    public static boolean isFactoryRegistered(AID aid) {
        for (AID a : FactoriesAIDs) {
            if (aid.getName().equals(a.getName()))
                return true;
        }
        return false;
    }
}
