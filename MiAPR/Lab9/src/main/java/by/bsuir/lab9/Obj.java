package by.bsuir.lab9;

import javafx.beans.property.SimpleStringProperty;

import java.util.Map;

public class Obj {
    private final SimpleStringProperty className;
    private Map<Integer, Double> attributes;

    public Obj(String className, Map<Integer, Double> attributes) {
        this.className = new SimpleStringProperty(className);
        this.attributes = attributes;
    }

    public String getClassName() {
        return className.get();
    }

    public void setClassName(String className) {
        this.className.set(className);
    }

    public Map<Integer, Double> getAttributes() {
        return attributes;
    }

    public void setAttributes(Map<Integer, Double> attributes) {
        this.attributes = attributes;
    }
}
