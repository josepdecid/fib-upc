package edu.upc.fib.sid.ontology.impl;

import edu.upc.fib.sid.ontology.ifaces.WaterMass;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.io.Serializable;

public class WaterMassImpl implements WaterMass, Serializable {
    protected PropertyChangeSupport pcs = new PropertyChangeSupport(this);

    public void addPropertyChangeListener(PropertyChangeListener pcl) {
        pcs.addPropertyChangeListener(pcl);
    }

    public void removePropertyChangeListener(PropertyChangeListener pcl) {
        pcs.removePropertyChangeListener(pcl);
    }


    private static final long serialVersionUID = 5620337684464241768L;

    private String _internalInstanceName;

    public WaterMassImpl() {
        this._internalInstanceName = "";
    }

    public WaterMassImpl(String instance_name) {
        this._internalInstanceName = instance_name;
    }

    public String toString() {
        return _internalInstanceName;
    }

    private String volume;

    public void setVolume(String value) {
        pcs.firePropertyChange("volume", (this.volume == null ? new String() : this.volume), value);
        this.volume = value;
    }

    public String getVolume() {
        return this.volume;
    }

    private String contaminant;

    public void setContaminant(String value) {
        pcs.firePropertyChange("contaminant", (this.contaminant == null ? new String() : this.contaminant), value);
        this.contaminant = value;
    }

    public String getContaminant() {
        return this.contaminant;
    }

}
