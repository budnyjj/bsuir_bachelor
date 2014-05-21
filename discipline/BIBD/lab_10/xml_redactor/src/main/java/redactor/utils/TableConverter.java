package redactor.utils;

import java.util.List;

import com.thoughtworks.xstream.converters.Converter;
import com.thoughtworks.xstream.converters.MarshallingContext;
import com.thoughtworks.xstream.converters.UnmarshallingContext;
import com.thoughtworks.xstream.io.HierarchicalStreamReader;
import com.thoughtworks.xstream.io.HierarchicalStreamWriter;

import redactor.model.RowData;
import redactor.model.TableData;

public class TableConverter implements Converter {

    private final String DEFAULT_TYPE = "unicode";

    @Override
    public boolean canConvert(Class cls) {
        return TableData.class.isAssignableFrom(cls);
    }
    
    @Override
    public void marshal(Object value,
                        HierarchicalStreamWriter writer,
                        MarshallingContext context) {
        try {
            TableData tableData = (TableData) value;
        
            List <String> tableAttributes = tableData.getAttributes();        
            int numOfAttributes = tableData.getAttributes().size();

            List <String> tableTypes = tableData.getTypes();
            // fill attributes with default values if not set
            if (tableTypes.size() == 0)
                for (int i = 0; i < numOfAttributes; i++)
                    tableTypes.add("unicode");
        
            for (RowData row : tableData.getRows()) {
                writer.startNode("row");
                for (int i = 0; i < numOfAttributes; i++) {
                    writer.startNode(tableAttributes.get(i));
                    writer.addAttribute("type", tableTypes.get(i));
                    writer.setValue(row.getValues().get(i));
                    writer.endNode();                
                }
                writer.endNode();
            }
        } catch (NullPointerException e) {
            e.printStackTrace();
        }
    }
    
    @Override
        public Object unmarshal(HierarchicalStreamReader reader,
                                UnmarshallingContext context) {
        TableData tableData = new TableData();

        List<String> tableAttributes = tableData.getAttributes();
        List <String> tableTypes = tableData.getTypes();

        // get attributes from first row
        if (reader.hasMoreChildren()) {
            reader.moveDown();
            RowData rowData = new RowData();
            while (reader.hasMoreChildren()) {
                reader.moveDown();
                tableAttributes.add(reader.getNodeName());
                String type = reader.getAttribute("type");
                if (type != null)
                    tableTypes.add(type);
                else 
                    tableTypes.add(DEFAULT_TYPE);
                rowData.getValues().add(reader.getValue());
                reader.moveUp();
            }
            tableData.getRows().add(rowData);
            reader.moveUp();
        }

        // get values
        while (reader.hasMoreChildren()) {
            reader.moveDown();
            RowData rowData = new RowData();
            while (reader.hasMoreChildren()) {
                reader.moveDown();
                rowData.getValues().add(reader.getValue());
                reader.moveUp();
            }
            tableData.getRows().add(rowData);
            reader.moveUp();
        }
        return tableData;
    }
}
