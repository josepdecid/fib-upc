package edu.upc.fib.sid.behaviours.river;

import edu.upc.fib.sid.agents.FactoryAgent;
import edu.upc.fib.sid.helpers.Globals;
import edu.upc.fib.sid.helpers.MessageUtils;
import jade.core.AID;
import jade.core.Agent;
import jade.core.behaviours.TickerBehaviour;
import jade.lang.acl.ACLMessage;
import jade.util.Logger;

import java.util.Random;
import java.util.logging.Level;

import static edu.upc.fib.sid.helpers.Globals.FactoriesInstances;
import static edu.upc.fib.sid.helpers.LoggerUtils.log;
import static edu.upc.fib.sid.helpers.ReflectionUtils.invokeMethod;

public class RiverRainBehaviour extends TickerBehaviour {
    private Logger logger = Logger.getMyLogger(this.getClass().getName());

    public RiverRainBehaviour(Agent a, long period) {
        super(a, period);
    }

    @Override
    protected void onTick() {
        Random random = new Random();
        Integer r = random.nextInt(5);
        Boolean isRaining = r == 0;
        log(logger, Level.INFO, isRaining ? "It's  raining!" : "It's not raining");

        ACLMessage msg = MessageUtils.createMessage(ACLMessage.INFORM, null);
        for (AID receiver : Globals.FactoriesAIDs) msg.addReceiver(receiver);
        for (FactoryAgent i : Globals.FactoriesInstances) invokeMethod(i, "setRaining", isRaining);
        msg.setContent(String.valueOf(isRaining));
        myAgent.send(msg);
    }
}
