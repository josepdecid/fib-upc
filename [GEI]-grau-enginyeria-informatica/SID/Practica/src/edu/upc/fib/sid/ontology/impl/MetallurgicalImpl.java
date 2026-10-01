package edu.upc.fib.sid.ontology.impl;

import edu.upc.fib.sid.ontology.ifaces.Metallurgical;
import edu.upc.fib.sid.ontology.ifaces.WaterTank;
import jade.util.leap.ArrayList;
import jade.util.leap.Iterator;
import jade.util.leap.List;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.io.Serializable;

public class MetallurgicalImpl implements Metallurgical, Serializable {
    protected PropertyChangeSupport pcs = new PropertyChangeSupport(this);

    public void addPropertyChangeListener(PropertyChangeListener pcl) {
        pcs.addPropertyChangeListener(pcl);
    }

    public void removePropertyChangeListener(PropertyChangeListener pcl) {
        pcs.removePropertyChangeListener(pcl);
    }


    private static final long serialVersionUID = 5620337684464241768L;

    private String _internalInstanceName;
    private Object oldList = null;

    public MetallurgicalImpl() {
        this._internalInstanceName = "";
    }

    public MetallurgicalImpl(String instance_name) {
        this._internalInstanceName = instance_name;
    }

    public String toString() {
        return _internalInstanceName;
    }

    private List hasTank = new ArrayList();

    public void addHasTank(WaterTank elem) {
        hasTank.add(elem);
        pcs.firePropertyChange("hasTank", oldList, this.hasTank);
    }

    public boolean removeHasTank(WaterTank elem) {
        boolean result = hasTank.remove(elem);
        pcs.firePropertyChange("hasTank", oldList, this.hasTank);
        return result;
    }

    public void clearAllHasTank() {
        hasTank.clear();
        pcs.firePropertyChange("hasTank", oldList, this.hasTank);
    }

    public Iterator getAllHasTank() {
        return hasTank.iterator();
    }

    public List getHasTank() {
        return hasTank;
    }

    public void setHasTank(List l) {
        hasTank = l;
    }

}
