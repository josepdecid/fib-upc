package edu.upc.fib.sid.ontology.ifaces;

import jade.util.leap.Iterator;
import jade.util.leap.List;

import java.beans.PropertyChangeListener;
import java.io.Serializable;

public interface TreatmentPlant extends Agent, Serializable {
    public void addPropertyChangeListener(PropertyChangeListener pcl);

    public void removePropertyChangeListener(PropertyChangeListener pcl);

    public void addHasTank(WaterTank elem);

    public boolean removeHasTank(WaterTank elem);

    public void clearAllHasTank();

    public Iterator getAllHasTank();

    public List getHasTank();

    public void setHasTank(List l);

}
