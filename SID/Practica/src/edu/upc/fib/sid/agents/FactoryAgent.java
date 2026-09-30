package edu.upc.fib.sid.agents;

import edu.upc.fib.sid.behaviours.contractNet.RequestPourWaterProposalResponder;
import edu.upc.fib.sid.behaviours.factories.FactoryBypassBehaviour;
import edu.upc.fib.sid.behaviours.factories.FactoryMainBehaviour;
import edu.upc.fib.sid.helpers.Globals;
import edu.upc.fib.sid.models.WaterTank;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;

public class FactoryAgent extends BaseAgent {
    private Integer processCost;
    private WaterTank cleanWaterTank;
    private WaterTank wasteWaterTank;
    private Boolean isRaining = false;
    private Boolean waitingWaterRequest = false;
    private Boolean waitingWaterPouring = false;
    private MessageTemplate mts = MessageTemplate.or(MessageTemplate.MatchPerformative(ACLMessage.CFP),
            MessageTemplate.or(MessageTemplate.MatchPerformative(ACLMessage.ACCEPT_PROPOSAL),
                    MessageTemplate.MatchPerformative(ACLMessage.REJECT_PROPOSAL)));

    @Override
    protected void setup() {
        Object[] args = getArguments();
        if (args.length > 3) {
            name = args[0].toString();
            type = "Factory";
            cleanWaterTank = new WaterTank(Integer.parseInt(args[1].toString()));
            wasteWaterTank = new WaterTank(Integer.parseInt(args[2].toString()));
            processCost = Integer.parseInt(args[3].toString());

            addBehaviour(new FactoryMainBehaviour(this, 2000));
            addBehaviour(new RequestPourWaterProposalResponder(this, mts));

            Globals.FactoriesInstances.add(this);

            super.setup();
        } else {
            System.err.println("Factories require a name as first parameter, a cleanTank capacity as second one, " +
                    "a wasteTank capacity as third one, and a processCost as fourth one.");
            this.doDelete();
        }
    }

    public Integer getProcessCost() {
        return processCost;
    }

    public WaterTank getCleanWaterTank() {
        return cleanWaterTank;
    }

    public WaterTank getWasteWaterTank() {
        return wasteWaterTank;
    }

    public Boolean getWaitingWaterRequest() {
        return waitingWaterRequest;
    }

    public void setWaitingWaterRequest(Boolean waitingWaterRequest) {
        this.waitingWaterRequest = waitingWaterRequest;
    }

    public Boolean getWaitingWaterPouring() {
        return waitingWaterPouring;
    }

    public void setWaitingWaterPouring(Boolean waitingWaterPouring) {
        this.waitingWaterPouring = waitingWaterPouring;
    }

    public void addWaterFromRiver(Integer quantity) {
        this.cleanWaterTank.addWater(quantity);
        this.waitingWaterRequest = Boolean.FALSE;
    }

    public void pourWaterToPlant() {
        this.wasteWaterTank.empty();
        this.waitingWaterPouring = Boolean.FALSE;
    }

    public Boolean getRaining() {
        return isRaining;
    }

    public void setRaining(Boolean raining) {
        isRaining = raining;
    }
}
