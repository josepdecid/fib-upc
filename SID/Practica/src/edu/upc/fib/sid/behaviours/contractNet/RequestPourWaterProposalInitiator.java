package edu.upc.fib.sid.behaviours.contractNet;

import edu.upc.fib.sid.behaviours.treatmentPlant.TreatmentPlantReturnWaterBehaviour;
import edu.upc.fib.sid.models.WaterTank;
import jade.core.AID;
import jade.core.Agent;
import jade.lang.acl.ACLMessage;
import jade.proto.ContractNetInitiator;
import jade.util.Logger;

import java.util.Enumeration;
import java.util.Vector;
import java.util.logging.Level;

import static edu.upc.fib.sid.helpers.LoggerUtils.log;
import static edu.upc.fib.sid.helpers.ReflectionUtils.invokeMethod;

public class RequestPourWaterProposalInitiator extends ContractNetInitiator {
    private Logger logger = Logger.getMyLogger(this.getClass().getName());

    public RequestPourWaterProposalInitiator(Agent agent, ACLMessage cfp) {
        super(agent, cfp);
    }

    @Override
    protected void handlePropose(ACLMessage propose, Vector acceptances) {
        log(logger, Level.WARNING, String.format(
                "Factory %s proposes to send %sL",
                propose.getSender().getLocalName(), propose.getContent()));
    }

    @Override
    protected void handleNotUnderstood(ACLMessage notUnderstood) {
        log(logger, Level.WARNING, String.format(
                "Factory %s didn't understood message", notUnderstood.getSender().getLocalName()));
    }

    @Override
    protected void handleRefuse(ACLMessage refuse) {
        log(logger, Level.INFO, String.format(
                "Factory %s rejected proposal", refuse.getSender().getLocalName()));
    }

    @Override
    protected void handleAllResponses(Vector responses, Vector acceptances) {
        // Evaluate proposals.
        int bestProposal = -1;
        AID bestProposer = null;
        ACLMessage accept = null;
        Enumeration e = responses.elements();
        while (e.hasMoreElements()) {
            ACLMessage msg = (ACLMessage) e.nextElement();
            if (msg.getPerformative() == ACLMessage.PROPOSE) {
                ACLMessage reply = msg.createReply();
                reply.setPerformative(ACLMessage.REJECT_PROPOSAL);
                acceptances.addElement(reply);
                int proposal = Integer.parseInt(msg.getContent());
                if (proposal > bestProposal) {
                    bestProposal = proposal;
                    bestProposer = msg.getSender();
                    accept = reply;
                }
            }
        }

        if (accept != null) {
            System.out.println("Accepting proposal '" + bestProposal + "' from responder '" + bestProposer.getName() + "'");
            accept.setPerformative(ACLMessage.ACCEPT_PROPOSAL);
        }
        else
            invokeMethod(myAgent, "setWaitingNegotiation", Boolean.FALSE);
    }

    @Override
    protected void handleInform(ACLMessage inform) {
        WaterTank waterTank = (WaterTank) invokeMethod(myAgent, "getWasteWaterTank");
        waterTank.addWater(50);

        invokeMethod(myAgent, "setWaitingClean", Boolean.TRUE);
        invokeMethod(myAgent, "setWaitingNegotiation", Boolean.FALSE);
        myAgent.addBehaviour(new TreatmentPlantReturnWaterBehaviour(myAgent, 1000));
    }

    @Override
    protected void handleFailure(ACLMessage failure) {
        log(logger, Level.INFO, String.format(
                "Factory %s denies to send water", failure.getSender().getLocalName()));
    }
}
