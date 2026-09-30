package edu.upc.fib.sid.ontology.impl;

import java.io.Serializable;
import java.beans.PropertyChangeSupport;
import java.beans.PropertyChangeListener;

import edu.upc.fib.sid.ontology.ifaces.SupplyWater;

public class SupplyWaterImpl implements SupplyWater, Serializable {
    protected PropertyChangeSupport pcs = new PropertyChangeSupport(this);

    public void addPropertyChangeListener(PropertyChangeListener pcl) {
        pcs.addPropertyChangeListener(pcl);
    }

    public void removePropertyChangeListener(PropertyChangeListener pcl) {
        pcs.removePropertyChangeListener(pcl);
    }


    private static final long serialVersionUID = 5620337684464241768L;

    private String _internalInstanceName;

    public SupplyWaterImpl() {
        this._internalInstanceName = "";
    }

    public SupplyWaterImpl(String instance_name) {
        this._internalInstanceName = instance_name;
    }

    public String toString() {
        return _internalInstanceName;
    }

}
