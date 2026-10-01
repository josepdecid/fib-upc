package edu.urv.mai.imas.agents;

import edu.urv.mai.imas.behaviours.user.ReadConfigurationBehaviour;
import edu.urv.mai.imas.behaviours.user.RequestActionBehaviour;
import edu.urv.mai.imas.helpers.Constants;
import jade.core.AID;

import static edu.urv.mai.imas.helpers.DFUtils.searchDF;

/**
 * The User agent acts like the human user alter ego in the simulation environment, acting as a bridge between the real
 * and the digital world. Their main jobs are, first read the configuration file that specifies the simulation
 * parameters, and wait for the human user to ask to perform actions, (T) for training and (P) for predicting.
 * The user agent then begins the transaction with the manager agent attaching the details of the simulation.
 */
public class UserAgent extends BaseAgent {
    private AID managerAID;

    @Override
    protected void setup() {
        Object[] args = getArguments();
        if (args.length == 1) {
            this.name = Constants.USER;
            this.type = Constants.USER;
            super.setup();

            // Set the UserAID for global access.
            Constants.USER_AID = getAID();

            // Get manager AID
            AID[] managerAID = searchDF(this, Constants.MANAGER);
            if (managerAID != null)
                this.managerAID = managerAID[0];

            // Add behaviour to read the configuration file and pass the required information to the Manager.
            String configurationFileName = args[0].toString();
            addBehaviour(new ReadConfigurationBehaviour(configurationFileName));

            // Add behaviour that allows to run actions from the running console.
            addBehaviour(new RequestActionBehaviour());
        } else {
            // If there is no specified file, exit the simulation.
            String errorMsg =
                    "One argument is required, the simulation configuration XML file name" +
                            "located at `src/main/resources/settings` folder";
            System.err.println(errorMsg);
            Runtime.getRuntime().exit(1);
        }
    }

    public AID getManagerAID() {
        return this.managerAID;
    }

}
