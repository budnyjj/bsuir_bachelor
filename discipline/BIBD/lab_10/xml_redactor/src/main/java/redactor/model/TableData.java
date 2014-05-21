package redactor.model;
import java.util.List;
import java.util.ArrayList;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import redactor.model.RowData;

public class TableData {
    private List<String> attributes = 
        new ArrayList<>();

    private List<String> types = 
        new ArrayList<>();

    private ObservableList<RowData> rows =
        FXCollections.observableArrayList();

    public TableData() { }

    public ObservableList<RowData> getRows() {
        return rows;
    } 

    public void setRows(ObservableList<RowData> rows) {
        this.rows = rows;
    }

    public List<String> getAttributes() {
        return attributes;
    } 

    public void setAttributes(List<String> attributes) {
        this.attributes = attributes;
    }

    public List<String> getTypes() {
        return types;
    } 

    public void setTypes(List<String> types) {
        this.types = types;
    }

    public String toString() {
        String s = "";
        for (int i = 0; i < attributes.size(); i++) {
            s += "| " + attributes.get(i) + " ( " + types.get(i) + " ) ";
        }
        s += "|\n";

        for (RowData row : rows) {
            s += row.toString();
        }
        return s;
    }
}
