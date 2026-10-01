package edu.urv.mai.imas.agents;

import jade.content.lang.sl.SLCodec;
import jade.core.Agent;
import jade.domain.DFService;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import jade.domain.FIPAException;
import jade.domain.FIPANames;

/**
 * Agent class that inherits directly from JADE's Agent.
 * It abstracts the process of registering the agent and its service to DF
 * and registering the codec required to handle FIPA SL.
 */
public abstract class BaseAgent extends Agent {
    String name;
    String type;

    protected void setup() {
        assert name != null && type != null;

        // Create a service description using its name and type.
        ServiceDescription sd = new ServiceDescription();
        sd.setName(this.name);
        sd.setType(this.type);

        // Create a Directory facilitator description of the service.
        DFAgentDescription dfd = new DFAgentDescription();
        dfd.setName(getAID());
        dfd.addServices(sd);

        try {
            // Register the agent to the DF.
            DFService.register(this, dfd);
        } catch (FIPAException e) {
            // Some unexpected error occurred when trying to register the agent to the DF.
            String errorMsg = String.format("Error registering %s agent to the DF.", this.name);
            System.err.println(errorMsg);
            Runtime.getRuntime().exit(1);
        }

        // Register a Codec to handle FIPA SL Content Language Specification
        getContentManager().registerLanguage(new SLCodec(), FIPANames.ContentLanguage.FIPA_SL0);
    }
}
