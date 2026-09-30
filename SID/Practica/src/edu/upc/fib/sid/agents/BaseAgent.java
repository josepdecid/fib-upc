package edu.upc.fib.sid.agents;

import edu.upc.fib.sid.helpers.DFUtils;
import edu.upc.fib.sid.helpers.Globals;
import edu.upc.fib.sid.ontology.BesosRiverOntology;
import jade.content.lang.sl.SLCodec;
import jade.core.Agent;
import jade.core.Service;
import jade.core.behaviours.Behaviour;
import jade.domain.DFService;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import jade.domain.FIPAException;
import jade.domain.FIPANames;
import jade.util.leap.Iterator;

abstract class BaseAgent extends Agent {
    String name;
    String type;

    protected void setup() {
        assert name != null && type != null;

        ServiceDescription sd = new ServiceDescription();
        sd.setName(this.name);
        sd.setType(this.type);

        DFAgentDescription dfd = new DFAgentDescription();
        dfd.setName(getAID());
        dfd.addServices(sd);

        try {
            DFService.register(this, dfd);
        } catch (FIPAException e) {
            e.printStackTrace();
        }

        getContentManager().registerLanguage(new SLCodec(), FIPANames.ContentLanguage.FIPA_SL0);
        getContentManager().registerOntology(BesosRiverOntology.getInstance());
    }
}
