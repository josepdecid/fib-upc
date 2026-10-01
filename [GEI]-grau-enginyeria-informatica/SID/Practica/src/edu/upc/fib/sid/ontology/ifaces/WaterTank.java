package edu.upc.fib.sid.ontology.ifaces;

import java.beans.PropertyChangeListener;
import java.io.Serializable;

public interface WaterTank extends jade.content.Concept, Serializable {
    public void addPropertyChangeListener(PropertyChangeListener pcl);

    public void removePropertyChangeListener(PropertyChangeListener pcl);

    public void setHasWaterMass(WaterMass value);

    public WaterMass getHasWaterMass();

    public void setOwnedBy(Object value);

    public Object getOwnedBy();

}
