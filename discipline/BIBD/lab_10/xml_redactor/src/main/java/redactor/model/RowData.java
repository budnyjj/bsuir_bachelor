package redactor.model;

import java.util.List;
import java.util.ArrayList;

public class RowData {
    private List<String> values = new ArrayList<String>();

    public RowData() { }

    public RowData(int numberOfValues) {
        for (int i = 0; i < numberOfValues; i++)
            values.add("");
    }

    public RowData(List<String> values) {
        this.values.addAll(values);
    }

    public List<String> getValues() {
        return values;
    }

    public void setValues(List <String> values) {
        this.values = values;
    }

    public String toString() {
        String s = "";
        for (String value : values)
            s += "| " + value;
        s += " |\n";
        return s;
    }
}
