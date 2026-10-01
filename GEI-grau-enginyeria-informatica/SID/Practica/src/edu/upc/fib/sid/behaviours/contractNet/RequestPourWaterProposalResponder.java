package edu.upc.fib.sid.behaviours.contractNet;

import edu.upc.fib.sid.helpers.ReflectionUtils;
import edu.upc.fib.sid.models.WaterTank;
import jade.core.Agent;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import jade.proto.ContractNetResponder;
import jade.util.Logger;

import static edu.upc.fib.sid.helpers.LoggerUtils.log;

public class RequestPourWaterProposalResponder extends ContractNetResponder {
    private Logger logger = Logger.getMyLogger(this.getClass().getName());

    public RequestPourWaterProposalResponder(Agent a, MessageTemplate mt) {
        super(a, mt);
    }

    @Override
    protected ACLMessage handleCfp(ACLMessage cfp) {
        ACLMessage msg = cfp.createReply();
        WaterTank wasteTank = (WaterTank) ReflectionUtils.invokeMethod(myAgent, "getWasteWaterTank");
        if (wasteTank.isEmpty()) {
            msg.setPerformative(ACLMessage.REFUSE);
            msg.setContent("No water to send");
            log(logger, Logger.INFO, "Factory refuses CPF because of empty wasteTank");
        } else {
            msg.setPerformative(ACLMessage.PROPOSE);
            msg.setContent(String.valueOf(wasteTank.getCurrentLevel()));
            log(logger, Logger.INFO, "Factory proposes to pass " + wasteTank.getCurrentLevel() + "L to EDAR");
        }
        return msg;
    }

    @Override
    protected ACLMessage handleAcceptProposal(ACLMessage cfp, ACLMessage propose, ACLMessage accept) {
        ACLMessage msg = cfp.createReply();
        WaterTank wasteTank = (WaterTank) ReflectionUtils.invokeMethod(myAgent, "getWasteWaterTank");
        msg.setPerformative(ACLMessage.INFORM);
        msg.setContent(String.valueOf(wasteTank.getCurrentLevel()));
        log(logger, Logger.INFO, "Factory passes " + wasteTank.getCurrentLevel() + "L to EDAR");
        return msg;
    }

    @Override
    protected void handleRejectProposal(ACLMessage cfp, ACLMessage propose, ACLMessage reject) {
        log(logger, Logger.INFO, "EDAR rejected Factory proposal");
    }
}
