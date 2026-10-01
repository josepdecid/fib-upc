package edu.upc.fib.sid.behaviours.treatmentPlant;

import edu.upc.fib.sid.behaviours.contractNet.RequestPourWaterProposalInitiator;
import edu.upc.fib.sid.helpers.Globals;
import edu.upc.fib.sid.helpers.MessageUtils;
import edu.upc.fib.sid.models.WaterTank;
import jade.core.AID;
import jade.core.Agent;
import jade.core.behaviours.CyclicBehaviour;
import jade.domain.FIPANames;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import jade.util.Logger;

import java.util.Date;

import static edu.upc.fib.sid.helpers.LoggerUtils.log;
import static edu.upc.fib.sid.helpers.ReflectionUtils.invokeMethod;
import static jade.lang.acl.MessageTemplate.*;

public class TreatmentPlantMainBehaviour extends CyclicBehaviour {
    private Logger logger = Logger.getMyLogger(this.getClass().getName());
    private Integer pendingValue = 0;

    public TreatmentPlantMainBehaviour(Agent agent) {
        super(agent);
    }

    public void action() {
        Boolean waitingNegotiation = (Boolean) invokeMethod(myAgent, "getWaitingNegotiation");
        Boolean waitingClean = (Boolean) invokeMethod(myAgent, "getWaitingClean");
        if (waitingNegotiation || waitingClean) return;

        MessageTemplate mt = and(not(MatchSender(Globals.RiverAID)),
                or(MatchPerformative(ACLMessage.QUERY_IF), MatchPerformative(ACLMessage.INFORM)));
        ACLMessage msg = myAgent.receive(mt);
        while (msg == null) {
            block();
            msg = myAgent.receive(mt);
        }

        WaterTank waterTank = (WaterTank) invokeMethod(myAgent, "getWasteWaterTank");
        Integer quantity = Integer.valueOf(msg.getContent());

        if (msg.getPerformative() == ACLMessage.QUERY_IF) {
            ACLMessage reply = msg.createReply();
            if (waterTank.hasEnoughCapacity(pendingValue + quantity)) {
                reply.setPerformative(ACLMessage.CONFIRM);
                reply.setContent(String.valueOf(quantity));

                pendingValue += quantity;
                log(logger, Logger.INFO, String.format(
                        "EDAR allows Factory %s to pour water", msg.getSender().getLocalName()));
            } else {
                reply.setPerformative(ACLMessage.DISCONFIRM);
                log(logger, Logger.INFO, String.format(
                        "EDAR disallows Factory %s to pour water", msg.getSender().getLocalName()));
            }
            myAgent.send(reply);
        } else if (msg.getPerformative() == ACLMessage.INFORM) {
            waterTank.addWater(quantity);
            pendingValue -= quantity;
            log(logger, Logger.INFO, String.format(
                    "EDAR receives %dL from Factory %s", quantity, msg.getSender().getLocalName()));

            if (waterTank.getFullnessPercent() > 50) {
                if (waterTank.isFull()) {
                    invokeMethod(myAgent, "setWaitingClean", Boolean.TRUE);
                    myAgent.addBehaviour(new TreatmentPlantReturnWaterBehaviour(myAgent, 1000));
                } else {
                    invokeMethod(myAgent, "setWaitingNegotiation", Boolean.TRUE);
                    Integer remainingWater = waterTank.getCapacity() - waterTank.getCurrentLevel();

                    ACLMessage cfp = MessageUtils.createMessage(ACLMessage.CFP, null);
                    cfp.setContent(String.valueOf(remainingWater));
                    cfp.setProtocol(FIPANames.InteractionProtocol.FIPA_CONTRACT_NET);
                    cfp.setReplyByDate(new Date(System.currentTimeMillis() + 2000));
                    for (AID receiver : Globals.FactoriesAIDs) cfp.addReceiver(receiver);

                    myAgent.addBehaviour(new RequestPourWaterProposalInitiator(myAgent, cfp));
                    log(logger, Logger.INFO, String.format(
                            "EDAR starts CFP with %d Factories", Globals.FactoriesAIDs.size()));
                }
            }
        }
    }
}
