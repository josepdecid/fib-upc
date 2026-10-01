package edu.upc.fib.sid.ontology;

import edu.upc.fib.sid.ontology.ifaces.*;
import jade.content.onto.*;
import jade.content.schema.*;

public class BesosRiverOntology extends jade.content.onto.Ontology {

    private static final long serialVersionUID = 5620337684464241768L;

    //NAME
    public static final String ONTOLOGY_NAME = "BesosRiver";
    // The singleton instance of this ontology
    private static Ontology theInstance = new BesosRiverOntology();

    public static Ontology getInstance() {
        return theInstance;
    }


    // VOCABULARY
    public static final String SUPPLYWATER = "SupplyWater";
    public static final String RETURNWATER = "ReturnWater";
    public static final String RESPONDPOURREQUEST = "RespondPourRequest";
    public static final String REQUESTPOUR = "RequestPour";
    public static final String REQUESTWATER = "RequestWater";
    public static final String WATERMASS_CONTAMINANT = "contaminant";
    public static final String WATERMASS_VOLUME = "volume";
    public static final String WATERMASS = "WaterMass";
    public static final String WATERTANK_OWNEDBY = "ownedBy";
    public static final String WATERTANK_HASWATERMASS = "hasWaterMass";
    public static final String WATERTANK = "WaterTank";
    public static final String RIVER = "River";
    public static final String TEXTILE = "Textile";
    public static final String TREATMENTPLANT_HASTANK = "hasTank";
    public static final String TREATMENTPLANT = "TreatmentPlant";
    public static final String PAPERMILL = "PaperMill";
    public static final String STRETCH_NEXTSTRETCH = "nextStretch";
    public static final String STRETCH = "Stretch";
    public static final String METALLURGICAL = "Metallurgical";
    public static final String FACTORY_HASTANK = "hasTank";
    public static final String FACTORY = "Factory";
    public static final String CEMENT = "Cement";
    public static final String AGENT = "Agent";

    /**
     * Constructor
     */
    private BesosRiverOntology() {
        super(ONTOLOGY_NAME, BasicOntology.getInstance());
        try {
            // adding Concept(s)
            ConceptSchema agentSchema = new ConceptSchema(AGENT);
            add(agentSchema, Agent.class);
            ConceptSchema cementSchema = new ConceptSchema(CEMENT);
            add(cementSchema, Cement.class);
            ConceptSchema factorySchema = new ConceptSchema(FACTORY);
            add(factorySchema, Factory.class);
            ConceptSchema metallurgicalSchema = new ConceptSchema(METALLURGICAL);
            add(metallurgicalSchema, Metallurgical.class);
            ConceptSchema stretchSchema = new ConceptSchema(STRETCH);
            add(stretchSchema, Stretch.class);
            ConceptSchema paperMillSchema = new ConceptSchema(PAPERMILL);
            add(paperMillSchema, PaperMill.class);
            ConceptSchema treatmentPlantSchema = new ConceptSchema(TREATMENTPLANT);
            add(treatmentPlantSchema, TreatmentPlant.class);
            ConceptSchema textileSchema = new ConceptSchema(TEXTILE);
            add(textileSchema, Textile.class);
            ConceptSchema riverSchema = new ConceptSchema(RIVER);
            add(riverSchema, River.class);
            ConceptSchema waterTankSchema = new ConceptSchema(WATERTANK);
            add(waterTankSchema, WaterTank.class);
            ConceptSchema waterMassSchema = new ConceptSchema(WATERMASS);
            add(waterMassSchema, WaterMass.class);

            // adding AgentAction(s)
            AgentActionSchema requestWaterSchema = new AgentActionSchema(REQUESTWATER);
            add(requestWaterSchema, RequestWater.class);
            AgentActionSchema requestPourSchema = new AgentActionSchema(REQUESTPOUR);
            add(requestPourSchema, RequestPour.class);
            AgentActionSchema respondPourRequestSchema = new AgentActionSchema(RESPONDPOURREQUEST);
            add(respondPourRequestSchema, RespondPourRequest.class);
            AgentActionSchema returnWaterSchema = new AgentActionSchema(RETURNWATER);
            add(returnWaterSchema, ReturnWater.class);
            AgentActionSchema supplyWaterSchema = new AgentActionSchema(SUPPLYWATER);
            add(supplyWaterSchema, SupplyWater.class);

            // adding AID(s)

            // adding Predicate(s)


            // adding fields
            factorySchema.add(FACTORY_HASTANK, waterTankSchema, 0, ObjectSchema.UNLIMITED);
            stretchSchema.add(STRETCH_NEXTSTRETCH, stretchSchema, 0, ObjectSchema.UNLIMITED);
            treatmentPlantSchema.add(TREATMENTPLANT_HASTANK, waterTankSchema, 0, ObjectSchema.UNLIMITED);
            waterTankSchema.add(WATERTANK_HASWATERMASS, waterMassSchema, 0, ObjectSchema.UNLIMITED);
            waterTankSchema.add(WATERTANK_OWNEDBY, new ConceptSchema("Concept"), 0, ObjectSchema.UNLIMITED);
            waterMassSchema.add(WATERMASS_VOLUME, (TermSchema) getSchema(BasicOntology.STRING), 0, ObjectSchema.UNLIMITED);
            waterMassSchema.add(WATERMASS_CONTAMINANT, (TermSchema) getSchema(BasicOntology.STRING), 0, ObjectSchema.UNLIMITED);

            // adding name mappings

            // adding inheritance
            cementSchema.addSuperSchema(factorySchema);
            factorySchema.addSuperSchema(agentSchema);
            metallurgicalSchema.addSuperSchema(factorySchema);
            stretchSchema.addSuperSchema(riverSchema);
            paperMillSchema.addSuperSchema(factorySchema);
            treatmentPlantSchema.addSuperSchema(agentSchema);
            textileSchema.addSuperSchema(factorySchema);
            riverSchema.addSuperSchema(agentSchema);
        } catch (java.lang.Exception e) {
            e.printStackTrace();
        }
    }
}
